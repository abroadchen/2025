//
// Created by Psy.C on 2026/3/30.
//
/**
rt: 根节点（当前外层循环的节点）
u: 当前访问的节点
mx[u]: MST中从rt到u路径上的最大边权
a[rt][u]: 原图中rt到u的直接边权
mx[i]：从根节点rt到节点i的路径上的最大边权
验证条件：mx[u] < a[rt][u]
这意味着：MST中从rt到u的路径上的最大边权 < 原图中rt到u的直连边权

memset(d, 0x3f, sizeof(d)): 将距离数组d全部初始化为无穷大（0x3f3f3f3f）
d[1] = 0: 将起始节点1的距离设为0
in[1] = true: 将节点1标记为已在MST中
d[i] = a[1][i]: 将节点1到其他所有节点的距离赋给距离数组
fr[i] = 1: 将其他所有节点的父节点设为节点1
此时，MST只包含节点1，其他节点都在MST外部。
寻找不在MST中且距离MST最近的节点x
d[j]表示节点j到当前MST的最短距离
x就是下一个要加入MST的节点
将节点x标记为已加入MST
在邻接表v中建立父子关系
fr[x]是x在MST中的父节点
这样就建立了MST的结构
遍历所有不在MST中的节点y
如果边(x,y)的权重小于y到当前MST的距离d[y]
则更新d[y] = a[x][y]，并设置fr[y] = x

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2505;

int d[N], n, a[N][N], fr[N];
bool in[N];
vector<int> v[N];
void prim() {
    memset(d, 0x3f, sizeof(d)); d[1] = 0; in[1] = true;
    for (int i = 2; i <= n; ++i)
        d[i] = a[1][i], fr[i] = 1;
    for (int i = 1; i < n; ++i) {
        int x = 0;
        for (int j = 1; j <= n; ++j)
            if (!in[j] && (x == 0 || d[j] < d[x]))
                x = j;
        in[x] = true;
        v[fr[x]].push_back(x); v[x].push_back(fr[x]);
        for (int y = 1; y <= n; ++y)
            if (!in[y] && a[x][y] < d[y]) {
                d[y] = a[x][y];
                fr[y] = x;
            }
    }
}

int mx[N];
void dfs(int rt, int u, int fa=0) {
    if (u != rt && mx[u] < a[rt][u]) {
        cout << "NOT MAGIC\n";
        exit(0);
    }
    for (int i : v[u]) {
        if (i == fa) continue;
        mx[i] = max(mx[u], a[u][i]);//更新路径最大边权
        dfs(rt, i, u);//递归访问子节点
    }
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            if (i > j && a[i][j] != a[j][i]) {//检查对称性 无向图
                cout << "NOT MAGIC\n";
                return 0;
            }
            if (i == j && a[i][j] != 0) {//检查对角线 无自环
                cout << "NOT MAGIC\n";
                return 0;
            }
        }
    prim();
    for (int i = 1; i <= n; ++i) {
        memset(mx, 0, sizeof(mx));
        dfs(i, i);//以i为根的MST子树是否满足特殊性质
    }
    cout << "MAGIC\n";
    return 0;
}