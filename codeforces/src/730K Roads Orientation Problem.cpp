//
// Created by Psy.C on 2026/4/26.
//
/**
dfn[N]: DFS时间戳
low[N]: 能到达的最低时间戳
tim: 当前时间戳
stk[N]: Tarjan算法栈
top: 栈顶指针
fa[N]: 父节点数组
mp[N]: 邻接表，存储(邻接点, 边ID)对

寻找桥和割点
构建DFS树，记录父节点关系
p: 存储DFS访问序列
q[N]: 新图的邻接表
dfs: 深度优先搜索，将访问顺序存入p
ans: 存储最终路径答案
l: 存储从终点到起点的路径
n, m: 节点数和边数
in[N], out[N]: 入度和出度统计
tag[N]: 标记在主路径上的节点
vp[N]: 标记已使用的边

从起始点运行Tarjan算法
沿着父节点关系从终点回溯到起点
反转路径得到正确的起点到终点路径
对不在主路径上的节点构建辅助图
连接到其父节点和low值对应的节点
按主路径顺序对每个节点进行DFS
遍历DFS序列，构建最终路径
统计入度和出度
标记已使用的边
检查是否使用了所有边
检查除了起点和终点外是否有节点入度或出度为0
如有问题输出"No"，否则输出"Yes"和路径
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e6+7;

int dfn[N], low[N], tim, stk[N], top, fa[N];
vector<ii> mp[N];
void tarjan(int u) {
    dfn[u] = ++tim; low[u] = tim; stk[++top] = u;
    for (auto key: mp[u] | views::keys) {
        int v = key;
        if (!dfn[v]) {
            fa[v] = u; tarjan(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], dfn[v]);
    }
}

vector<int> p, q[N];
bool vis[N];
void dfs(int u) {
    p.push_back(u); vis[u] = 1;
    for (auto v : q[u])
        if (!vis[v]) dfs(v);
}

vector<ii> ans;
vector<int> l;
int n, in[N], out[N], m;
bool tag[N], vp[N];
void init() {
    p.clear(); ans.clear(); l.clear();
    for (int i = 1; i <= n; ++i) {
        mp[i].clear();
        dfn[i] = 0, low[i] = 0, fa[i] = 0;
        vis[i] = false; tag[i] = false;
        in[i] = 0, out[i] = 0;
        q[i].clear();
    }
    for (int i = 1; i <= m; ++i) vp[i] = 0;
    top = 0, tim = 0;
}

int T, st, ed, u[N], v[N];
int main() {
    fast;
    cin >> T;
    while (T--) {
        init();
        cin >> n >> m >> st >> ed;
        for (int i = 1; i <= m; ++i) {
            cin >> u[i] >> v[i];
            mp[u[i]].emplace_back(v[i], i);
            mp[v[i]].emplace_back(u[i], i);
        }
        tarjan(st);
        for (int i = ed; i; i = fa[i]) tag[i] = true, l.push_back(i);
        ranges::reverse(l);
        for (int i = n; i >= 1; --i) {
            int x = stk[i];
            if (!tag[x]) {
                q[fa[x]].push_back(x);
                q[stk[low[x]]].push_back(x);
            }
        }
        for (auto x : l) dfs(x);
        int cnt = 0;
        for (auto x : p) {
            if (x == ed) break;
            for (auto [fst, snd] : mp[x])
                if (!vp[snd]) {
                    cnt++;
                    ans.emplace_back(x, fst);
                    in[fst]++; out[x]++;
                    vp[snd] = true;
                }
        }
        bool fl = false;
        for (int i = 1; i <= n; ++i)
            if ((i != st && !in[i]) || (i != ed && !out[i])) {
                fl = true; break;
            }
        if (cnt != m || fl) cout << "No\n";
        else {
            cout << "Yes\n";
            for (auto [fst, snd] : ans)
                cout << fst << ' ' << snd << '\n';
        }
    }
    return 0;
}