//
// Created by Psy.C on 2026/1/13.
//
/**
* 每个数a[i]需要a[i]/g - 1次操作才能变成g
总操作数为∑(a[i]/g - 1) = (∑a[i])/g - n
奇数次操作先手胜，偶数次操作后手胜
 *
 * O(n log(max_value))，主要是GCD计算的复杂度。
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    ranges::sort(a);
    int g = __gcd(a[0], a[1]);
    for (int i = 0; i < n; ++i) for (int j = i; j < n; ++j) {
        g = __gcd(__gcd(a[i], a[j]), g);
    }
    if ((a[n-1]/g - n) % 2 == 0) cout << "Bob"; else cout << "Alice";
    return 0;
}