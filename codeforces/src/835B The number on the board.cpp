//
// Created by Psy.C on 2026/9/25.
//
/**
读入阈值 k 和数字串 a。
len 为串长（数字个数）。
遍历每一位，用 a[i] - '0' 把字符转成数字，累加数位之和 s
对字符串 a 按字符（数字）升序排序。
排序后，a[0] 是最小的数字，a[len-1] 是最大的数字。
目的：后面贪心改数时，从最小的数字开始改，每次增量（9 - 该数字）最大
若当前数位和 s 已经 ≥ k，无需任何修改，直接输出 0
t 记录改了几个数字。
从 i=0 开始（最小数字优先），把 a[i] 改成 9：数位和增加 9 - (a[i]-'0')（即该位改 9 后净增的量）。
t++（改了一个数字）。
若 s 已达到 ≥ k，break 提前结束。
循环结束后输出 t，即需要改的最少数字个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
char a[N];
int k;
int main() {
    fast;
    cin >> k >> a;
    int len = strlen(a), s = 0;
    for (int i = 0; i < len; ++i) s += a[i] - '0';
    sort(a, a + len);
    if (s >= k) cout << 0 << '\n';
    else {
        int t = 0;
        for (int i = 0; i < len; ++i) {
            s += 9 - (a[i] - '0');
            t++;
            if (s >= k) break;
        }
        cout << t << '\n';
    }
    return 0;
}