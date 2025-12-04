//
// Created by Psy.C on 2025/12/3.
//
/*
*判断条件：如果当前累计增长量p加上下一轮的增长量(bc)大于等于目标总量(ac)
如果满足条件，则输出当前循环次数i，并结束程序
这实际上是在计算达到目标所需的最小周期数
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, c, p = 0;
    cin >> a >> b >> c;
    if (b >= a) { cout << 0; return 0; }//每轮增长量b已经大于等于目标值a时，不需要任何周期
    for (int i = 1; ; ++i) {//开始无限循环，从i=1开始计数，每次递增1
        p += b;//累计的增长量
        if (p + b * c >= a * c) { cout << i; return 0; }
    }
}
