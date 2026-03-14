//
// Created by Psy.C on 2026/3/13.
//
/**
n：元素总数，k：分组数
n1：需要分配l1个元素的组数（余数个）
n2：需要分配l2个元素的组数
l1：较大组的大小（n/k+1）
l2：较小组的大小（n/k）

双重循环遍历所有状态
i：使用了几个大小为l1的组
j：使用了几个大小为l2的组
如果i>0：从前一个状态转移（添加一个l1大小的组）
计算该组的代价（最大值-最小值）
如果j>0：从前一个状态转移（添加一个l2大小的组）
计算该组的代价（最大值-最小值）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5, M = 5005;

int n, k, a[N];
ll dp[M][M];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int n1 = n%k, n2 = k-n%k, l1 = n/k+1, l2 = n/k;
    memset(dp, 0x3f, sizeof dp); dp[0][0] = 0;
    for (int i = 0; i <= n1; ++i)
        for (int j = 0; j <= n2; ++j) {
            if (i)
                dp[i][j] = min(dp[i][j], dp[i-1][j] +
                    a[i*l1+j*l2] - a[(i-1)*l1+j*l2+1]);
            if (j)
                dp[i][j] = min(dp[i][j], dp[i][j-1] +
                    a[i*l1+j*l2] - a[i*l1+(j-1)*l2+1]);
        }
    cout << dp[n1][n2] << '\n';
    return 0;
}