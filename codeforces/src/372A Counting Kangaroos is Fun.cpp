//
// Created by Psy.C on 2026/1/22.
//
/*
* 左指针i：从前半部分遍历（较小值）
右指针r：从后半部分选择最大可用值
贪心选择：总是用当前最大的可用值与较小值配对
时间复杂度: O(n log n)，主要是排序的复杂度
空间复杂度: O(n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500100
using namespace std;


int main() {
    fast;
    ll n; cin >> n;
    ll a[N], cnt = 0, r = n;
    for (ll i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    for (ll i = n>>1; i >= 1; --i) {
        if (a[i]<<1 <= a[r]) {
            cnt++;//配对成功
            r--;
        }
    }
    cout << n - cnt << '\n';
    return 0;
}