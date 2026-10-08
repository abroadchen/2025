//
// Created by Psy.C on 2026/10/8.
//
/**
读入 6 个整数 a[0]..a[5]，并累加得到总和 sum。
三层循环，索引满足 i < j < k，枚举所有 C(6,3)=20 种"选 3 个数"的组合。
i+1、j+1 的起点保证不重不漏、且避免重复组合
s 为当前三个数之和；sum - s 为剩下三个数之和。
若两者相等，说明这 6 个数能分成两组、每组三个且和相等 → 输出 yes 并结束
20 种组合都不满足，输出 no
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[6], i, j, k, sum, s;
int main() {
    fast;
    for (i = 0; i < 6; ++i) { cin >> a[i]; sum += a[i]; }
    for (i = 0; i < 6; ++i)
        for (j = i+1; j < 6; ++j)
            for (k = j+1; k < 6; ++k) {
                s = a[i] + a[j] + a[k];
                if (s == sum - s) {
                    cout << "yes\n";
                    return 0;
                }
            }
    cout << "no\n";
    return 0;
}