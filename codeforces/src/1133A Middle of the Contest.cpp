//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
N=60，表示 1 小时 = 60 分钟，用于六十进制换算。
两个时间分别记为 (a:b) 和 (c:d)
读入格式 a:s:b:c:s:d，即两个 hh:mm，中间的冒号被 s 吸收（读两次冒号，两次都付给同一个 s，第二次覆盖）
a*N+b = 把第一个时间转成「总分钟数」（时×60+分）。
c*N+d = 第二个时间总分钟数。
两者相加再 /2 = 两个时间的平均总分钟数（可能为小数，整数除法会向下取整）
f/N：平均分钟数 ÷ 60 = 小时部分。
f%N：平均分钟数 mod 60 = 分钟部分。
若小时 < 10 先输出 0，保证两位；输出 :；分钟同理补零。
结果形如 HH:MM，例如平均值为 7 小时 30 分钟输出 07:30
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
constexpr int N = 60;
int a, b, c, d;
char s;
int main() {
    fast;
    cin >> a >> s >> b >> c >> s >> d;
    int f = (a*N+b+c*N+d)/2;
    if (f/N < 10) cout << 0;
    cout << f/N << ':';
    if (f%N < 10) cout << 0;
    cout << f%N;
    return 0;
}