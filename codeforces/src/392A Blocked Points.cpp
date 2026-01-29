//
// Created by Psy.C on 2026/1/29.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll calc(const int i, const int j) { return 1ll*i*i + 1ll*j*j; }

int main() {
    fast;
    int n; cin>>n;
    if (!n) { cout << "1\n"; return 0; }
    if (n == 1) { cout << "4\n"; return 0; }
    int y = 0, mn = n + 10, x = 0;
    for (int i = 0, j = n; i <= j; ++i) {
        while (calc(i, j) > 1ll*n*n) j--;//寻找满足 i² + j² ≤ n² 的 (i, j) 对
        if (i > j) break;
        if (j - i < mn) mn = j - i, x = i, y = j;//更新最优解
    }
    ll ans = 0;
    if (x == y) ans =  (x - 1)*8 + 8;//在对角线上
    else ans = min(x, y)*8 + 4;
    cout << ans << '\n';
    return 0;
}