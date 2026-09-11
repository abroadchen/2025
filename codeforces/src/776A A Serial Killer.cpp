//
// Created by Psy.C on 2026/9/11.
//
/**
while (cin >> a >> b)：循环读入，直到输入结束（EOF）为止。每一轮读入两个初始字符串 a、b——这通常代表每轮测试的初始两个物体/名字（例如两个初始的物质或变量）。
立刻把当前两个名字 a b 输出一行
读入 n（本轮的步数/变换次数）。
然后循环 n 次，每次读入一对替换关系 c d（含义一般是："c 出现了就把它换成 d"）
如果当前名字 a 恰好等于被替换对象 c，就把 a 改成 d；否则把 b 改成 d。
每次替换后输出当前 a b 这一行的最新状态
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string a, b, c, d;
int n;
int main() {
    fast;
    while (cin >> a >> b) {
        cout << a << ' ' << b << '\n';
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> c >> d;
            if (a == c) a = d; else b = d;
            cout << a << ' ' << b << '\n';
        }
    }
    return 0;
}