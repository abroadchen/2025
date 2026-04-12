//
// Created by Psy.C on 2026/4/12.
//
/**
如果sum > a[n]:
其他所有元素的和大于最大元素
说明可以通过合理分配使得最大元素不再突出
输出"0"（不需要任何操作或差值为0）
否则 (sum <= a[n]):
其他所有元素的和小于等于最大元素
需要增加a[n] - sum + 1使其满足条件
输出a[n] - sum + 1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, a[N], sum;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    sort(a + 1, a + n + 1);
    sum -= a[n];//从总和中减去最大元素
    if (sum > a[n]) cout << "0\n";
    else cout << a[n] - sum + 1 << '\n';
    return 0;
}