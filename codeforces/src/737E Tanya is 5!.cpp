//
// Created by Psy.C on 2026/4/28.
//
/**
价格p和编号id
边的两个端点u和v
z数组存储每种物品的数量
cmp1: 按照z数组降序排序
cmp2: 按照id升序排序
mt数组记录匹配关系
col数组记录边的颜色
s集合存储可用颜色

找到与节点u用颜色x连接的边，获取另一端点v
清除原来的匹配关系
如果v已经有颜色y的匹配，则递归调用
否则更新v的可用颜色集合
设置新的匹配关系并更新颜色

n: 节点数
m: 物品种类数
b: 预算
c[N][N]: 二维数组存储每个节点对每种物品的需求
r[N]: 每个节点的总需求
ans: 最终答案
pos[N]: 位置数组
id[N<<1]: id映射数组
tot: 计数器
sum[N]: 每种物品已分配数量
cnt: 边计数器
by[N]: 标记是否购买某种物品

读取n, m, b
读取每种物品的价格p，并设置其id
对于每个节点，读取它需要几种物品及数量
计算每个节点的总需求r[i]和每种物品的总需求z[j]
更新ans为最大节点需求
按照每种物品的总需求降序排列
贪心地购买能买的物品（按价格）
更新ans为最大值：已购买物品需求向上取整，未购买物品全需满足
为每种物品设置位置
如果已购买，在额外设置一个位置
按id排序恢复顺序
为每个需求构建边
根据是否购买以及当前数量决定连接哪个虚拟节点
为所有节点初始化可用颜色集合
对每条边进行图着色
取两端节点的第一个可用颜色
如果目标节点已有该颜色的匹配，执行DFS调整
建立新的匹配关系并更新颜色
输出最小颜色数ans
输出每种物品是否购买的标记
输出边总数
输出每条边的详细信息（起始节点、物品ID、颜色、权重）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 50, M = 1e6+7, K = 1e5+7;

struct node {
    int p, id;

} ch[N];
struct edge { int u, v; } e[M];

int z[N];
bool cmp1(node x, node y) { return z[x.id] > z[y.id]; }
bool cmp2(node x, node y) { return x.id < y.id; }

int mt[N<<1][K], col[M];
set<int> s[N<<1];
void dfs(int u, int x, int y) {
    int id = mt[u][x], v = e[id].u == u ? e[id].v : e[id].u;
    mt[u][x] = mt[v][x] = 0;
    if (mt[v][y]) dfs(v, y, x);
    else s[v].insert(x), s[v].erase(y);
    mt[v][y] = mt[u][y] = id, col[id] = y;
}

int n, m, b, c[N][N], r[N], ans, pos[N], id[N<<1], tot, sum[N], cnt;
bool by[N];
int main() {
    fast;
    cin >> n >> m >> b;
    for (int i = 1; i <= m; ++i) cin >> ch[i].p, ch[i].id = i;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        for (int j = 1, y; j <= x; ++j)
            cin >> y >> c[i][y];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            r[i] += c[i][j], z[j] += c[i][j];
    for (int i = 1; i <= n; ++i) ans = max(ans, r[i]);
    sort(ch + 1, ch + m + 1, cmp1);
    for (int i = 1; i <= m; ++i)
        if (ch[i].p <= b) b -= ch[i].p, by[ch[i].id] = true;
    for (int i = 1; i <= m; ++i)
        ans = max(ans, by[i] ? (z[i]+1)/2 : z[i]);
    for (int i = 1; i <= m; ++i) {
        pos[i] = ++tot, id[tot] = i;
        if (by[i]) id[++tot] = i;
    }
    sort(ch + 1, ch + m + 1, cmp2);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            while (c[i][j]--) {
                sum[j]++;
                if (!by[j]) e[++cnt] = {i, pos[j]+n};
                else if (sum[j] <= z[j]/2) e[++cnt] = {i, pos[j]+n};
                else e[++cnt] = {i, pos[j]+1+n};
            }
    for (int i = 1; i <= n+tot; ++i)
        for (int j = 1; j <= ans; ++j) s[i].insert(j);
    for (int i = 1; i <= cnt; ++i) {
        int u = e[i].u, v = e[i].v, c1 = *s[u].begin(), c2 = *s[v].begin();
        if (mt[v][c1]) dfs(v, c1, c2), s[v].erase(c2);
        mt[u][c1] = mt[v][c1] = i, col[i] = c1;
        s[u].erase(c1), s[v].erase(c1);
    }
    cout << ans << '\n';
    for (int i = 1; i <= m; ++i) cout << by[i];
    cout << '\n';
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i)
        cout << e[i].u << ' ' << id[e[i].v-n] << ' '  << col[i] - 1 << ' ' << 1 << '\n';
    return 0;
}