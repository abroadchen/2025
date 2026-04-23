//
// Created by Psy.C on 2026/4/23.
//
/**
q：队列，用于BFS处理
ve[N]：邻接表，存储原图
vv[N]：存储欧拉路径中的边
l[N][N]：邻接矩阵，记录边的数量
deg[N]：节点度数
in[N], out[N]：节点的入度和出度

构建欧拉路径
从队列中取出节点x
从x开始寻找可走的边：
减少边的数量和度数
更新入度和出度
将边加入路径
如果度数变为奇数，加入队列
移动到下一个节点v
重复直到找不到可走的边

读入测试用例数t
初始化邻接矩阵
清空邻接表和路径表
初始化度数数组
读入m条边
更新邻接矩阵（双向边）
更新邻接表
更新度数
初始化入度和出度
清空队列
将所有奇度数节点加入队列（欧拉路径的起点/终点）
第一次调用get()：处理奇度数节点（连接欧拉路径的端点）
将仍有度数的节点加入队列
第二次调用get()：处理剩余的欧拉回路
统计入度等于出度的节点数量
输出结果
输出所有的边（欧拉路径）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 207;

queue<int> q;
vector<int> ve[N], vv[N];
int l[N][N], deg[N], in[N], out[N];
void get() {
    while (!q.empty()) {
        int x = q.front(); q.pop();
        while (true) {
            int len = ve[x].size(), flag = 0;
            for (int i = 0; i < len; ++i) {
                int v = ve[x][i];
                if (l[x][v]) {
                    l[x][v]--, l[v][x]--;
                    deg[x]--, deg[v]--;
                    out[x]++, in[v]++;
                    vv[x].push_back(v);
                    if (deg[x]&1) q.push(x);
                    if (deg[v]&1) q.push(v);
                    x = v;
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) break;
        }
    }
}

int t, n, m;
int main() {
    fast;
    cin >> t;
    while (t--) {
        memset(l, 0, sizeof(l));
        cin >> n >> m;
        for (int i = 1; i <= n; ++i) ve[i].clear(), vv[i].clear();
        memset(deg, 0, sizeof(deg));
        for (int i = 0, u, v; i < m; ++i) {
            cin >> u >> v;
            l[u][v]++, l[v][u]++;
            ve[u].push_back(v); ve[v].push_back(u);
            deg[u]++, deg[v]++;
        }
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        while (!q.empty()) q.pop();
        for (int i = 1; i <= n; ++i)
            if (deg[i]&1) q.push(i);
        get();
        for (int i = 1; i <= n; ++i)
            if (deg[i]) q.push(i);
        get();
        int ans = 0;
        for (int i = 1; i <= n; ++i)
            if (in[i] == out[i]) ans++;
        cout << ans << '\n';
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < vv[i].size(); ++j)
                cout << i << ' ' << vv[i][j] << '\n';
        }
    }
    return 0;
}