//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
t[N<<2]：线段树节点，存区间和 val、区间最大 mx、区间最小 mn。
build：递归建树，叶节点三个字段都是 a[l]，非叶用 push_up 合并左右孩子的 max/min
up：给区间节点整段加 k——val += 长度*k，mx/mn += k，并把懒标记 laz[x] += k。
push_down：把父节点累积的懒标记下放到两个儿子。
in/out：区间包含判定与完全不相交判定。
update：标准区间加（含懒标记），完全包含则 up，部分覆盖则先 push_down 再递归，最后 push_up。注意这里没有 push_up 也会更新 max/min，但递归路径靠 push_up 回溯
读 n、m 和数组 a，建线段树
对每个区间 [l[i], r[i]]：
update(1,1,n, l[i], r[i], -1)：全局减 1。
nxt[l[i]] 记录左端点为 i 的区间右端；pre[r[i]] 记录右端点为 i 的区间左端（用于后续增量扫描）
对每个位置 i：
先把"左端点为 i"的区间加回来（update(1,1,n, i, nxt[i][j], 1)）——因为从 i 起，这些区间被当作"不再对位置 i 起作用" ？实际上这是在模拟"以 i 为分隔点重新选区间"：
移动分割点时，左端 ≤ i 的区间（其右端 ≥ i）恢复其影响。
更新答案：比较 t[1].mx - t[1].mn 与 ans，取大者，并记录最优分割点 p = i。t[1] 是整棵树的根，其 mx - mn 即备份全局最大值减最小值。
再把"右端点为 i"的区间减回去（update(1,1,n, pre[i][j], i, -1)）——因为这些区间到 i 结束，之后不再作用。
本质是滑动窗口/差分式地维护"每次只考虑左端点 ≤ i ≤ 右端点的区间的 +/-1 效果"，从而在线更新数组极值差。原本暴力是 O(n·m)，这里优化为 O((n+m)logn)
输出最优差值 ans。
统计并输出所有不包含位置 p 的区间（out(p,p,l[i],r[i]) 当区间与点 p 不相交时为真）——这些区间是最终方案中需要执行的（被选中的操作区间）。
先输出个数 cnt，再逐行输出这些区间编号（从 1 开始）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e5+10;

struct node { int val, mx, mn; } t[N<<2];

void push_up(int x) {
    t[x].mx = max(t[x<<1].mx, t[x<<1|1].mx);
    t[x].mn = min(t[x<<1].mn, t[x<<1|1].mn);
}

int a[N];
void build(int x, int l, int r) {
    if (l == r) { t[x].val = t[x].mx = t[x].mn = a[l]; return; }
    build(x<<1, l, mid); build(x<<1|1, mid+1, r);
    push_up(x);
}

int laz[N<<2];
void up(int x, int len, int k) { t[x].val += len*k; t[x].mx += k; t[x].mn += k; laz[x] += k; }
void push_down(int x, int l, int r) {
    up(x<<1,mid-l+1,laz[x]); up(x<<1|1,r-mid,laz[x]);
    laz[x] = 0;
}
bool in(int l, int r, int L, int R) { return l >= L && r <= R; }
bool out(int l, int r, int L, int R) { return l > R || r < L; }

void update(int x, int l, int r, int L, int R, int k) {
    if (in(l,r,L,R)) up(x,r-l+1,k);
    else if (!out(l,r,L,R)) {
        push_down(x,l,r);
        update(x<<1,l,mid,L,R,k); update(x<<1|1,mid+1,r,L,R,k);
        push_up(x);
    }
}

int n, m, l[N], r[N], ans, p, cnt;
vector<int> pre[N], nxt[N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    build(1,1,n);
    rep(i,m) {
        cin >> l[i] >> r[i];
        update(1,1,n,l[i],r[i],-1);
        nxt[l[i]].push_back(r[i]); pre[r[i]].push_back(l[i]);
    }
    rep(i,n) {
        for (int j = 0; j < nxt[i].size(); j++) update(1,1,n,i,nxt[i][j],1);
        if (t[1].mx - t[1].mn > ans) ans = t[1].mx - t[1].mn, p = i;
        for (int j = 0; j < pre[i].size(); j++) update(1,1,n,pre[i][j],i,-1);
    }
    cout << ans << '\n';
    rep(i,m) if (out(p,p,l[i],r[i])) cnt++;
    cout << cnt << '\n';
    rep(i,m) if (out(p,p,l[i],r[i])) cout << i << ' ';
    cout << '\n';
    return 0;
}