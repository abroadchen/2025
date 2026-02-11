//
// Created by Psy.C on 2026/2/10.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100001
using namespace std;

ll n, i, k, a[N];

int main() {
    fast;
    cin >> n;
    for (; i < n; ++i) cin >> k, a[k] += k;//每个数字出现后对总和的贡献
    ///要么不选当前值（保留前一个最优解），要么选当前值（当前值 + 前两个位置的最优解）
    for (i = 2; i < N; ++i) a[i] = max(a[i-1], a[i]+a[i-2]);
    cout << a[i-1];//整个数组的最优解
    return 0;
}