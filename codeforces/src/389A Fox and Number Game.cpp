//
// Created by Psy.C on 2026/1/28.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll gcd(const ll a, const ll b) { return b == 0 ? a : gcd(b, a % b); }

int main() {
    fast;
    int n, a[105]; cin >> n;
    cin >> a[0];
    int ans = a[0];//存储当前的最大公约数
    for (int i = 1; i < n; ++i) {
        cin >> a[i];
        ans = static_cast<int>(gcd(ans, a[i]));
    }
    cout << ans * n << '\n';
    return 0;
}