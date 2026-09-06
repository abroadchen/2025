//
// Created by Psy.C on 2026/9/6.
//
/**
计算余数：b %= a
将 b 更新为 b % a（即 b 除以 a 的余数）。
此时 b 的值已经改变，但 a 仍保持不变。
异或交换：a ^= b ^= a ^= b
这是一段经典的“异或三连环”技巧，用于在不使用临时变量的情况下互换 a 和 b 的值。
执行完这一行后，a 和 b 的值被交换：a 变成了旧的 b（即余数），b 变成了旧的 a。
循环判断：while (a)
* 循环继续执行的条件是 a != 0。
当 a 为 0 时，循环结束，此时 b 就是两数的最大公约数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(int a, int b) {
    while (a^=b^=a^=b%=a) {}
    return b;
}

int main() {
    fast;
    int n, m, z; cin >> n >> m >> z;
    int lcm = (n*m)/gcd(n,m);//n 和 m 的最小公倍数 (LCM)
    cout << z/lcm << '\n';//输出能整除 LCM 的 z 的个数
    return 0;
}