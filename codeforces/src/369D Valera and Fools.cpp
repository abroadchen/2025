//
// Created by Psy.C on 2026/1/21.
//
/**
* n: 输入数组长度
k: 操作次数限制
p[i]: 输入数组，存储每个位置的值
b[i]: 预处理数组，b[i] 表示从位置i到末尾的最大值
dp[i][j]: 状态数组，表示在某种条件下达到(i,j)状态所需的最小操作数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3005
#define M 5000
#define inf 0x3f3f3f3f
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    int dp[N][N], p[M], b[N];
    for (int i = 1; i <= N-2; ++i) for (int j = 1; j <= N-2; ++j) {
        dp[i][j] = inf;//初始状态下不可达
    }
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = n; i >= 1; --i) {
        if (i == n) b[i] = p[i];
        else b[i] = max(b[i+1], p[i]);//后缀最大值
    }
    dp[1][2] = 0;//从位置1到位置2的操作数为0
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n; ++j) {
        //位置j之后的最大值大于0且当前位置i的值小于100
        if (b[j] > 0 && p[i] < 100) dp[j][j+1] = min(dp[j][j+1], dp[i][j]+1);
        if (b[j] > 0 && p[i] > 0) dp[j+1][j+2] = min(dp[j+1][j+2], dp[i][j]+1);
        if (b[j] < 100 && p[i] > 0) dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) for (int j = i + 1; j <= n + 1; ++j) {
        if (dp[i][j] <= k) ans++;
    }
    if (dp[n+1][n+2] <= k) ans++;
    cout << ans << '\n';
    return 0;
}