//
// Created by Psy.C on 2025/11/29.
//
/*
*if (d1 > d2) swap(d1, d2); - 确保d1 ≤ d2，便于后续判断
获胜条件判断：
d1 >= 3 && d2 >= 4: 第一个距离≥3且第二个距离≥4时，Second获胜
d1 > 4 || d2 > 4: 任一距离>4时，Second获胜
否则First获胜
 *
*计算两点在x轴和y轴上的距离：
d1 = abs(x1 - x2): x轴距离
d2 = abs(y1 - y2): y轴距离
调用ok函数判断结果
 */
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

void ok(int d1, int d2) {
    if (d1 > d2) swap(d1, d2);
    if (d1 >= 3 && d2 >= 4 || (d1 > 4 || d2 > 4)) cout << "Second";
    else cout << "First";
}

int main() {
    fast;
    int n, m, x1, y1, x2, y2;
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    const int d1 = abs(x1 - x2), d2 = abs(y1 - y2);
    ok(d1, d2);
    return 0;
}