//
// Created by Psy.C on 2026/9/13.
//
/**
不断读取整数并累加到 s（读到 EOF 停止）。所以 s = 所有输入数字的和
s/100 = s 的百位。
string(个数, '+')：C++ 标准库，用指定个数的 '+' 字符构造字符串。这里个数 = 百位 + 48。
所以若百位为 k，就输出 k+48 个 '+'，再跟 ".>"。
if(s/100)：只有当百位非 0 才输出（即 s ≥ 100）
s/10%10 = s 的十位。
若十位为 t，输出 t+48 个 '+'，再跟 ".>"。
if (s/10%10 || s/100)：当十位非 0，或百位非 0（即大于等于 10 才输出这一节）‍。这是为了去掉前导零——若 s 像个位那样 < 10，就不输出十位段
s%10 = s 的个位。输出 个位+48 个 '+'，再跟 ".>"。这一节无条件执行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x, s = 0;
    while (cin >> x) s += x;
    if (s/100) cout << string(s/100+48, '+') << ".>";
    if (s/10%10 || s/100) cout << string(s/10%10+48, '+') << ".>";
    cout << string(s%10+48, '+') << ".>";
    return 0;
}