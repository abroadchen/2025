//
// Created by Psy.C on 2026/9/22.
//
/**
g[0][j]：记录第 j 列当前所有元素的最小值
g[i][0]：记录第 i 行当前所有元素的最小值
（因为矩阵从 [1][1] 开始存，所以第0行第0列可以闲置出来当辅助区
初始化时，边读入边更新每列的最小值（放 g[0][j]）和每行的最小值（放 g[i][0]）
分支一：n < m（先做所有行操作）
第一步：处理所有行
对每一行，取当前最小值 g[i][0]，记录对该行操作 g[i][0] 次，然后整行减去这个值，实时更新受影响的列最小值。
第二步：处理所有列
再对每一列做同样处理
分支二：else（先做所有列操作）
顺序调换：先处理列，再处理行。逻辑对称
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 110, inf = 0x7f7f7f7f;
int n, m, g[N][N];
vector<int> r, c;
int main() {
    fast;
    cin >> n >> m;
    memset(g, inf, sizeof g);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> g[i][j];
            g[0][j] = min(g[0][j], g[i][j]);
            g[i][0] = min(g[i][0], g[i][j]);
        }
    int cnt = 0;
    if (n < m) {
        for (int i = 1; i <= n; ++i) {
            if (g[i][0] < inf && g[i][0] != 0) {//第 i 行最小值存在且非0/
                for (int k = 0; k < g[i][0]; ++k)
                    r.push_back(i), cnt++;//对第 i 行减1，做 g[i][0] 次
                for (int j = 1; j <= m; ++j) {
                    g[i][j] = g[i][j] - g[i][0];//整行减 g[i][0]
                    g[0][j] = min(g[0][j], g[i][j]);//更新第 j 列最小值
                }
                g[i][0] = 0;//该行最小值已归0
            }
        }
        for (int j = 1; j <= m; ++j) {
            if (g[0][j] < inf && g[0][j] != 0) {
                for (int k = 0; k < g[0][j]; ++k)
                    c.push_back(j), cnt++;
                for (int i = 1; i <= n; ++i) {
                    g[i][j] = g[i][j] - g[0][j];
                    g[i][0] = min(g[i][0], g[i][j]);
                }
                g[0][j] = 0;
            }
        }
    } else {
        for (int j = 1; j <= m; ++j) {
            if (g[0][j] < inf && g[0][j] != 0) {
                for (int k = 0; k < g[0][j]; ++k)
                    c.push_back(j), cnt++;
                for (int i = 1; i <= n; ++i) {
                    g[i][j] = g[i][j] - g[0][j];
                    g[i][0] = min(g[i][0], g[i][j]);
                }
                g[0][j] = 0;
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (g[i][0] < inf && g[i][0] != 0) {
                for (int k = 0; k < g[i][0]; ++k)
                    r.push_back(i), cnt++;
                for (int j = 1; j <= m; ++j) {
                    g[i][j] = g[i][j] - g[i][0];
                    g[0][j] = min(g[0][j], g[i][j]);
                }
                g[i][0] = 0;
            }
        }
    }
    int flag = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (g[i][j]) { flag = 1; break; }//还有非0元素
    if (flag) cout << "-1\n";//无法归零，输出-1
    else {
        cout << cnt << '\n';//总操作次数
        int len = r.size(), len2 = c.size();
        for (int i = 0; i < len; ++i) cout << "row " << r[i] << '\n';//行操作序列
        for (int i = 0; i < len2; ++i) cout << "col " << c[i] << '\n';
    }
    return 0;
}