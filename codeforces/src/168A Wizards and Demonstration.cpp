//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 总数
x: 当前值
y: 百分比
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, x, y; cin >> n >> x >> y;
    int ans = 0;
    const double r = 1. * n * y / 100;
    if (x < r) {
        ans = static_cast<int>(r) - x;//目标值的整数部分减去当前值
        if (ans < r - x) ans++;//如果整数部分的差值小于实际差值，说明有小数部分，需要额外增加1
    }
    cout << ans << '\n';
    return 0;
}