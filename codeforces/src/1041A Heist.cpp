//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
a[n-1]：排序后最大值 max；
a[0]：排序后最小值 min；
a[n-1]-a[0]+1：从 min 到 max 的整数闭区间长度（即 max - min + 1，表示这个范围内共有多少个整数）；
- n：减去已有的 n 个数；
结果 = 在 [min, max] 之间"缺少"的整数个数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1005;

int n, a[N];
int main() {
    fast;
    while (cin >> n) {
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a, a + n);
        cout << a[n-1]-a[0] + 1 - n << '\n';
    }
    return 0;
}