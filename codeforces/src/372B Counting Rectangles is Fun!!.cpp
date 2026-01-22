//
// Created by Psy.C on 2026/1/22.
//
/**
* v[i][j]: 原始矩阵，存储0/1值
n, m: 矩阵尺寸
s[i][j]: 前缀和数组 左 + 上 - 左上 + 当前值
*f[a][b][c][d]: 从(a,b)到(c,d)矩形范围内，全零子矩形的数量
dp[a][b][c][d]: 从(a,b)到(c,d)矩形范围内，所有子矩形中全零矩形的总数量
 *
*检查矩形区域[(a,b), (c,d)]是否全为0
原理: 利用前缀和快速计算区域和，若和为0则全为0
 *
 *三维前缀和: 在第三、四维度上建立前缀和
 *四维前缀和: 从右下角向左上角递推
 *
*预处理时间: O(n²m²)
空间复杂度: O(n²m²)
查询时间: O(1) per query
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 45
using namespace std;

int s[N][N], n, m, v[N][N];
void get_s() {
    memset(s, 0, sizeof(s));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        s[i][j] = s[i][j-1] + s[i-1][j] - s[i-1][j-1] + v[i][j];
    }
}

int ok(const int a, const int b, const int c, const int d) {
    const int sum = s[c][d] - s[c][b-1] - s[a-1][d] + s[a-1][b-1];
    return sum == 0 ? 1 : 0;
}


int f[N][N][N][N];
void get_f() {
    memset(f, 0, sizeof(f));
    for (int a = 1; a <= n; ++a) for (int b = 1; b <= m; ++b)
        for (int c = a; c <= n; ++c) for (int d = b; d <= m; ++d) {
            f[a][b][c][d] = f[a][b][c-1][d] + f[a][b][c][d-1] -
                f[a][b][c-1][d-1] + ok(a, b, c, d);
        }
}

int dp[N][N][N][N];
void get_dp() {
    memset(dp, 0, sizeof(dp));
    for (int a = n; a >= 1; --a) for (int b = m; b >= 1; --b)
        for (int c = n; c >= a; --c) for (int d = m; d >= b; --d) {
            dp[a][b][c][d] = dp[a+1][b][c][d] + dp[a][b+1][c][d] -
                dp[a+1][b+1][c][d] + f[a][b][c][d];
        }
}

int t;
void init() {
    cin >> n >> m >> t; char c;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        cin >> c;
        v[i][j] = c - '0';
    }
}


int main() {
    fast;
    init();
    get_s(); get_f(); get_dp();
    int a, b, c, d;
    while (t--) {
        cin >> a >> b >> c >> d;
        cout << dp[a][b][c][d] << '\n';
    }
    return 0;
}