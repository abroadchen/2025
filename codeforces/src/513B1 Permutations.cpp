//
// Created by Psy.C on 2026/2/27.
//
/**
这个分数是排列[1,2,3,...,n]中所有子数组最小值之和
对于位置i（1-indexed），它会在i*(n-i+1)个子数组中成为最小值
将数组a初始化为[1,2,3,...,n]（0-indexed）

cnt = 1：当前已找到的满足条件的排列计数（初始排列[1,2,3,...,n]已算作第一个）
next_permutation(a, a + n)：生成下一个字典序排列
计算当前排列的"分数"t：
遍历所有可能的子数组[i,j]
对每个子数组找到最小值mn
将所有子数组的最小值累加到t
如果当前排列的分数等于目标分数score，则计数器cnt加1
循环直到找到第k个满足条件的排列

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k, a[9];
int main() {
    fast;
    cin >> n >> k;
    int score = 0;
    for (int i = 1; i <= n; ++i) score += i*(n-i+1);
    for (int i = 0; i < n; ++i) a[i] = i + 1;
    int cnt = 1;
    while (cnt != k) {
        next_permutation(a, a + n);
        int t = 0;
        for (int i = 0; i < n; ++i)
            for (int j = i; j < n; ++j) {
                int mn = n;
                for (int x = i; x <= j; ++x)
                    mn = min(mn, a[x]);
                t += mn;
            }
        if (t == score) cnt++;
    }
    for (int i = 0; i < n-1; ++i) cout << a[i] << ' ';
    cout << a[n-1] << '\n';
    return 0;
}