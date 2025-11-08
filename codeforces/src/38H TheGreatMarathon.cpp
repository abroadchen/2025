//
// Created by Psy.C on 2025/9/24.
//
/*
 *
 *定义变量n(节点数)和m(边数)
*创建一个n×n的二维向量dis，初始化为很大的值(1e9)，表示距离矩阵
将对角线元素(自己到自己的距离)设为0
*读取m条边的信息
对于每条边，读取起点a、终点b和权重c
将a和b减1(转换为0索引)
在距离矩阵中设置无向边的权重
*使用Floyd-Warshall算法计算所有点对之间的最短路径
三层循环，k为中间节点，更新i到j的最短距离
 *
 *对距离矩阵的每一行进行排序(每个节点到其他所有节点的距离排序)
*对于每个节点i，a存储(到第二近节点的距离, 节点编号)
b存储(到最远节点的距离, 节点编号)
*双重循环遍历a和b中的元素
如果r小于l或者l和r是同一个节点，则跳过
 *
*x: 节点属于"左侧"集合
y: 节点属于"中间"集合
z: 节点属于"右侧"集合
 *
*反向遍历DP状态
如果节点属于左侧且j<g2，将状态转移到j+1
如果节点属于中间且k<s2，将状态转移到k+1
如果节点不属于右侧，将当前状态置为0
 *
 *
 *
 */
#include <ios>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define ll long long
#define IO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

int main() {
    IO;
    int n, m; cin>>n>>m;
    vector<vector<int>> dis(n, vector<int>(n, 1e9));
    rep (i, n) dis[i][i] = 0;
    rep (i, m) {
        int a, b, c; cin>>a>>b>>c;
        a--, b--;
        dis[a][b] = dis[b][a] = c;
    }
    rep (k, n)
        rep (i, n)
            rep (j, n)
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);

    int g1, g2, s1, s2; cin>>g1>>g2>>s1>>s2;
    rep (i, n) sort(dis[i].begin(), dis[i].end());

    vector<pair<int, int>> a, b;
    rep (i, n) {
        a.emplace_back(dis[i][1], i);
        b.emplace_back(dis[i][n - 1], i);
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll ans = 0;
    for (auto l : a) {
        for (auto r : b) {
            if (r < l) continue;
            if (l.second == r.second) continue;
            vector<vector<ll>> dp(g2 + 1, vector<ll>(s2 + 1));
            dp[0][0] = 1;
            rep (i, n) {
                bool x(false), y(false), z(false);
                if (i == l.second) x = true;
                else if (i == r.second) z = true;
                else {
                    for (auto d : dis[i]) {
                        if (!d) continue;
                        if (pair(d, i) < l) x = true;
                        else if (pair(d, i) > r) z = true;
                        else y = true;
                    }
                }
                for (int j = g2; j >= 0; --j) {
                    for (int k = s2; k >= 0; --k) {
                        if (j < g2 && x) dp[j + 1][k] += dp[j][k];
                        if (k < s2 && y) dp[j][k + 1] += dp[j][k];
                        if (!z) dp[j][k] = 0;
                    }
                }
            }
            ll res = 0;
            for (int i = g1; i <= g2; ++i) {
                for (int j = s1; j <= s2; ++j)
                    res += dp[i][j];
            }
            ans += res;
        }
    }
    cout << ans << "\n";

    return 0;
}