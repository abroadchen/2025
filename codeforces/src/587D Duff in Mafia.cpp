//
// Created by Psy.C on 2026/3/18.
//
/**
起点u、终点v、权重w、颜色c
dfn[i]: 节点i的访问时间戳
low[i]: 节点i能到达的最小时间戳
tot: 时间戳计数器
in[i]: 节点i是否在栈中
st[N]: Tarjan算法使用的栈
top: 栈顶指针
scc: 强连通分量编号
c[i]: 节点i所属的强连通分量
g[N]: 图的邻接表表示

初始化节点u的时间戳和low值
将u标记为在栈中，并压入栈
遍历节点u的所有邻居v
如果v未访问过，递归调用tarjan，并更新low值
如果v已在栈中，更新low值
如果dfn[u] == low[u]，说明找到了一个强连通分量
从栈中弹出直到u的所有节点，都属于同一个SCC

cnt: 编号计数器，从1开始（保证偶数为真，奇数为假）
tmp: 临时变量
m, n: 边数和点数
id[i]: 边i在2-SAT中的编号
vis[i]: 颜色i的访问状态
v[i]: 与点i相关的边集合
ans: 存储答案

清空图和相关数组
x: 权重阈值
t: 标志位，决定是否记录答案
重置Tarjan相关变量
如果边权大于x，则添加约束条件（反向边）
遍历每个节点i
检查是否有冲突的颜色约束
i1, i2: 记录同一颜色的两条边
如果没有冲突（所有边颜色都不同）
添加约束：在同一节点的边中只能选一个
如果有冲突（有同色边）
对于权重≤x且不是冲突边的边，添加约束
对冲突的两条边添加异或约束
清空访问标记
对所有未访问节点运行Tarjan
检查2-SAT约束：如果某个变量和其否定在同一个SCC中，返回false
如果t=0，只检查可行性
如果t=1，记录答案（选择SCC编号更大的变量）


x: 权重阈值，只有权重大于x的边才产生约束
t: 控制标志，0表示只检查可行性，1表示记录答案
清空图的邻接表和Tarjan相关数组
重置栈指针和强连通分量计数器
cnt = tmp: 恢复到初始的变量编号数量
如果边的权重大于x，则添加约束：(¬id[i]) → id[i]，即必须选择这条边
遍历节点i的所有关联边
vis[e[z].c]记录颜色为e[z].c的边
如果发现重复颜色（即同一节点上有两条相同颜色的边）：
i1, i2记录这两条冲突的边
如果已经有冲突记录，返回false（无解）
否则记录冲突的两条边
如果节点i没有颜色冲突（所有边颜色都不同）
使用中间变量确保节点i上最多选一条边：
第一个循环：创建约束确保最多选一条边
g[++cnt].push_back(id[z]): 新变量→选择边z
g[cnt].push_back(lst): 新变量→上一个新变量（传递性）
g[id[z]^1].push_back(lst): ¬(选择边z)→上一个新变量
第二个循环：反向验证约束
这样确保同一节点最多选一条边
如果有冲突（节点i上有同色边i1和i2）
对于权重≤x且不是冲突边的边z：添加¬选择z → 选择z（自环，强制不选）
对冲突边i1和i2添加异或约束：
id[i1] → ¬id[i2]: 选i1就不能选i2
¬id[i1] → id[i2]: 不选i1就必须选i2
id[i2] → ¬id[i1]: 选i2就不能选i1
¬id[i2] → id[i1]: 不选i2就必须选i1
清空颜色访问标记
对所有未访问的2-SAT变量运行Tarjan算法
检查2-SAT可行性：如果某个变量和其否定在同一个强连通分量中，说明矛盾，返回false
如果t=0（只检查），直接返回true
如果t=1（记录答案），当变量的SCC编号大于其否定的SCC编号时，选择该变量
返回true表示存在可行解
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
void minn(int& x, int y) { x = x < y ? x : y; }
constexpr int N = 5e5+5, inf = 1e9;

struct node { int u, v, w, c; } e[N];

int dfn[N], low[N], tot, in[N], st[N], top, scc, c[N];
vector<int> g[N];
void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    in[u] = 1; st[++top] = u;
    for (auto v : g[u]) {
        if (!dfn[v]) tarjan(v), minn(low[u], low[v]);
        else if (in[v]) minn(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        ++scc;
        int y;
        do {
            y = st[top--]; in[y] = 0;
            c[y] = scc;
        } while (y != u);
    }
}

int cnt = 1, tmp, m, n, id[N], vis[N];
vector<int> v[N], ans;
bool check(int x, int t) {
    for (int i = 2; i <= cnt; ++i) {
        g[i].clear();
        dfn[i] = in[i] = 0;
    }
    top = scc = 0; cnt = tmp;
    for (int i = 1; i <= m; ++i)
        if (e[i].w > x) g[id[i]^1].push_back(id[i]);
    for (int i = 1; i <= n; ++i) {
        int i1 = 0, i2 = 0;
        for (auto z : v[i]) {
            if (vis[e[z].c]) {
                if (i1 || i2) return 0;
                i1 = vis[e[z].c]; i2 = z;
            }
            vis[e[z].c] = z;
        }
        if (!i1) {
            int lst = 0;
            for (auto z : v[i]) {
                g[++cnt].push_back(id[z]);
                if (lst) g[cnt].push_back(lst), g[id[z]^1].push_back(lst);
                lst = cnt;
            }
            ranges::reverse(v[i]); lst = 0;
            for (auto z : v[i]) {
                g[++cnt].push_back(id[z]);
                if (lst) g[cnt].push_back(lst), g[id[z]^1].push_back(lst);
                lst = cnt;
            }
        } else {
            for (auto z : v[i])
                if (e[z].w <= x && z != i1 && z != i2)
                    g[id[z]^1].push_back(id[z]);
            g[id[i1]].push_back(id[i2]^1); g[id[i1]^1].push_back(id[i2]);
            g[id[i2]].push_back(id[i1]^1); g[id[i2]^1].push_back(id[i1]);
        }
        for (auto z : v[i]) vis[e[z].c] = 0;
    }
    for (int i = 2; i <= cnt; ++i)
        if (!dfn[i]) tarjan(i);
    for (int i = 1; i <= m; ++i)
        if (c[id[i]] == c[id[i]^1]) return 0;
    if (!t) return 1;
    for (int i = 1; i <= m; ++i)
        if (c[id[i]] > c[id[i]^1]) ans.push_back(i);
    return 1;
}

int a[N], k;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) id[i] = ++cnt, cnt++; tmp = cnt;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].u >> e[i].v >> e[i].c >> e[i].w;
        a[i] = e[i].c;//记录颜色用于离散化
        v[e[i].u].push_back(i); v[e[i].v].push_back(i);
    }
    sort(a + 1, a + 1 + m);
    k = unique(a + 1, a + 1 + m) - a - 1;
    for (int i = 1; i <= m; ++i)
        e[i].c = lower_bound(a + 1, a + 1 + k, e[i].c) - a;
    int l = 0, r = inf;
    if (!check(r + 1, 0)) { cout << "No"; return 0; }//检查最大值是否可行
    while (l < r) {//查找最小可行解
        if (int mid = (l + r) >> 1; check(mid, 0)) r = mid;
        else l = mid + 1;
    }
    check(l, 1);
    cout << "Yes\n";
    cout << l << ' ' << ans.size() << '\n';
    for (auto z : ans) cout << z << ' ';
    return 0;
}