//
// Created by Psy.C on 2026/1/31.
//
/**
* dp[state][remainder]：在给定状态下的方案数
fac：阶乘数组
初始化dp[0][0]=1（空状态，余数为0的方案数为1）
初始化fac[0]=1
 *
*s[i]-48：将字符转换为数字（ASCII码转换）
fac[i+1] = fac[i]*(i+1ll)：计算(i+1)!
num[s[i]-48]++：统计对应数字出现次数
 *
*外层：遍历所有可能的状态i
中层：遍历所有可能的余数k
内层：遍历所有数字位置j
x = s[j] - 48：获取位置j的数字
if (x == 0 && i == 0) continue;：避免前导零（当状态为空时不能添加0）
if (1<<j&i) continue;：如果位置j已经被使用，跳过
y = 1<<j|i：在状态i中添加位置j的新状态
z = (k*10+x)%m：新的余数
dp[y][z] += dp[i][k]：转移方案数
 *
*计算重复数字的排列数修正
t = fac[num[0]] * fac[num[1]] * ... * fac[num[9]]
这是因为相同数字的排列应该被视为相同
 *
 *dp[tot-1][0]表示使用所有数字且余数为0的方案数
 *除以t消除重复数字的重复计算
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1<<18//2^18=262144
using namespace std;


int main() {
    fast;
    char s[50]; cin >> s;
    int m; cin >> m;
    const int n = static_cast<int>(strlen(s)), tot = 1<<n;//所有可能的子集状态数
    int num[N]={};//统计每个数字出现的次数
    ll dp[N][107]={}, fac[N]={}; dp[0][0] = 1; fac[0] = 1;
    for (ll i = 0; i < n; ++i) {
        fac[i+1] = fac[i]*(i+1ll);
        num[s[i]-48]++;
    }
    for (int i = 0; i < tot; ++i) for (int k = 0; k < m; ++k) {
        if (!dp[i][k]) continue;
        for (int j = 0; j < n; ++j) {
            const int x = s[j] - 48;
            if (x == 0 && i == 0) continue;
            if (1<<j&i) continue;
            const int y = 1<<j|i, z = static_cast<int>((k*10ll+x)%m);
            dp[y][z] += dp[i][k];
        }
    }
    ll t = 1;
    for (int i = 0; i < 10; ++i) t *= fac[num[i]];
    cout << dp[tot-1][0]/t << '\n';
    return 0;
}