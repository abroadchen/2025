//
// Created by Psy.C on 2026/1/19.
//
/**
* dp[i][j]：动态规划数组，表示到位置i、代价为j的方案数
sum[j]：前缀和数组，sum[j]表示所有dp[][j]的和
 *
 *位置0代价0的方案数为1
 *代价为0的总方案数为1
 *
*计算从之前状态转移到位置i的贡献
1LL 确保乘法使用long long类型
s[i] - 'a'：当前字符相对于'a'的偏移量
从所有代价为j的状态继承，乘以字符偏移量
*内层循环：从位置i-1向前查找可能的转移来源
k >= 0 && (i - k) * (n - i + 1) <= j：边界条件
(i - k) * (n - i + 1)：计算转移代价
j - (i - k) * (n - i + 1)：剩余代价
('z' - s[i])：从当前字符到'z'的偏移量
使用add函数安全地加上转移贡献
 *
 *区间 [k+1, i] 的修改会影响到后面的 n - i + 1 个位置，总的影响量是两者的乘积
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2007
#define mod 1000000007
using namespace std;

template<class T, class S>
void add(T& a, S b) {a += b; if(a >= mod) a -= mod;}
int n, m;
int dp[N][N];
int sum[N];
char s[N];

int main() {
    scanf("%d%d%s", &n, &m, s + 1);
    dp[0][0] = 1;
    sum[0] = 1;
    for(int i = 1; i <= n; i++) {//处理每个字符位置
        for(int j = 0; j <= m; j++) {//处理每个可能的代价
            dp[i][j] = 1LL * sum[j] * (s[i] - 'a') % mod;
            for(int k = i - 1; k >= 0 && (i - k) * (n - i + 1) <= j; k--)//代价不超过当前预算 j
                add(dp[i][j], 1LL * dp[k][j - (i - k) * (n - i + 1)] * ('z' - s[i]) % mod);
            add(sum[j], dp[i][j]);//将当前位置的方案数加入前缀和数组
        }
    }
    int ans = 0;
    for(int i = 0; i <= n; i++) add(ans, dp[i][m]);//代价恰好为m的方案数累加
    printf("%d\n", ans);
    return 0;
}