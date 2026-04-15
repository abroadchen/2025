//
// Created by Psy.C on 2026/4/15.
//
/**
n：操作次数
x：初始值
num：当前计算器的值
a：每次操作的数值
s[10]：存储操作符（+ 或 -）
ans用于记录失败的减法操作次数，num设为初始值x
循环n次：处理每一个操作
读取操作：s存储操作符，a存储操作数
加法操作：如果操作符是'+'，将a加到当前值num上
减法操作：
如果当前值num小于操作数a，无法执行减法（结果会变成负数），ans计数器加1
否则执行减法操作，从num中减去a
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll x, num, a;
char s[10];
int main() {
    fast;
    cin >> n >> x;
    int ans = 0; num = x;
    for (int i = 0; i < n; ++i) {
        cin >> s >> a;
        if (s[0] == '+') num += a;
        else {
            if (num < a) ans++;
            else num -= a;
        }
    }
    cout << num << ' ' << ans << '\n';
    return 0;
}