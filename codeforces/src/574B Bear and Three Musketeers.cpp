//
// Created by Psy.C on 2026/3/14.
//
/**
vis[N][N]: 邻接矩阵，标记边的存在
v: 存储所有边的端点对
g[N]: 邻接表，存储每个节点的邻居
对每条边(x,y)：
存入边向量v
在邻接矩阵中标记边存在
在邻接表中添加双向连接

三重循环结构：遍历所有可能的三角形(x,y,z)

i: 遍历所有边
j: 遍历边(y,?)的另一个端点z
检查是否存在边(x,z)形成三角形
三角形检测：

(x,y): 已知边
(y,z): y的邻居节点z
(x,z): 检查vis[x][z]是否存在
度数和计算：
计算三角形三个顶点的度数之和
减去6是因为三角形内部的3条边在度数统计中被重复计算
每条边连接两个顶点，所以每条边贡献2个度数
最小值更新：

初始化ans=-1表示未找到
找到第一个三角形时赋初值
后续找到更优解时更新

时间复杂度: O(m × d)，其中d是最大度数
空间复杂度: O(n²)，主要由邻接矩阵占用
适用范围: 适合稠密图中寻找三角形的问题
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 4e3+5;

int n, m, vis[N][N];
vector<ii> v;
vector<int> g[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y; v.emplace_back(x, y);
        vis[x][y] = vis[y][x] = 1;
        g[x].push_back(y), g[y].push_back(x);
    }
    int ans = -1;
    for (int i = 0; i < m; ++i) {
        int x = v[i].first, y = v[i].second;
        for (int j = 0; j < g[y].size(); ++j) {
            if (int z = g[y][j]; vis[x][z]) {
                int t = g[x].size();
                t += g[y].size(); t += g[z].size(); t -= 6;
                if (ans == -1) ans = t;
                else ans = min(ans, t);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}