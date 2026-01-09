//
// Created by Psy.C on 2026/1/8.
//
/**
* n：输入的整数，表示集合大小
k：约束条件数量
idx[2]：存储两个约束值的数组
 *
*i-low_bit(i)：去掉i的最低位1
low_bit(i)：最低位1对应的数值
 *
*~low_bit(j)：low_bit(j)的按位取反
i&~low_bit(j)：从i中去掉j的最低位1，得到i的一个子集
 *
* sum[i-low_bit(i)] = sum[12] = sum[1100₂]：表示集合 {2, 3} 的元素和
sum[low_bit(i)] = sum[1] = sum[0001₂]：表示集合 {0} 的元素和
sum[i] = sum[12] + sum[1]：表示集合 {0, 2, 3} 的元素和
 *
 *sum[子集] + sum[单元素集合]
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000007
using namespace std;
//low_bit(12) = low_bit(1100₂) = 100₂ = 4
int low_bit(const int x) { return x & -x; }

int main() {
    fast;
    int n, k, idx[2]; cin >> n;
    vector<int> a(1<<n);
    vector<ll> sum(1<<n), dp(1<<n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; sum[1<<i] += a[i];//将单个元素a[i]放在对应的状态2^i中
    }
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> idx[i]; dp[0] = 1;//空集的方案数为1
    for (int i = 1; i < 1<<n; ++i) {//遍历所有非空子集（状态从1到2^n-1）
        sum[i] = sum[i-low_bit(i)] + sum[low_bit(i)];//状态i对应集合的元素和
        if (sum[i] == idx[0] || sum[i] == idx[1]) continue;//等于任一约束值
        for (int j = i; j; j -= low_bit(j)) {//枚举i的所有子集（通过去除每一位的1）
            dp[i] += dp[i&~low_bit(j)];//子集的方案数累加到当前状态
            if (dp[i] > mod) dp[i] -= mod;
        }
    }
    cout << dp[(1<<n)-1];//包含所有元素的集合的方案数 二进制全为1
    return 0;
}