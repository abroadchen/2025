//
// Created by Psy.C on 2026/1/8.
//
/**
 * ans：最大子数组和，表示通过翻转某个子数组最多能增加多少个1
 *one + ans：原1的个数 + 通过翻转增加的1的个数
 *如果全是1，必须翻转一个子数组，所以是n-1
 *找到最多的0和最少的1的连续子数组，翻转它们可以得到最多的1
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, one = 0, sum = 0; cin >> n; vector<int> a(n);
    for (ll i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == 1) one++;
    }
    ll ans = 0;
    for (ll i = 0; i < n; ++i) {
        if (a[i] == 0) sum += 1; else sum -= 1;
        ans = max(ans, sum);
        if (sum < 0) sum = 0;
    }
    if (one == n) cout << n - 1 << '\n'; else cout << one + ans << '\n';
    return 0;
}