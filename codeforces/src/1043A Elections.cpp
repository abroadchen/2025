//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
n：元素个数
a[N]：数组
s1：所有元素的和
s2：临时累加（某 k 下"补全"的总量）
读入并累加得到 s1 = Σa。
降序排序（cmp 返回 a > b）。排序本身在这个算法里其实不影响结果——因为 s1 和 s2 都和顺序无关，只和值有关。排序在这里主要是冗余/习惯写法
从 k = a[1]（数组最大值，因为降序排序所以是最大元素）开始递增枚举。
对每个 k，计算 s2 = Σ(k - a[i])，即把所有元素"补到 k"所需的补足量。
当 s2 > s1 时，输出当前 k 并结束
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 110;

bool cmp(int a, int b) { return a > b; }

int n, a[N], s1, s2;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i], s1 += a[i];
    sort(a+1, a+n+1, cmp);
    for (int k = a[1]; ; k++) {
        s2 = 0;
        for (int i = 1; i <= n; i++) s2 += k - a[i];
        if (s2 > s1) { cout << k; return 0; }
    }
    return 0;
}