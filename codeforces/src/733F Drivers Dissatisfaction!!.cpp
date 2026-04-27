//
// Created by Psy.C on 2026/4/27.
//
/**
权重w、费用c、起点u、终点v、编号id
f[N][22]：倍增数组，f[x][i]表示x节点向上2^i步到达的节点
d[N][22]：d[x][i]表示从x到其2^i祖先路径上的最大边权
dep[N]：节点深度数组
g[N]：邻接表，存储树的结构
构建倍增数组：f[x][i] = f[f[x][i-1]][i-1]
构建路径最大边权：d[x][i] = max边权(f[x][i-1]和d[f[x][i-1]][i-1])
遍历邻接表，构建树结构，设置父子关系和深度
b[i] = 2^i
如果x深度小于y，交换x和y
让x和y处于同一深度
二进制拆分跳跃，找到LCA
查询从x到y路径上的最大边权
利用倍增数组跳跃查询路径上的最大值

n：节点数，m：边数
C：当前最小费用，初始化为无穷大
bf[N]：布尔数组，标记是否在MST中
num：当前最小费用边的索引
bb[N]：输出标记数组
pri[N]：价格数组
S：预算，tot：总权重，ans：答案

Kruskal算法构建MST：检查每条边，如果不连通就加入MST
构建邻接表表示的树
标记MST中的边
更新最小费用和对应的边
累加MST的总权重
输入预算S
计算初始答案：总权重-预算/最小费用
从节点1开始DFS构建倍增数组
遍历所有费用小于当前最小费用的边
对每条这样的边，找到它在MST上形成的环中的最大边
计算替换后的总成本
如果更优就更新答案
输出最终答案
标记在最优解中的边
设置价格：如果是最小费用边，价格为权重-预算/费用；否则就是权重
按要求格式输出所有选中的边及其价格



dl：被删除的边（Deleted edge）的索引
pr：费用最优边（Price-optimal edge）的索引
num：当前费用最小的边索引
bf[]：布尔数组，标记边是否在当前MST中
t：在当前环中权重最大的边
i：当前考虑加入的新边
tmp：替换后的总成本

1. bf[dl] = 1; bf[dl=t] = 0;
第一部分：bf[dl] = 1;
将之前被移除的边dl重新标记为在MST中
在上一次迭代中，边dl被从MST中移除了（设置为0），现在要恢复它
第二部分：bf[dl=t] = 0;
这是一个复合赋值操作：先执行dl = t，然后执行bf[dl] = 0
dl = t：将变量dl更新为t（即找到的环中最大权重边的索引）
bf[t] = 0：将这条最大权重边从MST中移除（标记为0）
注意：这里dl的值发生了改变
2. bf[pr] = 0; pr = i;
第一部分：bf[pr] = 0;
将之前标记为最小费用边的边从MST中移除
pr记录的是上一轮迭代中的最小费用边
第二部分：pr = i;
更新pr变量为当前考虑的新边索引i
3. num = i; bf[i] = 1;
第一部分：num = i;
更新当前最小费用边的索引为i
num变量跟踪当前MST中费用最小的边
第二部分：bf[i] = 1;
将当前新加入的边i标记为在MST中
表示这条边现在是MST的一部分
4. ans = tmp;
更新全局最优答案为当前计算出的更优值tmp

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define ll long long
using namespace std;
constexpr int N = 2e5+7, inf = 21e8;

struct node {
    int w, c, u, v, id;
    bool operator<(const node &o) const {
        return w < o.w;
    }
} a[N];

int fa[N];
int find(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

///比较两条边的权重，返回权重更大的边的索引
int mxx(int x, int y) {
    if (a[x].w > a[y].w) return x;
    return y;
}

int f[N][22], d[N][22], dep[N];
vector<ii> g[N];
void dfs(int x) {
    for (int i = 1; i <= 20; ++i)
        f[x][i] = f[f[x][i-1]][i-1];
    for (int i = 1; i <= 20; ++i)
        d[x][i] = mxx(d[x][i-1], d[f[x][i-1]][i-1]);
    for (auto [fst, snd] : g[x]) {
        int y = fst, w = snd;
        if (y == f[x][0]) continue;
        f[y][0] = x, d[y][0] = w;
        dep[y] = dep[x] + 1;
        dfs(y);
    }
}

int b[22];
int lcq(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int t = dep[x] - dep[y];
    for (int i = 0; i <= 20; ++i)
        if (t&b[i]) x = f[x][i];
    for (int i = 20; i >= 0; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return x == y ? x : f[x][0];
}

int query(int x, int y) {
    int t = dep[x] - dep[y], ret = 0;
    for (int i = 0; i <= 20; ++i)
        if (t&b[i]) {
            ret = mxx(ret, d[x][i]);
            x = f[x][i];
        }
    return ret;
}

int n, m, C = inf, bf[N], num, bb[N], pri[N];
ll S, tot, ans;
int main() {
    fast;
    b[0] = 1;
    for (int i = 1; i <= 20; ++i) b[i] = b[i-1]<<1;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i].w;
    for (int i = 1; i <= m; ++i) cin >> a[i].c;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i].u >> a[i].v;
        a[i].id = i;
    }
    sort(a + 1, a + m + 1);
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i <= m; ++i) {
        int x = a[i].u, y = a[i].v, r1 = find(x), r2 = find(y);
        if (r1 != r2) {
            fa[r1] = r2;
            g[x].emplace_back(y, i);
            g[y].emplace_back(x, i);
            bf[i] = 1;
            if (a[i].c < C) { C = a[i].c; num = i; }
            tot += a[i].w;
        }
    }
    cin >> S;
    ans = tot - S/C; dfs(1);
    int dl = 0, pr = 0;
    for (int i = 1; i <= m; ++i) {
        if (a[i].c < C) {
            int x = a[i].u, y = a[i].v, z = lcq(x, y),
            t = mxx(query(x, z), query(y, z));
            ll tmp = tot - a[t].w + a[i].w;
            tmp -= S/a[i].c;
            if (tmp < ans) {
                bf[dl] = 1; bf[dl=t] = 0;
                bf[pr] = 0; pr = i; num = i; bf[i] = 1;
                ans = tmp;
            }
        }
    }
    cout << ans << '\n';
    for (int i = 1; i <= m; ++i) {
        if (bf[i]) {
            bb[a[i].id] = 1;
            if (num == i) pri[a[i].id] = a[i].w - S/a[i].c;
            else pri[a[i].id] = a[i].w;
        }
    }
    for (int i = 1; i <= m; ++i)
        if (bb[i]) cout << i << ' ' << pri[i] << '\n';
    return 0;
}