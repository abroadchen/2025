//
// Created by Psy.C on 2026/3/30.
//
/**
这是在计算i!末尾零的个数
累加 floor(i/5) + floor(i/25) + floor(i/125) + ...
如果等于m，找到解
如果超过m，说明无解

单调性：f(n)单调不减
跳跃性：当n是5的倍数时，f(n)可能增加
要么有5个连续的n使得f(n)=m（当存在解时）
要么不存在这样的n（当m是跳跃中缺失的值）

为什么从5的倍数开始？
只有当n是5的倍数时，f(n)才可能发生变化
所以只需检查5的倍数
为什么找到第一个解就输出连续5个？
当f(n)=m时，接下来的4个数f(n+1)=f(n+2)=f(n+3)=f(n+4)=m
因为n+1, n+2, n+3, n+4都不是5的倍数，不会增加因子5
为什么超出m就无解？
如果f(i) > m，由于f(n)单调，之后的f(n)都大于m
所以不存在f(n)=m的情况
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int m;
int main() {
    fast;
    cin >> m;
    int flag = -1, i;
    for (i = 5; ; i += 5) {
        flag = 0;
        for (int j = 5; j <= i; j *= 5)
            flag += i/j;
        if (flag == m) break;
        if (flag > m) {
            cout << "0\n";
            return 0;
        }
    }
    cout << "5\n";//解的个数
    for (int j = 0; j < 5; ++j)
        cout << i+j << ' ';//输出5个连续解
    return 0;
}