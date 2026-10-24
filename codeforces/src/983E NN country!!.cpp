//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
树状数组（Fenwick）‍。
low_bit：返回最低位 1。
add(x, y)：在下标 x 处加 y。
query(x, y)：求下标在 [x, y] 区间的和（前缀差分 sum(y) - sum(x-1)）
链式前向星存图。adde(u,v) 添加一条 u→v 的边
fa[x][i]：x 向上跳 2^i 步的祖先（倍增表，深度 21 足够 4e5）。
dep[x]：深度。
dfn[x]：DFS 进入序（给每个点分配编号，从 1 开始）。
bot[x]：x 子树中最大的 dfn（因为 DFS 序中子树连续，故 [dfn[x], bot[x]] 就是 x 的子树区间）。
递归访问子结点（跳过父结点）
标准倍增 LCA：
让深的点跳到与浅的同深度。
若相同则返回。
一起向上跳到 LCA 下方，返回 fa[x][0]
f[x][0] 表示"在 x 的子树内（含自己）被标记过的、深度最小（最靠近根）的那个跳点"。
遍历子树，收集子结点的 f[y][0]，保留深度最小的那个赋给 f[x][0]。
用于后续把"每条给定路径的 LCA"标记向子树传播
读入 n，然后读 n-1 条边（i 与 v 连边）构成树。
dfs(1, 0) 做倍增、dfn、bot 预处理（以 1 为根）
循环读入 m 条"给定路径" (x,y)。
按 dfn 排序使 dfn[x] <= dfn[y]。
计算其 LCA。
把 f[x][0] 和 f[y][0] 更新为"深度更小的 LCA"（若当前 f 为空或 lca 更浅）。即每个端点上记录"能到达该点的给定路径的 LCA 中最浅的那个"。
同时把 (dfn[x], dfn[y]) 作为一条"二维点"记录到 p（f=0 标记为"数据点"而非"查询点"，稍后用于 BIT 离线
dfs2(1)：把每条路径的 LCA 标记向子树传播（自底向上）。
若 f[i][0] == i（自己标记自己，即自己是某路径的 LCA 但无意义）则清零。
对 f 数组做倍增表：f[j][i] = 向上跳 2^i 层的跳点，用于快速向上跳
对每个询问 (x,y)：

若 x==y（同点，路径长度 0），ans=0，跳过。
用倍增把 x、y 分别向上跳到"给定路径所能覆盖的最深跳点范围内"：只要 f[x][j] 存在且深度大于 lca，就跳上去并累加步数 2^j 到 ans[i]。这一步相当于"用给定路径快速拼接覆盖询问路径的上行段"。
若跳完后某端 f[x][0] 为空（x 不再是 lca 却没有给定路径向上覆盖），说明无法覆盖，ans[i] = -1，跳过。
若 lca == x || lca == y（lca 是其中一个端点），只需再加 1（被覆盖的段数）。
否则（lca 在中间，需要两条给定路径分别在 x 侧和 y 侧覆盖后汇合），ans += 2，并在 p 中构造一个二维区间和查询：
{bot[x], bot[y], 1, 1, i}
{dfn[x]-1, bot[y], -1, 1, i}
{bot[x], dfn[y]-1, -1, 1, i}
{dfn[x]-1, dfn[y]-1, 1, 1, i}
这是典型的二维前缀和容斥四角写法，用来统计"子矩形 [dfn[x], bot[x]] × [dfn[y], bot[y]]"内有多少条给定路径端点（即两条路径的子树相交点对数量）。
其中 x、y 此时已被跳到了 LCA 下的子结点（x 在 lca 的某子树上、y 在另一子树上），因此两个子树区间不相交，用二维数点判断"给定路径端点是否分别落在两个子树的笛卡尔积内"。
cmp 按第一维 x 排序（x 相同时查询点在后）。
离线扫描 + BIT 二维数点：
f==0 的是给定路径的数据点 (dfn[x], dfn[y])，扫到它就 add(dfn[y], 1)（在 y 维树状数组中 +1）。
f==1 的是查询点，用 query(1, p[i].y) 求 y 维 ≤ p[i].y 的点数和，乘以容斥系数 k（±1）累加到 res[id]。
这是把二维区间和内点个数用"按 x 排序 + BIT 维护 y"的经典离线方法求出。
最后对每个询问输出 ans[i] - (res[i] > 0)：res[i] 是该询问对应二维矩形内给定路径端点对数量，(res[i]>0) 转成 0/1 布尔，扣除修正项
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 4e5+5;

