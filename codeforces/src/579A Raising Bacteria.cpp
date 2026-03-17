//
// Created by Psy.C on 2026/3/16.
//
/**
循环结束条件：当 x < 2 时循环结束，即当 x == 1 或 x == 0 时停止
最高位的1没有被计算：当 x 最终变为 1 时，由于 1/2 == 0，循环提前结束了，所以最高位的 1 没有被 cnt++ 计算进去
加1是为了补偿循环中没有计算到的最高位的1（当x最终变为1时，这个1没有被统计到cnt中）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x, cnt;
int main() {
    fast;
    cin >> x;
    while (x/2 != 0) {//当x>=2时
        if (x&1) cnt++;
        x >>= 1;
    }
    cout << cnt+1;
    return 0;
}