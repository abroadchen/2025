//
// Created by Psy.C on 2026/4/13.
//
/**
a[N]: 存储序列的数组
cnt: 当前数组中元素的个数
n: 查询位置
一位数 (1-9)：
直接将数字本身存入数组
例如：1 → 存入1
两位数 (10-99)：
拆分成十位和个位
s = i/10: 十位数字
g = i%10: 个位数字
例如：12 → 存入1, 2
三位数 (100-999)：
拆分成百位、十位、个位
b = i/100: 百位数字
s = i%100/10: 十位数字
g = i%10: 个位数字
例如：123 → 存入1, 2, 3

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e4+5;
int a[N], cnt, n;
int main() {
    fast;
    for (int i = 1; i <= 999; ++i) {
        if (i >= 1 && i <= 9) a[++cnt] = i;
        else if (i >= 10 && i <= 99) {
            int s = i/10, g = i%10;
            a[++cnt] = s; a[++cnt] = g;
        } else if (i >= 100) {
            int b = i/100, s = i%100/10, g = i%10;
            a[++cnt] = b; a[++cnt] = s; a[++cnt] = g;
        }
    }
    cin >> n; cout << a[n];
    return 0;
}