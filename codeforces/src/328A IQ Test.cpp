//
// Created by Psy.C on 2026/1/9.
//
/**
* const double EPS = 1e-9;  // 定义误差范围
bool equal(double a, double b) {
    return abs(a - b) < EPS;
}
 *
if (abs(a[2]) > EPS && abs(a[3]) > EPS && abs(a[4]) > EPS)
 *
*const int f = static_cast<int>(h + 0.5);  // 四舍五入
if (equal(f, h)) {
    cout << a[4] / z;
} else {
    cout << 42;
}
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    double a[10];
    for (int i = 1; i <= 4; ++i) cin >> a[i];
    if (a[1] - a[2] == a[2] - a[3] && a[2] - a[3] == a[3] - a[4]) {//检查是否为等差数列
        cout << a[4]*2 - a[3];//输出下一个数（a[4] + (a[4]-a[3]))
        return 0;
    }
    if (const double x = a[1] / a[2], y = a[2] / a[3], z = a[3] / a[4];//相邻两项的比值
        x == y && y == z) {//检查是否为等比数列
        const double h = a[4] / z;//计算下一个数（a[4] / (a[3]/a[4]))
        const int f = static_cast<int>(h);//将h转换为整数
        f == h ? cout << a[4] / z : cout << 42;//如果h是整数则输出，否则输出42
        return 0;
    }
    cout << 42;//既不是等差数列也不是等比数列
    return 0;
}