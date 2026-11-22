//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
N：矩阵边长上限。
M：n·m 个格子（节点）数量上限，也是 LCT 节点数组大小。
fa[u]：LCT 中节点 u 的父节点。
ch[2][M]：LCT 的左右孩子（ch[0][u] 左、ch[1][u] 右）
判断 u 是不是其所在 Splay 的根。如果 u 不是某个孩子（左或右）的引用，说明 u 是树根或虚边父节点，视为"已经是 Splay 根"。LCT 中只有"不是 Splay 根"的节点才需要被 splay
Splay 的单次旋转，把 u 旋转到其父 y 的位置：

y = fa[u] 父，z = fa[y] 祖父。
k = (ch[1][y]==u)：u 是 y 的右孩子则为 1，否则 0。
w = ch[k^1][u]：u 的"另一边"孩子（若 u 是右孩子则取 u 的左孩子）。
若 y 不是 Splay 根，则用 u 替换 z 的孩子位置。
重新连接 y 与 u 的孩子 w、u 与 y。
更新 fa 指针
用于 LCT 的 make_root（换根）操作，给节点打上"左右孩子交换"的懒标记（rv[u] 异或 1），同时立即交换左右孩子
如果 u 有反转标记，则把标记传给两个子节点并清除自己的标记
把 u 转到其 Splay 的根：

收集路径：从 u 向上沿 fa 一路收集所有节点到栈 st 中（用 nr 判断是否到顶）。
自顶向下下传：因为 splay 涉及旋转，必须先把从上到下的反转标记 pd 全部下传。
双旋：标准 splay 双旋（zig-zig 先旋父 y，zig-zag 先旋 u），直到 u 成为 Splay 根
LCT 核心操作：建立从根到 u 的实链。每次 splay(u)，把右孩子设为 y（断开原来的右链），然后 u 跳到 fa[u]
把 u 变成整棵树的根：先 access(u) 让 u 在实链顶端，splay 后打反转标记即可换根
把 x 到 y 的路径抽成一条以 y 为 Splay 根的实链（分离出 x-y 路径）。常用于查询或 cut
找 u 所在辅助树（Splay）的最左节点（即整棵 LCT 树的树根）：access+splay 后，一直沿左儿子走下去（最左就是根，因为 kept 反转标记需 pd 下传），最后 splay 一次
把 x 和 y 连一条边：把 x 设为根，然后 fa[x] = y。
删除 x-y 之间的边：split 把 x-y 变成一条实链（y 为根），此时 x 是 y 的左孩子，直接把两边断开置 0。

tr[u]：区间最小值（即区间内最小的"覆盖深度"）。
sum[u]：最小值出现的位置个数
统计该区间最小值及其出现次数，等于取左右子最小值，并把最小值的 sum 合并。
区间加懒标记下传：给两个子节点的懒标记和 tr 值同加 lz，再清空自己。
建树：初始每个位置覆盖深度为 0，最小值次数 = 区间长度（全部相同为 0）。
对区间 [L,R] 全部加 w（标准线段树区间加 + 懒标记）。
查询区间 [L,R] 的最小值 fst 和其出现个数 snd（用全局变量 fst/snd 收集）。这是用于统计答案的。
dx[i], dy[i]：数值 i 对应的在矩阵中的坐标。
d：四方向。
lb, rb：滑动窗口的左右端点（数值窗口）。
a[i][j]：矩阵数值。
判断"如果加入下一个格子 rb+1 会不会形成环"：

遍历 rb+1 的四个邻居。
若邻居在窗口 [lb, rb] 内，记录它所在连通块树根。
若存在两个邻居属于同一连通块，则加入 rb+1 会成环，返回 0（false）。
否则返回 1（可以加入）。
本质：新格子连接的所有"已在窗口内的邻居"若属于同一棵树，就会形成环（因为新格子会把它们连起来）。如果分布在不同的树/孤立节点，则仍是森林
读入矩阵，记录每个数值的坐标 dx/dy。

初始化线段树：值域 1..n*m，初始全部深度 0，位置 1 的深度 +1（upd(...,1,1,1)）。

滑动窗口扩展右端点 rb（从 1 到 n·m）：

while 循环检查：若当前窗口 [lb, rb] 加上 rb+1 会成环（!check()）且 lb < rb，则不断 右移左端点 lb（移除左端格子 lb），并 cut 掉它与其邻居之间的边——即删除格子的树边。这是为了让窗口保持无环。
扩展右端点：++rb，给当前窗口的位置（lb 到 rb）整体深度 +1（线段树 upd(1,1,n*m,lb,rb,1)）。
加入新节点 rb：把 rb 与它所有邻居中的"已在窗口内"的格子连边 lnk，并在线段树上对 [lb, a[x][y]] 深度减 1（表示这些格子的"重叠覆盖"减少了一个——因为新增了一个连接，让它们更"靠拢"了）。
统计贡献：查询区间 [lb, rb] 的最小值 fst 及出现次数 snd。如果 fst == 1，说明存在"最小覆盖深度=1"的位置，则把 snd 累加到答案 ans。
设计思想（讲清楚为什么线段树这样更新）：
对每个左端点 lb，需要统计"最小的右边位置 rb' 使得 [lb, rb'] 合法"。线段树维护每个位置作为"左端点"时，为保持无环还需覆盖的最小深度。加入新格子和删除格子时，通过整体 +1 或 -1 来反映。当区间内最小值恰为 1 时，说明该左端点正好需要一个"单位"才能达成无环，此时对应的合法右端点计数就是 snd。
输出 ans（答案包含了 lb=rb=1 的情况已初始为 1）
*/

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 1010, M = 2e5+10;

