//
// Created by Psy.C on 2026/4/19.
//
///O(n): 单次遍历数组
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, a[N];
int main() {
    fast;
    cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum += a[i] - 1;//累加每个数减1的值
        if (sum&1) cout << "1\n";
        else cout << "2\n";
    }
    return 0;
}