//
// Created by Psy.C on 2026/2/3.
//
/**
* 成本比较：比较单位成本
c/n：每单位的c成本
d：每单位的d成本
 *
*x = t/n：完整单位的数量（t除以n的商）
y = t - x*n：剩余数量（t除以n的余数）
 *
*z = y*d：剩余部分使用d方案的成本
z < c：如果y个单位用d方案更便宜
输出：c*x + z（完整单位用c方案 + 剩余用d方案）
z >= c：如果y个单位用d方案不便宜
输出：c*x + c（完整单位用c方案 + 剩余部分也用完整c方案）
 *
 *第二种情况：c/n >= d
 *直接方案：全部使用d方案
 *
 *O(1)：纯数学计算，无循环
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int c, d, n, m, k; cin >> c >> d >> n >> m >> k;
    if (const int t = n*m - k; t <= 0) cout << 0 << '\n'; else {
        if (c/n < d) {
            const int x = t/n, y = t - x*n;
            if (const int z = y*d; z < c) cout << c*x + z << '\n';
            else cout << c*x + c << '\n';
        }
        else cout << t*d << '\n';
    }
    return 0;
}