//
// Created by Psy.C on 2026/2/9.
//
/**
二分搜索：O(log k)
每次get函数：O(min(n, x)) ≤ O(n)
总体：O(n log k)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
ll get(const ll x) {//矩阵中不超过x的元素个数
    ll sum = 0;
    for (ll i = 1; i <= x && i <= n; ++i) sum += min(x/i, m);
    return sum;
}

ll k;//第k小的元素

int main() {
    fast;
    cin >> n >> m >> k;
    ll l = 1, r = k, mid = l + (r-l)/2;
    const ll kk = k;
    while (l < r) {
        if (get(mid) < kk) l = mid + 1;
        else r = mid;
        mid = l + (r-l)/2;
    }
    cout << mid << '\n';
    return 0;
}