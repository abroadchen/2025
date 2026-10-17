//
// Created by Psy.C on 2026/10/16.
//
/**
x 记录出现 U 的个数，y 记录出现 R 的个数（这里只有两种方向 U 与 R）。

循环统计前缀中 U 与 R 的数量：

a[i]=='U' 则 x++，否则 y++（其他字符都算 R 方向）。
当 x == y（前缀中 U 和 R 数量相等，即处于对称中点）且 a[i] == a[i+1]（当前字符与下一个字符相同）时，ans++。
注意：代码里条件 a[i] == a[i+1] 在 i+1 越界时（i = n-1）访问 a[n]（未定义），这是代码的水平问题，但典型输入下 i 不会到 n-1 时 x==y 同时触发边界
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, x, y,ans;
string a;
int main() {
    fast;
    cin >> n >> a;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 'U') x++; else y++;
        if (x == y && a[i] == a[i+1]) ans++;
    }
    cout << ans;
    return 0;
}