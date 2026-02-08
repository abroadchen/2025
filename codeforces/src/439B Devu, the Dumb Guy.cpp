//
// Created by Psy.C on 2026/2/7.
//
/**
排序: O(n log n)
主循环: O(n)
总体: O(n log n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define ll long long
using namespace std;


int main() {
    fast;
    int n, x; cin >> n >> x;
    int a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += 1ll*a[i]*x;
        if (x > 1) x--;
    }
    cout << ans;
    return 0;
}