int low_bit(int x) { return x & -x; }

int tr[N], n;
void add(int x, int y) { for (int i = x; i <= n; i += low_bit(i)) tr[i] += y; }
int query(int x, int y) {
    int t = 0;
    for (int i = y; i; i -= low_bit(i)) t += tr[i];
    for (int i = x-1; i; i -= low_bit(i)) t -= tr[i];
    return t;
}

struct edge { int val, nxt; } e[N];

int cnt, head[N];
void adde(int u, int v) { e[++cnt].val = v; e[cnt].nxt = head[u]; head[u] = cnt; }

int fa[N][22], dep[N], dfn[N], tim, bot[N];
void dfs(int x, int ff) {
    fa[x][0] = ff; dep[x] = dep[ff] + 1; dfn[x] = ++tim;
    for (int i = 1; i <= 21; i++) fa[x][i] = fa[fa[x][i-1]][i-1];
    for (int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].val;
        if (y != ff) dfs(y, x);
    }
    bot[x] = tim;
}

int LCA(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 21; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if (x == y) return x;
    for (int i = 21; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int f[N][22];
void dfs2(int x) {
    for (int i = head[x]; i; i = e[i].nxt) {
        int y = e[i].val;
        if (y != fa[x][0]) {
            dfs2(y);
            if (!f[x][0]||(f[y][0]&&dep[f[y][0]]<dep[f[x][0]]))
                f[x][0] = f[y][0];
        }
    }
}
struct node { int x, y, k, f, id; } p[N<<2];
bool cmp(const node &x, const node &y) {
    return x.x == y.x ? x.id < y.id : x.x < y.x;
}

int m, tot, q, ans[N], res[N];
signed main() {
    fast;
    cin >> n;
    for (int i = 2, v; i <= n; i++) {
        cin >> v; adde(i, v); adde(v, i);
    }
    dfs(1, 0);
    cin >> m;
    for (int i = 1, x, y; i <= m; i++) {
        cin >> x >> y;
        if (dfn[x] > dfn[y]) swap(x, y);
        int lca = LCA(x, y);
        if (!f[x][0] || dep[lca] < dep[f[x][0]]) f[x][0] = lca;
        if (!f[y][0] || dep[lca] < dep[f[y][0]]) f[y][0] = lca;
        p[++tot] = {dfn[x], dfn[y], 0, 0, 0};
    }
    dfs2(1);
    for (int i = 1; i <= n; i++) if (f[i][0] == i) f[i][0] = 0;
    for (int i = 1; i <= 21; i++) for (int j = 1; j <= n; j++) f[j][i] = f[f[j][i-1]][i-1];
    cin >> q;
    for (int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        if (dfn[x] > dfn[y]) swap(x, y);
        int lca = LCA(x, y);
        if (x == y) { ans[i] = 0; continue; }
        for (int j = 21; j >= 0; j--)
            if (f[x][j]&&dep[f[x][j]]>dep[lca])
                x = f[x][j], ans[i] += 1<<j;
        for (int j = 21; j >= 0; j--)
            if (f[y][j]&&dep[f[y][j]]>dep[lca])
                y = f[y][j], ans[i] += 1<<j;
        if ((!f[x][0]&&x!=lca)||(!f[y][0]&&y!=lca)) { ans[i] = -1; continue; }
        if (lca == x || lca == y) ans[i]++;
        else {
            ans[i] += 2;
            p[++tot] = {bot[x], bot[y], 1, 1, i};
            p[++tot] = {dfn[x]-1, bot[y], -1, 1, i};
            p[++tot] = {bot[x], dfn[y]-1, -1, 1, i};
            p[++tot] = {dfn[x]-1, dfn[y]-1, 1, 1, i};
        }
    }
    sort(p+1, p+tot+1, cmp);
    for (int i = 1; i <= tot; i++) {
        if (p[i].f == 0) add(p[i].y, 1);
        else res[p[i].id] += query(1, p[i].y)*p[i].k;
    }
    for (int i = 1; i <= q; i++) cout << ans[i]-(res[i]>0) << '\n';
    return 0;
}