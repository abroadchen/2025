//
// Created by Psy.C on 2026/4/22.
//
/**
n: 字符串长度
a[N]: 输入字符数组
m, t, u, v: 计数器
m: 偶数位置上的'r'
t: 偶数位置上的'b'
u: 奇数位置上的'r'
v: 奇数位置上的'b'
"rbrb..." 模式的最少操作数
"brbr..." 模式的最少操作数
两个模式中操作数更少的那个
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;
int n, m, t, u, v;
char a[N];
int main() {
    fast;
    cin >> n;
    cin >> a;
    for (int i = 0; i < n; ++i) {
        if (i%2 == 0) {
            if (a[i] == 'r') m++;
            if (a[i] == 'b') t++;
        } else {
            if (a[i] == 'r') u++;
            if (a[i] == 'b') v++;
        }
    }
    int x = max(t, u), y = max(m, v), z = min(x, y);
    cout << z << '\n';
    return 0;
}