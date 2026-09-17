//
// Created by Psy.C on 2026/9/17.
//
/**
t[k] 是 pair<int,int>。线段树每个节点存 {某值, 下标}。
push_up：父节点取两子树中字典序较大的 pair（先比较 first，再比较 second），因为 pair 的 max 按字典序比较
build：叶子节点 t[l] = {vis[l], l}，即每个位置存 {vis[该位置], 该位置}。
query(L,R)：区间查询最大 pair（按字典序），越界返回 {0,-1}（作为最小值便于 max）。
update(pos)：把位置 pos 的值置为 {0,-1}（即"删除/激活"该位置，标记为已访问）
p[u] 最终被赋值为 ++cur，这是一个后序（先递归后编号）‍的过程，cur 从 0 递增。
每次访问 u：
先用 update 删除/标记 u。
若 vis[u]（记录某个关联位置）≤ n 且它的排列号还没确定，先 dfs 它。
然后循环：在区间 [1, a[u]-1] 里查最大 pair {fst, snd}，只要 fst > u 就继续 dfs snd，直到最大 pair 的 first ≤ u 为止。
最后给 u 分配编号 cur。
这构成了一个基于约束的 DFS 构造拓扑顺序：a[i] 表示某种大小关系的约束（第一个大于 i 的下标），vis 记录反向关系，DFS 保证构造出一个满足所有"大于关系"的排列 p
vis[i] 初始化 n+1。
读 a[i]：若为 -1 则视为 n+1；否则若 a[i] != -1，设 vis[a[i]] = i（反向记录：位置 a[i] 的前驱是 i）。
建线段树。
对所有未处理的位置跑 dfs。
输出排列 p[1..n]
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 5e5+5;

ii t[N<<2];
#define lc (k<<1)
#define rc (k<<1|1)
void push_up(int k) { t[k] = max(t[lc], t[rc]); }

int vis[N];
void build(int k, int l, int r) {
    if (l == r) { t[k] = {vis[l], l}; return; }
    int mid = (l + r) >> 1;
    build(k<<1, l, mid); build(k<<1|1, mid + 1, r);
    push_up(k);
}
ii query(int k, int l, int r, int L, int R) {
    if (l > R || r < L) return {0, -1};//越界返回最小值
    if (l >= L && r <= R) return t[k];
    int mid = (l + r) >> 1;
    return max(query(lc, l, mid, L, R), query(rc, mid + 1, r, L, R));
}
void update(int k, int l, int r, int pos) {
    if (l == r) { t[k] = {0, -1}; return; }//单点置为最小值
    int mid = (l + r) >> 1;
    if (pos <= mid) update(lc, l, mid, pos);
    else update(rc, mid + 1, r, pos);
    push_up(k);
}

int n, p[N], a[N], cur(0);
void dfs(int u) {
    update(1, 1, n, u);
    if (int x = vis[u]; x <= n && !p[x]) dfs(x);
    for (; ;) {
        auto [fst, snd] = query(1, 1, n, 1, a[u]-1);
        if (fst <= u) break;
        dfs(snd);
    }
    p[u] = ++cur;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int main() {
    fast;
    rd(n);
    for (int i = 1; i <= n; ++i) vis[i] = n+1;
    for (int i = 1; i <= n; ++i) {
        rd(a[i]);
        if (a[i] != -1) vis[a[i]] = i;
        else a[i] = n+1;
    }
    build(1, 1, n);
    for (int i = 1; i <= n; ++i)
        if (!p[i]) dfs(i);
    for (int i = 1; i <= n; ++i) cout << p[i] << ' ';
    cout << '\n';
    return 0;
}