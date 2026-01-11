//
// Created by Psy.C on 2026/1/11.
//
/**
* 从最高位（第30位）开始向下遍历每一位
x = 1<<t 表示第 t 位为1，其余位为0的掩码
找出所有在第 t 位上有1的数字，存入 b 数组
 *
*如果没有找到在第 t 位上有1的数字，继续下一位
对 b 数组中的所有数字执行按位与操作
检查结果 y 是否能被 x 整除（即检查 y 的低位是否为0）
*输出符合条件的数字个数
输出这些数字
 *
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10;

int main() {
    fast;
    int n, a[N], b[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int i, t = 30;
    while (t >= 0) {
        const int x = 1<<t; int tot = 0;
        for (i = 1; i <= n; ++i) if (x & a[i]) b[tot++] = a[i];
        if (!tot) { t--; continue; }
        int y = b[0];
        for (i = 1; i < tot; ++i) y &= b[i];
        if (y % x == 0) {
            cout << tot  << '\n';
            for (i = 0; i < tot; ++i) {
                if (i) cout << ' ';
                cout << b[i];
            }
            cout << '\n';
            break;
        }
        t--;
    }
    return 0;
}