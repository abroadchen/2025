//
// Created by Psy.C on 2025/12/7.
//
/*
*时间复杂度：O(√n) —— 只需枚举到 √n
空间复杂度：O(1) —— 只使用常数额外空间
 *
 *a⁴ - 2na² + a + n² - m = 0 直接求解比较复杂
 *直接枚举 a，通过方程(1)计算 b
*避免浮点运算：全程使用整数运算
剪枝优化：通过约束条件减少枚举范围
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, ans = 0;
    cin >> n >> m;
    for (int a = 0; a * a <= n && a <= m; ++a) {
        const int b = n - a * a;
        if (a + b * b == m) ans++;
    }
    cout << ans << '\n';
    return 0;
}