//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    if (n == 2) return cout << 10, 0;

    ll a = 4, cur = 4, res = 6;
    for (int i = 3; i <= n / 2; ++i)
        a = a * 2 % MOD, cur = (cur * (a - 3 + MOD)) % MOD, res = (res + cur) % MOD;
    cout << 2 * (res * res + 1) % MOD;

    return 0;
}