//
// Created by Psy.C on 2026/3/14.
//
/**
f[N][20]: 倍增数组，用于LCA查询
dep[N]: 深度数组
up[N], down[N]: 差分数组，up向上累加，down向下累加
e[N]: 邻接表，存储树的边
f[u][0] = fa: 设置父亲节点
dep[u] = dep[fa] + 1: 设置深度
倍增预处理：f[u][i] = f[f[u][i-1]][i-1]，即u的2^i祖先
遍历子节点，递归建树
后序遍历：先处理子节点，再汇总到父节点

~i等价于i >= 0，从高位到低位遍历
将x调整到不低于y的深度
第一个循环：跳跃使x和y在同一高度
如果x已经是y的祖先，直接返回
第二个循环：同时向上跳跃，直到最近公共祖先的子节点
返回父亲节点，即LCA

n: 节点数
k: 查询路径数
a[N*10]: 存储路径端点
mp: 映射边的方向性，0表示正向，ty表示反向
pw: 2的幂次方数组
ans: 最终答案
读入路径点序列
从节点1开始DFS建树
初始化边界条件
预计算2的幂次方
对每对相邻路径点，找到LCA
差分标记：在起点增加up，终点增加down，LCA处减少
这样在第二次DFS时，能够统计每条边被经过的次数
第二次DFS，完成差分数组的前缀和计算
遍历所有边，只处理有意义的边（mp[{v,u}]不为0）
根据边的方向判断使用up还是down数组
pw[x] - 1：如果有x条路径经过这条边，每条路径可以选或不选，共2^x种方案，减去全不选的情况
累加到答案

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e5+5, mod = 1e9+7;

int f[N][20], dep[N], up[N], down[N];
vector<int> e[N];
void dfs(int u, int fa) {
    f[u][0] = fa; dep[u] = dep[fa] + 1;
    for (int i = 1; i <= 18; ++i)
        f[u][i] = f[f[u][i-1]][i-1];
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs(v, u);
        up[u] += up[v]; down[u] += down[v];
    }
}

int get(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int i = 18; ~i; --i) {
        if (dep[f[x][i]] >= dep[y]) x = f[x][i];
        if (x == y) return x;
    }
    for (int i = 18; ~i; --i)
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    return f[x][0];
}

int n, k, a[N*10];
map<ii, int> mp;
ll pw[N*10], ans;
int main() {
    fast;
    n = rd();
    for (int i = 1; i < n; ++i) {
        int x = rd(), y = rd(), ty = rd();
        e[x].push_back(y); mp[{x, y}] = 0;
        e[y].push_back(x); mp[{y, x}] = ty;
    }
    k = rd();
    for (int i = 1; i <= k; ++i) a[i] = rd(); dfs(1, 0);
    a[0] = pw[0] = 1;
    for (int i = 1; i <= k; ++i) pw[i] = pw[i-1]*2%mod;
    for (int i = 1; i <= k; ++i) {
        int lca = get(a[i], a[i-1]);
        ++up[a[i-1]]; ++down[a[i]]; --up[lca]; --down[lca];
    }
    dfs(1, 0);
    for (int u = 1; u <= n; ++u)
        for (auto v : e[u]) {
            if (!mp[{v, u}]) continue;
            if (dep[u] < dep[v]) ans = (ans + pw[up[v]] - 1 + mod) % mod;
            else ans = (ans + pw[down[u]] - 1 + mod) % mod;
        }
    cout << ans << '\n';
    return 0;
}