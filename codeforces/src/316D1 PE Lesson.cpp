//
// Created by Psy.C on 2026/1/5.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000010
#define mod 1000000007
using namespace std;


int main() {
    fast;
    int n, m = 0, dp[N]; cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x == 1) m++;//值为1的元素
    }
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= m; ++i) dp[i] =
        static_cast<int>((dp[i-1] + 1ll * dp[i-2] * (i-1)) % mod);//i个元素的错排方案数
    int ans = dp[m];
    //从 m+1 到 n 的所有数字（即 n! / m!）
    for (int i = m + 1; i <= n; ++i) ans = static_cast<int>(1ll * ans * i % mod);
    cout << ans << '\n';
    return 0;
}