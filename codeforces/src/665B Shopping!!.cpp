//
// Created by Psy.C on 2026/4/11.
//
/**
查找x在数组a中的位置j
将位置j加到答案中（访问此元素的成本）
将位置j的元素移到数组前面（像LRU/MRU缓存一样）
更新a[1] = x将访问的元素移到开头
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 105;
int n, m, k, a[N];
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= k; ++i) cin >> a[i];
    int ans = 0;
    for (int i = 1, x, j; i <= n*m; ++i) {
        cin >> x;
        for (j = 1; j <= k; ++j)
            if (a[j] == x) break;
        ans += j;
        for (int l = j; l >= 2; l--)
            a[l] = a[l-1];
        a[1] = x;
    }
    cout << ans << '\n';
    return 0;
}