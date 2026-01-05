//
// Created by Psy.C on 2026/1/5.
//
/**
 * 当只有普通元素（非特殊元素）时，从 j-1 个元素的排列数推导到 j 个元素的排列数
*dp[0][j] = dp[0][j-1] × j
这实际上计算的是 j!（j的阶乘）
*i 表示特殊元素（值为1）的数量
j 表示普通元素（值不为1）的数量
当 i=0 时，只有普通元素，就是简单的全排列问题
dp[0][j] = j! 表示 j 个不同普通元素的排列数

*dp[i][j-1]: 已有 j-1 个元素的排列方案数
*j: 新元素可以插入到 j 个不同位置（j 个间隙）
总方案数 = 原方案数 × 新元素插入位置数
所以"在 j 个普通元素的排列中增加一个元素"就是计算 j 个不同元素的全排列数量
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 510
#define mod 1000000007
using namespace std;

ll dp[N][N];
void init(const int n) {
    for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) {//遍历所有可能的 i、j 组合
        dp[i][j] = 0;//边界条件 当前位置
        if (!i && !j) { dp[i][j] = 1; continue; }//跳过后续处理
        //在 j 个普通元素的排列中增加一个元素
        if (i == 0) { dp[i][j] += dp[i][j-1]*j; dp[i][j]%=mod; continue; }//没有特定限制时，j 个元素的某种排列数
        //不给当前特殊元素分配位置的方案数
        dp[i][j] += dp[i-1][j]; dp[i][j] %= mod;//不添加新限制
        //将一个普通元素放在某个位置的方案数
        if (j) { dp[i][j] += j*dp[i][j-1]; dp[i][j] %= mod; }//在j个位置中选择一个
        if (i >= 2) {//至少有两个特殊元素
            ll cur = i - 1;//第一个特殊元素有 (i-1) 种配对选择
            for (int k = 0; k <= j; ++k) {//枚举 j 个元素的分配方式 一对特殊元素分配 k 个普通元素
                dp[i][j] += cur * dp[i-2][j-k]; dp[i][j] %= mod;//选择方案数 处理完一对特殊元素后的方案数
                cur *= j - k; cur %= mod;//成对元素的排列 j-k 是选择普通元素的方案数
            }
        }
    }
}


int main() {
    fast;
    int n, b = 0; init(500);
    cin >> n;
    for (int i = 0, a; i < n; ++i) {
        cin >> a;
        if (a == 1) b++;
    }
    cout << dp[b][n-b] << '\n';
    return 0;
}