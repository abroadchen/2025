//
// Created by Psy.C on 2026/9/25.
//
/**
dp[x][y][v]：坐标 (x,y) 处初始亮度为 v 的星星数量。n 颗星星，q 次询问，c 为最大亮度（c+1 种亮度 0..c）。
每轮测试先清零 dp。
读入每颗星星的坐标 x,y 和初始亮度 v，在 dp[x][y][v]++ 计数。同一坐标可能有多个不同亮度的星星，所以分亮度维度存
对每一种初始亮度 k（0..c），分别对整张坐标网格做二维前缀和：
dp[i][j][k] += dp[i-1][j][k] + dp[i][j-1][k] - dp[i-1][j-1][k]
这是标准二维前缀和公式（上 + 左 − 左上）。
处理后，dp[i][j][k] 表示 矩形 (1,1)-(i,j) 内初始亮度为 k 的星星总数。
循环到 N-5 = 100，覆盖坐标上限
读入时刻 t 和矩形左下角 (sx,sy)、右上角 (ex,ey)。
对每种初始亮度 i（0..c）：
x = (i + t) % (c+1)：初始亮度为 i 的星星在时刻 t 的当前亮度（周期性：t 秒后亮度 = (i+t) mod (c+1)）。
dp[ex][ey][i] - dp[sx-1][ey][i] - dp[ex][sy-1][i] + dp[sx-1][sy-1][i]：用二维前缀和求矩形 (sx,sy)-(ex,ey) 内初始亮度为 i 的星星数量。
当前亮度 × 数量，累加到 ans。
输出 ans，即矩形内所有星星在时刻 t 的亮度总和
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105, M = 12;
int n, q, c, dp[N][N][M];
int main() {
    fast;
    while (cin >> n >> q >> c) {
        memset(dp, 0, sizeof dp);
        for (int i = 1, x, y, v; i <= n; ++i) {
            cin >> x >> y >> v; dp[x][y][v]++;
        }
        for (int i = 1; i <= N-5; ++i)
            for (int j = 1; j <= N-5; ++j)
                for (int k = 0; k <= c; ++k)
                    dp[i][j][k] += dp[i-1][j][k]+dp[i][j-1][k]-dp[i-1][j-1][k];
        while (q--) {
            int t, sx, sy, ex, ey, ans = 0;
            cin >> t >> sx >> sy >> ex >> ey;
            for (int i = 0; i <= c; ++i) {
                int x = (i+t)%(c+1);
                ans += x*(dp[ex][ey][i]-dp[sx-1][ey][i]-dp[ex][sy-1][i]+dp[sx-1][sy-1][i]);
            }
            cout << ans << '\n';
        }
    }
    return 0;
}