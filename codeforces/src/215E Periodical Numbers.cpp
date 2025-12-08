//
// Created by Psy.C on 2025/12/7.
//
/*
*cnt：二进制位数计数器
a[N]：存储二进制位的数组
dp[N]：动态规划数组，用于计算周期性二进制数
 *
*计算特定长度和周期的二进制数个数：
参数：len（总长度）、k（周期长度）、n（上界）
x：提取周期部分的数值
y：构造完整的重复周期数
返回满足条件的周期性数的个数
 *
*计算从1到n中满足条件的数的个数：
将n转换为二进制并存储在数组a中
cnt记录二进制位数
*遍历可能的二进制长度i（从2到位数cnt）
对于每个长度i，检查其因数j
如果i小于总位数cnt，直接计算周期性数个数
否则调用get函数精确计算
使用容斥原理去除重复计算
累加结果
 *使用前缀和思想计算区间内的结果：f(r) - f(l-1)
 *
 *从 0 到 x 共有 x + 1 个数
*k位二进制数总共有 2^k 个，其中一半(2^(k-1))以 1 开头
所以减去以 0 开头的那一半
*如果构造的完整周期数 y 超过了上界 n
则需要减去 1，因为这个数不合法
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 66
using namespace std;

int cnt, a[N];
ll dp[N];


ll get(const int len, const int k, const ll n) {
    ll x = 0, y = 0;
    for (int i = 0; i < k; ++i) x = 2ll * x + a[cnt - i - 1];//高位到低位
    for (int i = 0; i < len / k; ++i) y = (y << k) + x;
    return x + 1 - (1<<(k-1)) - (y > n);
}


ll f(const ll n) {
    cnt = 0;
    ll x = n, ans = 0;
    while (x) a[cnt++] = static_cast<int>(x) % 2, x /= 2;
    for (int i = 2; i <= cnt; ++i) {
        memset(dp, 0, sizeof(dp));
        for (int j = 1; j < i; ++j) if (i % j == 0) {
            if (i < cnt) dp[j] = 1ll<<(j-1);//最高位必须为1
            else dp[j] = get(i, j, n);
            for (int k = 1; k < j; ++k) if (j % k == 0) {
                dp[j] -= dp[k];
            }
            ans += dp[j];
        }
    }
    return ans;
}

int main() {
    fast;
    ll l, r; cin>>l>>r;
    cout << f(r) - f(l - 1) << '\n';
    return 0;
}