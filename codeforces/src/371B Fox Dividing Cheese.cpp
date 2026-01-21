//
// Created by Psy.C on 2026/1/21.
//
///O(log(min(a,b)))，主要是GCD计算的时间复杂度
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(const int a, const int b) { return b == 0 ? a : gcd(b, a % b); }

constexpr int d[] = {2, 3, 5};
int main() {
    fast;
    int a, b; cin >> a >> b;
    if (a == b) { cout << 0 << '\n'; return 0; }
    const int g = gcd(a, b); a /= g; b /= g;
    int ans = 0;
    for (const int i : d) {
        while (a % i == 0) { a /= i; ans++; }
        while (b % i == 0) { b /= i; ans++; }
    }
    //原分数仅含质因子 2,3,5
    if (a == 1 && b == 1) cout << ans << '\n';
    else cout << -1 << '\n';
    return 0;
}