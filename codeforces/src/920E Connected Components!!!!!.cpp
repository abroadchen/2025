//
// Created by Psy.C on 2026/10/14.
//
/**
e[u]：原图 u 的邻居列表（无向，add 两次）。
f[i]：并查集父节点；sz[i]：连通块大小
路径压缩 find。
merge：按编号合并（小的那个作为父，便于按序遍历区间），累加大小。
关键：find(l) 会把一个"已合并区间"的代表定位到区间最左端的根，从而可以跳过整个已合并段——这是把区间合并加速到 O(n α) 的核心
初始化 DSU
读入 n、m、所有边；邻居列表排序（下面按序扫描区间需要）
第一趟循环——通过"跳过非邻居区间"建立合并关系：
solve(l, r)（见下）把区间 [l,r] 内所有与 i 不相邻（即补图中的邻居）的点合并到同一个连通块
从 find(l)（可能已合并区间的代表）开始，把 [l,r] 内所有 find 出来的根依次 merge，从而把这段"补图连通"的区间合成一个块
若 e[i] 为空（孤立点）‍：它和除自己外的所有点在补图里都相连。因此把 [1,i-1] 和 [i+1,n] 分别整个合并，然后 break（孤立点只有一个时直接并掉两侧，几乎确定整体连成一个补图分量）。
否则把邻居列表之间的"空隙区间"（即非邻居的连续段）逐一 solve：
开头空隙 [1, e[i][0]-1]；
若 i 在这个空隙里，则把它拆成 [l, i-1] 和 [i+1, r] 两段分别 solve（避免把 i 自己并进集合，因为 i 与自己是同一补图块的还不确定，其实主要排除自环逻辑）；
每两个相邻邻居之间空隙 [e[i][j-1]+1, e[i][j]-1]；
末尾空隙 [e[i][len-1]+1, n]。
注意：此循环里"i 是否与空隙段相连"是通过"i 不是 e[i] 里邻居"来保证的——因为空隙段里的点都不是 i 的邻居，所以在补图里 i 与它们相连，故这些段应并入 i 所在的块。而 solve 内部用 find 跳过已合并部分，保证线性复杂度
这一步补充处理第一趟可能漏掉的点 i 自身的合并：
对孤立点：把它并入邻点（数值上相邻的点）的块——因为孤立点在第一趟里已与整个补图连通，这里把它并到相邻顶点即可与全局连通。
if (e[i][0] > 1) merge(1, i)：若 1 不是 i 的邻居，则补图里 1 与 i 相连，并起来。
对每个邻居空隙 e[i][j]-e[i][j-1]>1（中间有空缺点），把 i 与这个空隙点 e[i][j]-1 合并。
这一趟的目的：确保每个点 i 自身也通过"它与某非邻居相连"被接入正确的补图分量，因为第一趟主要按区间合并、可能没把"点本身"挂进去
遍历所有点，取其 DSU 根，用 vis 去重，收集每个分量的 sz。
输出分量个数 num，再按升序输出每个分量大小

建图 + 排序邻接表	便于线性扫描"非邻居区间"
第一趟 solve	把"与 i 不相邻的连续段"整体合并成补图连通块（利用 find 跳段加速）
第二趟 merge	把每个点 i 自身接入补图分量（孤立点 + 空隙点）
DSU 统计	求各补图连通分量大小并升序输出
复杂度：每个点的邻居区间被扫描有限次，solve 中因 find 跳段、每个元素最多被并一次，总近似 O(n log n)（排序） + O(n α)（DSU），适合 n≤2e5
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;
constexpr int N = 2e5+5;

vector<int> e[N];
void add(int u, int v) { e[u].push_back(v); }

int f[N], n, sz[N];
void init() {
    for (int i = 1; i <= n; ++i)
        f[i] = i, sz[i] = 1;
}

int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (x > y) swap(x, y);
    f[x] = y, sz[y] += sz[x];
}

void solve(int l, int r) {
    int x = find(l), y;
    for (int i = x+1; i <= r; ++i) {
        y = find(i); merge(x, y); x = y;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m, ans[N], num;
bool vis[N];
int main() {
    fast;
    n = rd(), m = rd(); init();
    rep(i,1,m) {
        int u = rd(), v = rd();
        add(u, v); add(v, u);
    }
    rep(i,1,n) ranges::sort(e[i]);
    int l, r, len, pos;
    rep(i,1,n) {
        if (e[i].empty()) {
            if (1 < i-1) solve(1, i-1);
            if (i+1 < n) solve(i+1, n);
            break;
        }
        l = 1, r = e[i][0]-1, len = e[i].size();
        if (l <= i && i <= r) {
            int t = r; r = i-1;
            if (l < r) solve(l, r);
            l = i+1, r = t;
        }
        if (l < r) solve(l, r);
        rep(j,1,len-1) {
            l = e[i][j-1]+1, r = e[i][j] - 1;
            if (l < r) solve(l, r);
        }
        if (e[i][len-1] == n) l = r = n;
        else l = e[i][len-1]+1, r = n;
        if (l < r) solve(l, r);
    }
    rep(i,1,n) {
        if (e[i].empty()) {
            if (i == n) merge(i, i-1); else merge(i, i+1);
            continue;
        }
        if (e[i][0] > 1) merge(1, i);
        rep(j,1,e[i].size()-1) if (e[i][j]-e[i][j-1] > 1) merge(i, e[i][j]-1);
    }
    rep(i,1,n) {
        int x = find(i);
        if (!vis[x]) { ans[++num] = sz[x]; vis[x] = 1; }
    }
    cout << num << '\n';
    sort(ans+1, ans+num+1);
    rep(i,1,num) cout << ans[i] << ' ';
    return 0;
}