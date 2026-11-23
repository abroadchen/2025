//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
q[id]：第 id 个询问的左右端点
两个树状数组工具类。t1 用来存带权位置值（对 l[i] 或 r[i] 累加），t2 用来存数量（是否选中）
p[l[i]]：在位置 l[i] 挂上节点 i。
v[q[i].l]：在询问左界挂上询问号。
ans[id]：询问答案
单调递减栈（维护严格递减）。
弹出时得到右界：r[被弹出] = i。
入栈前栈顶即左界 l[i]。
结束清栈，右界设为 n+1（哨兵）
初始把所有 i 插入 t1，权值 = l[i]；t2 先不放任何东西
从左到右推进扫描线 i。
p[i-1] 里的节点 j 意味着 l[j] = i-1，即到了左界，把它从"带权"部分移到"已激活"部分。
对每个以 i 为左界的询问，减掉当前区间内 l[j] 的和等贡献，构成左半贡献
换成用 r[i] 挂节点、q[i].r 挂询问。
t1 初值为 r[i]-1
从右往左扫描（对应右界推动）。
p[i+1] 节点表示 r[j] = i+1，即到右界，从 t1 拿掉 r[j]-1、加入 t2。
对以 i 为右界的询问，加上区间内 r[x]-1 之和，再加 i× 已激活数量。
两次扫描的“减”与“加”相互抵消中间项，恰好合成每个子区间最大值贡献的精确值
按输入顺序输出每个询问答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e6+5;

struct node { int l, r; } q[N];

int n;
struct BIT {
    ll tr[N];
    void clear() { memset(tr, 0, sizeof(tr)); }
    void upd(int x, ll k) { for (int i = x; i <= n; i += i&-i) tr[i] += k; }
    ll qry(int x) {
        ll res = 0;
        for (int i = x; i; i -= i&-i) res += tr[i];
        return res;
    }
} t1, t2;

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int m, a[N], st[N], l[N], r[N];
vector<int> p[N], v[N];
ll ans[N];
int main() {
    fast;
    read(n); read(m);
    rep(i,n) read(a[i]);
    rep(i,m) read(q[i].l);
    rep(i,m) read(q[i].r);
    int top = 0;
    rep(i,n) {
        while (top && a[st[top]] < a[i]) r[st[top--]] = i;
        if (top) l[i] = st[top];
        st[++top] = i;
    }
    while (top) r[st[top--]] = n + 1;
    rep(i,n) p[l[i]].push_back(i);
    rep(i,m) v[q[i].l].push_back(i);
    rep(i,n) t1.upd(i,l[i]);
    rep(i,n) {
        for (int j : p[i-1]) { t1.upd(j,-l[j]); t2.upd(j,1); }
        for (int j = 0; j < v[i].size(); ++j) {
            int id = v[i][j];
            ans[id] -= t1.qry(q[id].r)-t1.qry(q[id].l-1);
            ans[id] -= (ll)(i-1)*(t2.qry(q[id].r)-t2.qry(q[id].l-1));
        }
    }
    for (int i = 0; i <= n; ++i) p[i].clear(), v[i].clear();
    rep(i,n) p[r[i]].push_back(i);
    rep(i,m) v[q[i].r].push_back(i);
    t1.clear(); t2.clear();
    rep(i,n) t1.upd(i,r[i]-1);
    for (int i = n; i; --i) {
        for (int j : p[i+1]) { t1.upd(j,-r[j]+1); t2.upd(j,1); }
        for (int j = 0; j < v[i].size(); ++j) {
            int id = v[i][j];
            ans[id] += t1.qry(q[id].r)-t1.qry(q[id].l-1);
            ans[id] += (ll)i*(t2.qry(q[id].r)-t2.qry(q[id].l-1));
        }
    }
    rep(i,m) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}