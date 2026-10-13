//
// Created by Psy.C on 2026/10/12.
//
/**
sqrt(a) 返回 a 的平方根（浮点数），static_cast<int>(...) 强制转成整数（向下取整，截断小数部分）。
若 a 是完全平方数，比如 a = 49，则 floor(√49) = 7，7*7 = 49 == a，条件不成立 → 该数被排除。
若 a 不是完全平方数，比如 a = 50，则 floor(√50) = 7，7*7 = 49 ≠ 50，条件成立 → 该数参与比较。
所以这个 if 条件等价于："a 不是完全平方数"
只保留"非完全平方数"中的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int a, mx = INT_MIN;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        if (static_cast<int>(sqrt(a))*static_cast<int>(sqrt(a)) != a)
            mx = max(mx, a);
    }
    cout << mx << '\n';
    return 0;
}