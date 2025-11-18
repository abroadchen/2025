//
// Created by Psy.C on 2025/11/18.
//
/*
 *循环条件为--n（先将n减1再判断是否为真）
 *迭代部分：将v赋值给x，w赋值给y
 *
 */
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

int k, n;
double v, w, x, y, z;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (cin >> n >> k >> x >> y; --n; x = v, y = w) {
        cin >> v >> w;
        z += sqrt((v - x) * (v - x) + (w - y) * (w - y));//当前点(v,w)与前一个点(x,y)之间的欧几里得距离，并累加到z中
    }
    cout << fixed << setprecision(9) << z * k / 50 << '\n';
    return 0;
}