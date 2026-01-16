//
// Created by Psy.C on 2026/1/15.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 4501510
using namespace std;


int main() {
    fast;
    int dp[N], n, a[N], cnt = 0; dp[0] = 0; dp[1] = 1; cin >> n;
    //n个元素最多可能出现的逆序对数量
    for (int i = 2; i <= n * (n-1) / 2; ++i) dp[i] = dp[i-2] + 4;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) for (int j = i; j <= n; ++j) {
        if (a[i] > a[j]) cnt++;
    }
    cout << dp[cnt] << ".000000";
    return 0;
}