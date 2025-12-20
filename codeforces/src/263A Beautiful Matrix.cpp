//
// Created by Psy.C on 2025/12/20.
//
/*
*如果x等于1：
计算当前位置(i,j)到中心点(3,3)的曼哈顿距离
abs(i - 3)：行坐标到中心行的距离
abs(j - 3)：列坐标到中心列的距离
曼哈顿距离 = |i-3| + |j-3|
输出结果并换行
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x;
    for (int i = 1; i <= 5; ++i) for (int j = 1; j <= 5; ++j) {
        cin >> x;
        if (x == 1) cout << abs(i - 3) + abs(j - 3) << '\n';
    }
    return 0;
}