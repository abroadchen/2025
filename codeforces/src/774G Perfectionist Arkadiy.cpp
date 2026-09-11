//
// Created by Psy.C on 2026/9/11.
//
/**
a 是目标正方形的边长，h、w 是原长方形的两维
可行性判断：若 g < a（最大公约数连 a 都达不到），或 a 大于 h 或大于 w（正方形边长不能超过长方形任一边），输出 -1（无解）
有解时：ans = (double)g / (g/a)，因为 g 是 (h+a) 与 (w+a) 的公约数，g/a 是某个整数系数；(double)g/(g/a) 计算得到整数 g 除以 g/a = a（精确值恰好是 a），再 ans - a。
注意：这里 ans = g / (g/a) = a（数学上恰好等于 a），所以 ans - a = 0。也就是说，在满足 gcd 条件的情况下，程序输出的总是 0。
这一点值得指出：(double)g/(g/a) 在数学上恒等于 a，因此 ans - a 恒为 0。所以这段代码的"输出分支"实际上只会输出 0（当有解时）或 -1（无解时），它并不是在算一个非零的"剩余量"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int a, h, w;
double ans;
int main() {
    fast;
    cin >> a >> h >> w;
    int g = gcd(h+a, w+a);
    if (g < a || a > h || a > w) cout << "-1\n";
    else {
        ans = (double)g/(g/a);
        cout << ans-a << '\n';
    }
    return 0;
}