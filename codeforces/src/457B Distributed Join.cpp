//
// Created by Psy.C on 2026/2/11.
//
/**
排序：O(m log m + n log n)
计算：O(m + n)
总体：O(m log m + n log n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 111111
using namespace std;

int m, n, a[N], b[N];
int main() {
    fast;
    cin >> m >> n;
    ll s1 = 0, s2 = 0;
    for (int i = 0; i < m; ++i) cin >> a[i], s1 += a[i];
    for (int i = 0; i < n; ++i) cin >> b[i], s2 += b[i];
    sort(a, a + m); sort(b, b + n);
    ll a1 = s2, a2 = s1;
    for (int i = 0; i < m-1; ++i) a1 += min(s2, 1ll*a[i]);
    for (int i = 0; i < n-1; ++i) a2 += min(s1, 1ll*b[i]);
    cout << min(a1, a2) << '\n';
    return 0;
}