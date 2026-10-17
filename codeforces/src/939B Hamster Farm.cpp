//
// Created by Psy.C on 2026/10/17.
//
/**
mn 初始化为 10^18（一个很大的数，作为"最小值"初值）；id 记录最优的编号；num 记录对应商；a 接收每次读入的数。
读入 n（某总量）与 k（可选项个数
对第 i 个选项：
cin >> a;：读入这个选项的数值 a。
if (n%a < mn) mn=n%a, id=i, num=n/a;：计算 n % a（n 除以 a 的余数），若该余数小于当前最小值 mn，则更新：mn=余数、id=当前选项序号 i、num = n / a（n 除以 a 的商）。
循环结束后输出 id 与 num，即 cout << id << ' ' << num;
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;


int main() {
    fast;
    ull n, k, mn = pow(10, 18), id = 0, num = 0, a;
    cin >> n >> k;
    for (ull i = 1; i <= k; ++i) {
        cin >> a;
        if (n%a < mn) mn = n%a, id = i, num = n/a;
    }
    cout << id << ' ' << num;
    return 0;
}