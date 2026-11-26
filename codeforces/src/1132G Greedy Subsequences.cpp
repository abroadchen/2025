//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
后序遍历累加子树节点数得 sz[x]（以 x 为根、即元素 x 为最大值的区间长度）。
记录每个节点在子树中的 DFS 序 dfn[x]，保证每个节点的所有后代是一段连续 dfn 区间 [dfn[x], dfn[x]+sz[x]-1]——这是线段树区间 add 的基础
数据离散到一维线段树，index 是 dfn 序号。
add 给区间 [L,R]（某个元素对应的子树区间）整体 +1，用懒标记加速，区间最大值 mx[u] 同步 +1。
clear：单点把某元素（其子树区间整段）置为可用(0，在窗口内)或不可用(-N，移出窗口)，并向上更新区间最大值。
注意：这里线段树存储的是「以该 dfn 对应元素为根的子树的 dfn 区间」。给整个区间 +1 或置 0 相当于是对整个子树覆盖
单调栈：从左到右，遇比栈顶大的元素就弹出栈顶并令其为 i 的子节点（在笛卡尔树中，更大的值做父）。最后栈内元素统一挂到虚拟根 n+1（值为无穷大）。
得到一棵以 n+1 为根、父亲值 ≥ 儿子值（对应 a 值较大者在上）的笛卡尔树。
dfs(n+1) 确定 sz 和 dfn，build 初始化线段树
先预热前 k-1 个元素。
窗口向右滑动：加入新元素 i（置可用并给其子树区间 +1），输出全树最大值 mx[1]（即当前窗口内所有元素 sz 的最大值），然后移出最左 i-k+1（置不可用）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 1e6+5;

int sz[N], dfn[N], tot;
vector<int> e[N];
void dfs(int x) {
    sz[x] = 1; dfn[x] = ++tot;
    for (int u : e[x]) { dfs(u); sz[x] += sz[u]; }
}

int mx[N<<2];
void build(int u, int l, int r) {
    mx[u] = -N;
    if (l < r) build(u<<1, l, mid), build(u<<1|1, mid+1, r);
}
int lz[N<<2];
void push_down(int u) {
    lz[u<<1] += lz[u], lz[u<<1|1] += lz[u];
    mx[u<<1] += lz[u], mx[u<<1|1] += lz[u];
    lz[u] = 0;
}
void add(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) lz[u]++, mx[u]++;
    else {
        if (lz[u]) push_down(u);
        if (L <= mid) add(u<<1,l,mid,L,R);
        if (mid < R) add(u<<1|1,mid+1,r,L,R);
        mx[u] = max(mx[u<<1], mx[u<<1|1]);
    }
}
void clear(int u, int l, int r, int x, bool op) {
    if (l == r) mx[u] = op ? -N : 0;
    else {
        if (lz[u]) push_down(u);
        if (x <= mid) clear(u<<1, l, mid, x, op);
        else clear(u<<1|1, mid+1, r, x, op);
        mx[u] = max(mx[u<<1], mx[u<<1|1]);
    }
}

int n, k, a[N], fa[N];
stack<int> t;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) {
        cin >> a[i];
        while (!t.empty() && a[t.top()] < a[i]) {
            fa[t.top()] = i;
            e[i].push_back(t.top()); t.pop();
        }
        t.push(i);
    }
    while (!t.empty()) {
        fa[t.top()] = n + 1;
        e[n+1].push_back(t.top()); t.pop();
    }
    dfs(n+1); build(1,1,n+1);
    rep(i,k-1) {
        clear(1,1,n+1,dfn[i],0);
        add(1,1,n+1,dfn[i],dfn[i]+sz[i]-1);
    }
    for (int i = k; i <= n; i++) {
        clear(1,1,n+1,dfn[i],0);
        add(1,1,n+1,dfn[i],dfn[i]+sz[i]-1);//窗口右端加入 i
        cout << mx[1] << ' ';
        clear(1,1,n+1,dfn[i-k+1],1);//窗口左端元素移出(置不可用)
    }
    return 0;
}