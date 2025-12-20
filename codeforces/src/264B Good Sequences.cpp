//
// Created by Psy.C on 2025/12/20.
//
/*
*埃拉托斯特尼筛法生成质数表：
初始化所有数为质数(true)
0和1不是质数
从2开始筛选，如果i是质数，则i的所有倍数都不是质数
只需筛选到√N
 *
 *n(数组长度)、dp(动态规划数组)、a(输入数组)、ans(答案)
 *如果只有一个元素，答案是1
*t：以当前元素结尾的最长序列长度
x：当前元素的副本
分解质因数：对每个质因子j，计算dp[j] + 1的最大值
如果最后x>1，说明x本身是一个质因子
*重新设置x为原值
对所有质因子，将dp[质因子]更新为t
更新全局最大值
 *
 *dp[p]表示以质数p为公共因子的最长子序列长度
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100007
using namespace std;

bool pri[N];
void init() {
    memset(pri, true, sizeof(pri));
    pri[0] = pri[1] = false;
    for (int i = 2; i * i < N; ++i) {
        if (!pri[i]) continue;
        for (int j = i * i; j < N; j += i)
            pri[j] = false;
    }
}


int main() {
    fast;
    init(); int n, dp[N], a[N], ans = 0; cin >> n;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; ++i) cin >> a[i];
    if (n == 1) { cout << "1" << '\n'; return 0; }
    for (int i = 0; i < n; ++i) {
        int t = 0, x = a[i];
        for (int j = 2; j * j <= x; ++j) {
            if (x % j) continue;
            if (!pri[j]) continue;
            while (x % j == 0) x /= j;
            t = max(t, dp[j] + 1);
        }
        if (x > 1) t = max(t, dp[x] + 1);
        x = a[i];
        for (int j = 2; j * j <= x; ++j) {
            if (x % j) continue;
            if (!pri[j]) continue;
            while (x % j == 0) x /= j;
            dp[j] = t;
        }
        if (x > 1) dp[x] = t;
        ans = max(ans, t);
    }
    cout << ans << '\n';
    return 0;
}