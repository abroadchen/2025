//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
n（总数）、m（组大小）、a（每次增加的代价）、b（每次移除的代价）
若 n 能被 m 整除（无需任何调整），直接输出 0
当 n < m 时，n % m = n ≠ 0，有剩余 n。
方案1（ans）‍：把 n 补齐到 m，需要补 m - n 个，每补一个代价 a，故 ans = (m-n)*a。
方案2（sum）‍：把 n 个全部移除（因为不到一组 m），每移除一个代价 b，故 sum = n*b。
取两者较小值 min(ans, sum) 输出
当 n ≥ m 时，考虑三种方案：
方案 A（ans）— 向上补齐到 m 的倍数
n/m = 完整组数；(n/m+1)*m = 下一个 m 的倍数。
(n/m+1)*m - n = 还差多少个补到下一个倍数。
乘以 a = 补充的代价。
例如 n=7, m=3：n/m=2，(2+1)*3=9，9-7=2，补 2 个到 9，代价 2a。
方案 B（sum）— 向下截断到 m 的倍数
n/m*m = 当前完整组占用的总量（向下取最大倍数）。
n - n/m*m = 多余出来的数（n mod m 的补，即超出完整倍数的那部分）。
乘以 b = 删除这些多余单位的代价。
例如 n=7, m=3：n/m*m=6，7-6=1，删 1 个到 6，代价 1b。
方案 C（res）— 全部移除：
把所有 n 个单位全部删掉，代价 n*b。

输出三者最小值 min(min(ans, sum), res)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, a, b;
int main() {
    fast;
    cin >> n >> m >> a >> b;
    if (n%m == 0) cout << "0\n";
    else {
        ll ans = 0, sum = 0, res = 0;
        if (n < m) {
            ans = (m - n) * a; sum = n*b;
            cout << min(ans, sum) << '\n';
        } else {
            ans = ((n/m+1)*m-n)*a; sum = (n-n/m*m)*b;
            res = n*b;
            cout << min(min(ans, sum), res) << '\n';
        }
    }
    return 0;
}