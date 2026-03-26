//
// Created by Psy.C on 2026/3/26.
//
/**
读入n（区间数）和m（整除基数）
循环处理n个区间[l,r]：
t = r/m - l/m：计算区间[l,r]内能被m整除的数的个数
r/m：0到r内能被m整除的数的个数
l/m：0到l-1内能被m整除的数的个数
相减得到区间[l,r]内能被m整除的数的个数
if (l%m == 0) t++：如果l本身能被m整除，需要额外加1
p[i] = 1. - (double)t/(r - l + 1)：计算区间内不能被m整除的概率
t/(r-l+1)：能被m整除的概率
1 - t/(r-l+1)：不能被m整除的概率

遍历相邻区间对(i, i+1)：
p[i]*p[i+1]：区间i和区间i+1都不能被m整除的概率
1 - p[i]*p[i+1]：至少有一个区间能被m整除的概率
乘以2000（费用系数）
最后一项连接首尾：区间n和区间1的配对
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, m;
double p[N], ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, l, r; i <= n; ++i) {
        cin >> l >> r;
        int t = r/m - l/m;
        if (l%m == 0) t++;
        p[i] = 1. - (double)t/(r - l + 1);
    }
    for (int i = 1; i < n; ++i)
        ans += (1 - p[i]*p[i+1]) * 2000;
    ans += (1 - p[n]*p[1]) * 2000;
    printf("%.7lf\n", ans);
    return 0;
}