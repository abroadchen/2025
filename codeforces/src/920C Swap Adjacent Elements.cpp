//
// Created by Psy.C on 2026/10/14.
//
/**
a[N]：存放排列（1..n 的某个排列）。
mx：前缀最大值（扫描过程中维护）。
s[N]：交换标记字符串，s[i] 表示位置 i 与 i+1 之间能否交换
mx = max(mx, a[i])：把 a[i] 并入前缀最大值，得到 前缀 [1..i] 中的最大元素。
判断 if (s[i] == '0' && i != mx)：
s[i] == '0' 表示 位置 i 和 i+1 之间不可交换，即数组在这里被"切开"成两块。
i != mx 表示前缀 [1..i] 里的最大值不是 i 本身。
两者同时成立 → 无法排序，输出 NO 并结束。
若条件不成立，继续扫描
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5+10;

int n, a[N], mx;
char s[N];
int main() {
    scanf ("%d", &n);
    for (int i = 1; i <= n; ++i) scanf ("%d", &a[i]);
    scanf("%s", s+1);
    for (int i = 1; i < n; ++i) {
        mx = max(mx, a[i]);
        if (s[i] == '0' && i != mx) { puts("NO"); return 0; }
    }
    puts("YES");
    return 0;
}