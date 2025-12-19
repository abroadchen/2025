//
// Created by Psy.C on 2025/12/19.
//
/*
 *n:节点数, m:交换次数, a:节点权值数组
 *f:概率矩阵, ans:最终答案
 *
*时间复杂度：O(m×n + n²)
空间复杂度：O(n²)
 */
#include <iomanip>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


int main() {
    fast;
    int n, m, a[N]; double f[N][N], ans = 0;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,n) rep(j,n) if (a[i] > a[j]) f[i][j] = 1.;//i战胜j的概率为1
    while (m--) {//迭代更新概率矩阵
        int x, y; cin >> x >> y;//读取要交换的两个节点
        rep(i,n) {//更新与其他节点的关系概率
            if (i == x || i == y) continue;//跳过自身
            f[i][x] = f[i][y] = (f[i][x] + f[i][y]) / 2.;//更新i节点与x、y节点的概率关系
            f[x][i] = f[y][i] = (f[x][i] + f[y][i]) / 2.;//更新x、y节点与i节点的概率关系
        }
        f[x][y] = f[y][x] = 0.5;//设置x和y节点之间的胜负概率为0.5（平局）
    }
    rep(i,n) for (int j = i + 1; j <= n; ++j) ans += f[i][j];//只计算上三角矩阵
    cout << fixed << setprecision(9) << ans << '\n';
    return 0;
}