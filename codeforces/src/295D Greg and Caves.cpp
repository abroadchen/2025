//
// Created by Psy.C on 2025/12/31.
//
/**
 * 初始化第一行：dp[1][2]到dp[1][m]都设为1
*计算第一行的前缀和：
s1[1][j]：dp[1][1]到dp[1][j]的和
s2[1][j]：dp[1][1]*1到dp[1][j]*j的和
 *
*根据公式dp[i][j] = (-s2[i-1][j] + s1[i-1][j] * (j+1)) % mod计算新值
同时更新当前行的前缀和数组s1和s2
 *
*s[i][j]：dp数组关于行的前缀和
s3[i][j]：s数组关于列的前缀和
s4[i][j]：s数组乘以列索引的前缀和
 *
*遍历所有位置(i,j)
将s[i][j]与后续部分的贡献相乘
后续部分的计算公式：(s3[n-i][j-1] * (j + 1) - s4[n-i][j-1] + mod + 1)
再乘以(m-j+1)的权重
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 2005
#define mod 1000000007
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define rep2(i,n) for (int i=2; i<=(n); ++i)
using namespace std;


int main() {
    fast;
    ll n, m, dp[N][N], s1[N][N], s2[N][N]; cin >> n >> m;
    rep2(i,m) dp[1][i] = 1;
    rep2(j,m) {
        s1[1][j] = (s1[1][j-1] + dp[1][j]) % mod;
        s2[1][j] = (s2[1][j-1] + dp[1][j] * j % mod) % mod;
    }
    rep2(i,n) {
        rep2(j,m) dp[i][j] = (-s2[i-1][j]+s1[i-1][j]*(j+1)%mod+mod)%mod;
        rep2(j,m) {
            s1[i][j] = (s1[i][j-1] + dp[i][j]) % mod;
            s2[i][j] = (s2[i][j-1] + dp[i][j] * j % mod) % mod;
        }
    }
    ll ans = 0, s[N][N], s3[N][N], s4[N][N];
    rep(i,n) rep2(j,m) s[i][j] = (s[i-1][j] + dp[i][j]) % mod;
    rep(i,n) rep2(j,m) s3[i][j] = (s3[i][j-1] + s[i][j]) % mod;
    rep(i,n) rep2(j,m) s4[i][j] = (s4[i][j-1] + s[i][j] * j % mod) % mod;
    rep(i,n) rep2(j,m) {
        ans = (ans + s[i][j] * (s3[n-i][j-1] * (j + 1) % mod -
            s4[n-i][j-1] + mod + 1) % mod * (m - j + 1) % mod) % mod;
    }
    cout << ans << '\n';
    return 0;
}