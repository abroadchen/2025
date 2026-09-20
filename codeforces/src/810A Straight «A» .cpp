//
// Created by Psy.C on 2026/9/20.
//
/**
n：当前题目数；k：每道题的满分（也是目标平均分）。
a[i]：当前每道题的得分；sum：当前总分
每次假设：再多“过” x 道题，每道得满分 k。

新总分 = sum + x*k
新题目数 = n + x
新平均分 w = (sum + x·k) / (n + x)
w + 0.5 再 floor，就是 C/C++ 里"四舍五入取整"的等价写法：
若 w 的小数部分 ≥ 0.5，则 floor(w+0.5) 进位；
若 < 0.5，则保持原整数部分。
floor(w+0.5) 等于平均分四舍五入后的整数值。
条件成立（floor(w+0.5) == k）：达标，停止，输出 x；否则 x++ 继续
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, a[110], sum = 0; cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    int x = 0;
    while (true) {
        double w = (double)(sum+x*k)/(n+x);
        if (floor(w+0.5) == k) break;
        x++;
    }
    cout << x << '\n';
    return 0;
}