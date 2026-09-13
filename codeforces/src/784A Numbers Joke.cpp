//
// Created by Psy.C on 2026/9/13.
//
/**
493775 = 3·5²·65837 是 Smith 数，因为各位和 4+9+3+7+7+5=42，质因数和 3+2·5+6+5+8+3+7=42
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int a[] = {
    4, 22, 27, 58, 85, 94, 121, 166, 202, 265, 274, 319, 346, 355, 378, 382,
    391, 438, 454, 483, 517, 526, 535, 562, 576, 588, 627, 634, 636, 645
};
int main() {
    fast;
    int x; cin >> x;
    cout << a[x-1];
    return 0;
}

int digit_sum(ll n) {
    int s = 0;
    while (n) { s += n%10; n /= 10; }
    return s;
}
bool is_prime(int x) {
    if (x < 2) return false;
    for (int i = 2; 1ll*i*i <= x; ++i)
        if (x % i == 0) return false;
    return true;
}
int factor_sum(int x) {
    int s = 0;
    for (int i = 2; 1ll*i*i <= x; ++i) {
        while (x%i == 0) {
            s += digit_sum(i);
            x /= i;
        }
    }
    if (x > 1) s += digit_sum(x);
    return s;
}

int solve() {
    vector<int> ans;
    for (int n = 4; ans.size() < 30 && n < 2000000; ++n) {
        if (is_prime(n)) continue;
        if (digit_sum(n) == factor_sum(n)) ans.push_back(n);
    }
    for (int v : ans) cout << v << ",\n";
    return 0;
}