//
// Created by Psy.C on 2026/9/8.
//
///排序后的中点（上中位数/靠右的中位数)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;

int a[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1); n = n/2+1;
    cout << a[n];
    return 0;
}