//
// Created by Psy.C on 2025/12/6.
//
/*
* 时间复杂度：O(1) - 固定大小的排序和常数时间操作
空间复杂度：O(1) - 固定大小的数组
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    constexpr int n = 3;
    ll a[3];
    for (ll & i : a) cin >> i;
    sort(a, a+n);//排序后 a[0] ≤ a[1] ≤ a[2]
    cout << ((a[0] + a[1]) % 2 ? a[2] : a[1]);
    return 0;
}