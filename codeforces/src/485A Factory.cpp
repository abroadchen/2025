//
// Created by Psy.C on 2026/2/17.
//
/**
时间复杂度：O(min(m, 100))
空间复杂度：O(1)

每次操作：n = n + (n % m)
等价于：n = n + (n - ⌊n/m⌋ * m) = 2*n - ⌊n/m⌋ * m
或者：n = ⌊n/m⌋ * m + 2 * (n % m)
由于n % m的值域有限（0到m-1），状态会在有限步内重复
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, r;
int main() {
    fast;
    cin >> n >> m;
    int q = 100;
    while (q--) {
        r = n%m;
        if (r == 0) { cout << "Yes\n"; return 0; }
        n += r;
    }
    cout << "No\n";
    return 0;
}