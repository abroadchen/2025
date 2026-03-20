//
// Created by Psy.C on 2026/3/20.
//
/**
N = 32：最大长度
M = 52：最大面积
dp[x][y][sum]：在x×y的矩形中切割出面积为sum的矩形所需的最小代价
面积为0：不需要切割，代价为0
面积等于总面积：不用切割，代价为0
水平切割：沿着长度方向切割
i*y <= sum：如果左边部分面积 ≤ 需要的面积
dfs(x - i, y, sum - i*y) + y*y：切割右边，代价是y²
else：如果左边部分面积 > 需要的面积
dfs(i, y, sum) + y*y：只考虑左边，代价是y²
时间复杂度：O(N²M)预处理，O(1)查询 空间复杂度：O(N²M)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 32, M = 52, inf = 0x3f3f3f3f;
int dp[N][N][M];

int dfs(int x, int y, int sum) {
    if (sum == 0 || sum == x*y) return 0;
    if (dp[x][y][sum] != inf) return dp[x][y][sum];
    for (int i = 1; i < x; ++i) {
        if (i*y <= sum)
            dp[x][y][sum] = min(dp[x][y][sum],
                dfs(x - i, y, sum - i*y) + y*y);
        else
            dp[x][y][sum] = min(dp[x][y][sum],
                dfs(i, y, sum) + y*y);
    }
    for (int i = 1; i < y; ++i) {
        if (i*x <= sum)
            dp[x][y][sum] = min(dp[x][y][sum],
                dfs(x, y - i, sum - i*x) + x*x);
        else
            dp[x][y][sum] = min(dp[x][y][sum],
                dfs(x, i, sum) + x*x);
    }
    return dp[x][y][sum];
}

void init() {
    memset(dp, inf, sizeof(dp));
    for (int i = 1; i <= N-2; ++i)
        for (int j = 1; j <= N-2; ++j)
            for (int k = 1; k <= M-2 && k <= i*j; ++k)
                dp[i][j][k] = dfs(i, j, k);
}

int q, i, j, k;
int main() {
    fast;
    cin >> q; init();
    while (q--) {
        cin >> i >> j >> k;
        cout << dp[i][j][k] << '\n';
    }
    return 0;
}