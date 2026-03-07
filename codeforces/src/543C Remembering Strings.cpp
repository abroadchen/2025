//
// Created by Psy.C on 2026/3/7.
//
/**
n, m：网格的行数和列数
c[N][N]：成本矩阵
v[N][N]：优化后的价值矩阵
st[N][N]：状态掩码矩阵
dp[1<<21]：动态规划数组，状态压缩
s[N][N]：字符网格

对每个位置(i,k)：
遍历所有行j，找出与s[i][k]相同字符的行
v[i][k]累加相同字符的c值
mx记录最大c值
st[i][k] |= 1<<j：将与s[i][k]相同字符的行j设置在状态掩码中
v[i][k] -= mx：减去最大值，得到除最大值外的总和

dp[0] = 0：初始状态的成本为0
tot = (1<<n)-1：所有行都被选择的状态
外层循环：遍历所有可能的状态i
内层循环：找到第一个未被选择的行j（!(i>>j&1)表示j不在i中）
x = 1<<j：表示只选择第j行的状态
对每一列k：
y = st[j][k]：与s[j][k]相同字符的所有行的状态掩码
dp[i|x] = min(dp[i|x], dp[i] + c[j][k])：选择单行j
dp[i|y] = min(dp[i|y], dp[i] + v[j][k])：选择所有与s[j][k]相同字符的行
每次可以选择一行（成本c[j][k]）或选择所有具有相同字符的行（成本v[j][k]）
break：找到第一个未选择的行后就跳出内层循环
所有行都被选择的最小成本
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;
constexpr int N = 26;
int n, m, c[N][N], v[N][N], st[N][N], dp[1<<21];
char s[N][N];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> s[i];
    rep(i,n) rep(j,m) cin >> c[i][j];
    rep(i,n) rep(k,m) {
        int mx = 0;
        rep(j,n) {
            if (s[i][k] != s[j][k]) continue;
            v[i][k] += c[j][k];
            mx = max(mx, c[j][k]);
            st[i][k] |= 1<<j;
        }
        v[i][k] -= mx;
    }
    memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
    const int tot = (1<<n)-1;
    rep(i,tot) for (int j = 0; ; ++j) {
        if (!(i>>j&1)) {
            const int x = 1<<j;
            rep(k,m) {
                const int y = st[j][k];
                dp[i|x] = min(dp[i|x], dp[i] + c[j][k]);
                dp[i|y] = min(dp[i|y], dp[i] + v[j][k]);
            }
            break;
        }
    }
    cout << dp[tot] << '\n';
    return 0;
}