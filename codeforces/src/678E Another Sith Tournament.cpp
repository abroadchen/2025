//
// Created by Psy.C on 2026/4/14.
//
/**
f[1<<n]: DP数组，f[mask]表示状态mask下的最大值
f[1] = 1: 只选择第0个元素时的初始值为1
外层循环：for (int m = 2; m < 1<<n; ++m)
遍历所有可能的状态（二进制掩码）
中层循环：for (int i = 0; i < n; ++i)
if (~m>>i&1) continue;: 如果第i位不在mask中，跳过
检查mask中的每个位置i
内层循环：for (int j = 0; j < n; ++j)
if (~m>>j&1) continue;: 如果第j位不在mask中，跳过
检查mask中的每个位置j
m^(1<<i): 移除第i位的状态
m^(1<<j): 移除第j位的状态
从移除i或j的状态转移而来
计算 f[去掉i]*a[j][i] + f[去掉j]*a[i][j] 的最大值

~m>>i&1: 检查m的第i位是否为0
m^(1<<i): 将m的第i位取反（移除或添加第i个元素）
f.back(): f数组的最后一个元素，即f[(1<<n)-1]

时间复杂度O(n²×2ⁿ)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

template<typename T>
void mxx(T& x, T y) { if (x < y) x = y;}

int n;
int main() {
    fast;
    cin >> n;
    vector a(n, vector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> a[i][j];
    vector<double> f(1<<n); f[1] = 1;
    for (int m = 2; m < 1<<n; ++m)
        for (int i = 0; i < n; ++i) {
            if (~m>>i&1) continue;
            for (int j = 0; j < n; ++j) {
                if (~m>>j&1) continue;
                mxx(f[m], f[m^(1<<i)]*a[j][i]+f[m^(1<<j)]*a[i][j]);
            }
        }
    cout << fixed << setprecision(12) << f.back() << '\n';
    return 0;
}