//
// Created by Psy.C on 2025/12/4.
//
/*
 *
*正向动态规划计算前缀最优值：
sum[0][i]：到第i个位置为止，不强制选择第i个元素时的最大和
从前一个位置的两种状态中选择较大的
加上当前元素值，如果当前元素是偶数则减去1（相当于取floor((a[i]-1)/2)的效果）
sum[1][i]：到第i个位置为止，强制选择第i个元素时的最大和
只有当a[i]>1时才有意义
如果a[i]≤1，则sum[1][i]=0（因为选择它没有收益）
 *
*反向动态规划计算后缀最优值：
suf[0][i]：从第i个位置到末尾，不强制选择第i个元素时的最大和
suf[1][i]：从第i个位置到末尾，强制选择第i个元素时的最大和
 *
*合并前缀和后缀的结果，考虑三种组合情况：
sum[0][i] + suf[1][i+1]：前缀不强制选择，后缀强制选择
sum[1][i] + suf[0][i+1]：前缀强制选择，后缀不强制选择
sum[1][i] + suf[1][i+1]：前缀和后缀都强制选择
 *
 *时间复杂度是O(n)，空间复杂度也是O(n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

int n;
ll a[N], sum[2][N], suf[2][N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i < n; ++i) cin >> a[i];
    for (int i = 1; i < n; ++i) {
        sum[0][i] = max(sum[1][i-1], sum[0][i-1]) +
            a[i] - (a[i] % 2 == 0);
        if (a[i] > 1) sum[1][i] = sum[1][i-1] + a[i] -
            (a[i] % 2 == 1);
        else sum[1][i] = 0;
    }
    for (int i = n - 1; i >= 1; --i) {
        suf[0][i] = max(suf[1][i+1], suf[0][i+1]) +
            a[i] - (a[i] % 2 == 0);
        if (a[i] > 1) suf[1][i] = suf[1][i+1] + a[i] -
            (a[i] % 2 == 1);
        else suf[1][i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        ans = max(ans, sum[0][i] + suf[1][i+1]);
        ans = max(ans, sum[1][i] + suf[0][i+1]);
        ans = max(ans, sum[1][i] + suf[1][i+1]);
    }
    cout << ans;
    return 0;
}