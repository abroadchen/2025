//
// Created by Psy.C on 2026/1/16.
//
/**
* 如果没有0，输出"-1"
因为要构造能被90整除的数，必须有0才能被10整除
*否则，如果5的个数少于9个，输出"0"
因为要被9整除，各位数字之和必须是9的倍数
5的倍数中只有9个5（即45）是9的倍数
如果5的个数少于9个，无法构造出被9整除的数
 *
*c5 / 9: 能组成几个完整的9个5
* 9: 乘以9得到实际使用的5的个数
 *
*循环输出num个字符'5'
这些5构成数字的前半部分
*循环输出c0个字符'0'
这些0构成数字的后半部分，确保能被10整除
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, c0 = 0, c5 = 0; cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (x == 5) c5++; else c0++;
    }
    if (c0 == 0) cout << "-1\n";
    else if (c5 < 9) cout << "0\n"; else {
        const int num = c5 / 9 * 9;
        for (int i = 0; i < num; ++i) cout << "5";
        for (int i = 0; i < c0; ++i) cout << "0";
        cout << '\n';
    }
    return 0;
}