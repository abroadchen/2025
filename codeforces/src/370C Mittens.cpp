//
// Created by Psy.C on 2026/1/21.
//
/*
* 设 half = n/2，则配对关系为：

a[0] ↔ a[half]
a[1] ↔ a[half+1]
a[2] ↔ a[half+2]
...
a[half-1] ↔ a[n-1]
a[half] ↔ a[0] (当i >= half时，(i+half)%n 会回绕)

时间复杂度: O(n log n)（主要由排序决定）
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5500
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int a[N];
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    int cnt = 0;
    for (int i = 0; i < n; ++i) cnt += a[i] != a[(i+n/2)%n];//与其对称位置的元素进行比较
    cout << cnt << '\n';
    for (int i = 0; i < n; ++i) cout << a[i] << ' ' << a[(i+n/2)%n] << '\n';
    return 0;
}