int fa[M], ch[2][M];
inline bool nr(int u) { return ch[0][fa[u]] == u || ch[1][fa[u]] == u; }
inline void rot(int u) {
    int y = fa[u], z = fa[y], k = ch[1][y] == u, w = ch[k^1][u];
    if (nr(y)) ch[ch[1][z]==y][z] = u;
    ch[k][y] = w, ch[k^1][u] = y;
    if (w) fa[w] = y;
    fa[u] = z, fa[y] = u;
}
#define lc ch[0][u]
#define rc ch[1][u]
bool rv[M];
inline void rev(int u) { rv[u] ^= 1, swap(lc, rc); }
inline void pd(int u) { if (rv[u]) rev(lc), rev(rc), rv[u] = 0; }

int st[M], tp;
inline void splay(int u) {
    int y = u, z;
    for (st[tp=1] = y; nr(y); st[++tp] = y = fa[y]) {}
    for (; tp; pd(st[tp--])) {}
    for (; nr(u); rot(u)) {
        y = fa[u], z = fa[y];
        if (nr(y)) rot((ch[0][y] == u) ^ (ch[0][z] == y) ? u : y);
    }
}
inline void access(int u) { for (int y = 0; u; u = fa[y=u]) splay(u), rc = y; }
inline void mkrt(int u) { access(u); splay(u); rev(u); }
inline void split(int x, int y) { mkrt(x), access(y), splay(y); }
inline int findrt(int u) {
    access(u); splay(u);
    for (; lc; pd(u), u = lc) {}
    splay(u);
    return u;
}
inline void lnk(int x, int y) { mkrt(x), fa[x] = y; }
inline void cut(int x, int y) { split(x,y), fa[x] = ch[0][y] = 0; }
inline int min(const int &x, const int &y) { return x < y ? x : y; }

int sum[M<<2], tr[M<<2];
void push_up(int u) {
    sum[u] = 0, tr[u] = min(tr[u<<1], tr[u<<1|1]);
    if (tr[u] == tr[u<<1]) sum[u] += sum[u<<1];
    if (tr[u] == tr[u<<1|1]) sum[u] += sum[u<<1|1];
}

int lz[M<<2];
void push_down(int u) {
    if (!lz[u]) return;
    lz[u<<1] += lz[u], lz[u<<1|1] += lz[u];
    tr[u<<1] += lz[u], tr[u<<1|1] += lz[u];
    lz[u] = 0;
}
void build(int u, int l, int r) {
    tr[u] = 0, sum[u] = r-l+1;
    if (l >= r) return;
    int mid = (l+r)>>1;
    build(u<<1, l, mid); build(u<<1|1, mid+1, r);
}
void upd(int u, int l, int r, int L, int R, int w) {
    if (L <= l && r <= R) { tr[u] += w, lz[u] += w; return; }
    int mid = (l+r)>>1;
    push_down(u);
    if (L <= mid) upd(u<<1, l, mid, L, R, w);
    if (R > mid) upd(u<<1|1, mid+1, r, L, R, w);
    push_up(u);
}

int fst, snd;
void qry(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        if (fst > tr[u]) fst = tr[u], snd = 0;
        if (fst == tr[u]) snd += sum[u];
        return;
    }
    int mid = (l+r)>>1;
    push_down(u);
    if (L <= mid) qry(u<<1, l, mid, L, R);
    if (R > mid) qry(u<<1|1, mid+1, r, L, R);
}

int dx[M], dy[M], d[][2] = {{0,1},{1,0},{-1,0},{0,-1}};
int lb = 1, rb = 1, a[N][N];
int n, m;
bool check() {
    static int t[5];
    int len = 0;
    for (auto &i : d) {
        int x = dx[rb+1]+i[0], y = dy[rb+1]+i[1];
        if (!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb) continue;
        t[++len] = findrt(a[x][y]);
    }
    sort(t+1,t+len+1);
    rep(i,len-1) if (t[i] == t[i+1]) return 0;
    return 1;
}

ll ans = 1;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) rep(j,m) cin >> a[i][j], dx[a[i][j]] = i, dy[a[i][j]] = j;
    build(1,1,n*m); upd(1,1,n*m,1,1,1);
    while (rb < n* m) {
        for (; lb < rb && !check(); ++lb) for (auto &i : d) {
            int x = dx[lb]+i[0], y = dy[lb]+i[1];
            if (!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb) continue;
            cut(lb, a[x][y]);
        }
        ++rb, upd(1,1,n*m,lb,rb,1);
        for (auto &i : d) {
            int x = dx[rb]+i[0], y = dy[rb]+i[1];
            if (!x || !y || x > n || y > m || a[x][y] < lb || a[x][y] > rb) continue;
            lnk(rb, a[x][y]), upd(1,1,n*m,lb,a[x][y],-1);
        }
        fst = M, snd = 0, qry(1,1,n*m,lb,rb);
        if (fst == 1) ans += snd;
    }
    cout << ans << '\n';
    return 0;
}