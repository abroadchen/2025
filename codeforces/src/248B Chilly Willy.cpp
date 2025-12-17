//
// Created by Psy.C on 2025/12/16.
//
/*
 *210是能被2,3,5,7整除的最小三位数
*对于a>3的情况：
初始化b=100（表示10的2次方）
循环a-3次，每次将b乘以10再对210取模
这实际上是在计算10^(a-1) mod 210
 *计算需要补足的数值，使得整个数能被210整除
 *
*如果b<100：输出"1" + (a-3)个"0" + b
如果b≥100：输出"1" + (a-4)个"0" + b
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a; cin>>a;
    if (a == 1 || a == 2) cout << "-1";
    else if (a == 3) cout << "210";
    else {
        int b = 100;
        for (int i = 0; i < a - 3; ++i) {
            b = b * 10;
            b = b % 210;
        }
        b = 210 - b;
        if (b < 100) {
            cout << "1";
            for (int i = 0; i < a - 3; ++i) cout << "0";
            cout << b;
        } else {
            cout << "1";
            for (int i = 0; i < a - 4; ++i) cout << "0";
            cout << b;
        }
    }
    return 0;
}