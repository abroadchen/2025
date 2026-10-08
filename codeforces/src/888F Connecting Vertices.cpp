//
// Created by Psy.C on 2026/10/8.
//
/**
读入
n
×
n
n×n 的 0/1 矩阵 arr，arr[i][j] 表示点
i
,
j
i,j 之间是否有连接关系
dp[i][i][0]=1：长度为 1 的区间，作为基础状态
枚举区间长度 len、左端点 i、右端点 j。

dp[i][j][0]：不依赖
i
,
j
i,j 直接相连，把区间在某个
k
k 处切开合并，用 dp[i][k][1]（左段以
i
i 结尾被连接的状态）乘上右段
[
k
,
j
]
[k,j] 的总方案数。

dp[i][j][1]：仅当 arr[i][j]（
i
i 与
j
j 直接相连）时，把区间在
k
k 处切开，左段
[
i
,
k
]
[i,k] 总方案数乘右段
[
k
+
1
,
j
]
[k+1,j] 总方案数，表示
i
,
j
i,j 这条边被用作连接。

所有加法、乘法都对 mod=1e9+7 取模（宏 add/mul
输出整个区间
[
1
,
n
]
[1,n] 两种状态方案数之和 % mod
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define add(a,b) (((a)+(b))%mod)
#define Add(a,b) (a=add(a,b))
#define mul(a,b) ((a)*(b)%mod)
using namespace std;
constexpr int N = 510, mod = 1e9+7;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

bool arr[N][N];
int dp[N][N][2];
signed main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) arr[i][j] = rd();
    for (int i = 1; i <= n; ++i) dp[i][i][0] = 1;
    for (int len = 2; len <= n; ++len) {
        for (int i = 1, j = len; j <= n; ++i, ++j) {
            for (int k = i+1; k <= j; ++k)
                Add(dp[i][j][0], mul(dp[i][k][1], add(dp[k][j][0], dp[k][j][1])));
            if (arr[i][j]) {
                for (int k = i; k < j; ++k)
                    Add(dp[i][j][1], mul(add(dp[i][k][0], dp[i][k][1]),
                        add(dp[k+1][j][0], dp[k+1][j][1])));
            }
        }
    }
    cout << add(dp[1][n][0], dp[1][n][1]);
    return 0;
}