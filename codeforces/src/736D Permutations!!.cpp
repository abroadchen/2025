//
// Created by Psy.C on 2026/4/28.
//
/**
n表示节点数量
m表示边的数量
x[M], y[M]存储每条边的起点和终点
将对角线位置(i, i+n)设为1，这是高斯消元中的增广矩阵部分
读入m条边，将对应位置(x[i], y[i])设为1，构建邻接矩阵
对第i列进行高斯消元
寻找第i列中第i行以下第一个非零元素
如果找到，就交换第i行和第j行，使主元不为0
消元操作：对所有其他行，如果第i列元素为1，则与第i行异或消除该列
对于每条边(x[i], y[i])，检查增广矩阵对应位置
如果g[y[i]][x[i]+n]为1则输出"NO"，否则输出"YES"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2007, M = 5e5+7;
int n, m, x[M], y[M];
bitset<N*2> g[N];//存储图的信息
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) g[i][i+n] = 1;
    for (int i = 1; i <= m; ++i) {
        cin >> x[i] >> y[i];
        g[x[i]][y[i]] = 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j)
            if (g[j][i]) {
                swap(g[i], g[j]);
                break;
            }
        for (int j = 1; j <= n; ++j)
            if (j != i && g[j][i]) g[j] ^= g[i];
    }
    for (int i = 1; i <= m; ++i)
        cout << (g[y[i]][x[i]+n] ? "NO" : "YES") << '\n';
    return 0;
}