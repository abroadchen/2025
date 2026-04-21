//
// Created by Psy.C on 2026/4/20.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;
int n;
ll a[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    if (n&1) cout << a[(n+1)/2] << '\n';//中位数是第 (n+1)/2 个元素
    else cout << a[n/2] << '\n';//取下中位数（较小的中位数）
    return 0;
}