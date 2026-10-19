//
// Created by Psy.C on 2026/10/19.
//
/**
原理：若序列是按宽 num 的网格按行展开得到的：

同行相邻两数的差 = 1（右移一位）。
跨行（同列上下）‍差 = num（下一行同列）。
所以在序列里，差 = 1 表示同行水平步；差 ≠ 1 的相邻差就是列宽 num，且所有非 1 差应相等。
第一遍找出这个唯一的 num，并检测不一致（差既不=1也不=num，或多次出现不同非1差 → NO）
差为 1 的两数必须在同一行（否则说明在行末又跳到下一行开头，形成伪相邻）。判断"所在行"用 (a-1)/num（把值映射到格子坐标），若行号不同则非法 → NO
输出 YES，并给出构造的网格参数：宽 = num，总列数 num，首行从 1000000000 开始（大数保证左边界不越界？实际是任选一个起点）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+1, inf = 1e9;

int n, a[N], num;
int main() {
    fast;
    cin >> n;
    rep(i,1,n) cin >> a[i];
    rep(i,2,n) {
        if (abs(a[i]-a[i-1]) == 1) continue;
        if (a[i] == a[i-1]) return cout << "NO", 0;
        if (num && abs(a[i]-a[i-1]) != num) return cout << "NO", 0;
        num = abs(a[i]-a[i-1]);
    }
    if (!num) num = inf;
    rep(i,2,n) if (abs(a[i]-a[i-1]) == 1 && (a[i]-1)/num != (a[i-1]-1)/num)
        return cout << "NO", 0;
    cout << "YES\n1000000000 " << num;
    return 0;
}