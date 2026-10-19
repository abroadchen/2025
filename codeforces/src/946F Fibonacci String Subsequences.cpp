//
// Created by Psy.C on 2026/10/18.
//
/**
f[i][j][k] 是一个三维 DP：i 表示"某种代数/代数"，[j,k] 表示原字符串 s 的一个区间（j 到 k）
初始化 fib[0]=fib[1]=1（类斐波那契，但这里 f[0]、f[1] 都 = 1，和标准 fib[0]=0,fib[1]=1 不同——是"某种生成串的 0 代、1 代"）。
fib[i] 递推 fib[i-1]+fib[i-2]，对 mod-1（即 1e9+6）取模——这是为指数降幂。
pw[i] = ksm(2, fib[i])，即 2^fib[i]。这是"第 i 代串的长度/方案数的某种量"。
边界：
f[0][i][i] = (s[i]=='0')：第 0 代是一个单字符，当该字符等于 '0' 时，在区间 [i,i] 记 1（真），否则 0。
f[1][i][i] = (s[i]=='1')：第 1 代单字符 '1'，等于 '1' 时记 1。
这强烈说明：第 0 代串 = "0"（单字符），第 1 代串 = "1"（单字符）‍，后面的代数按某种规则拼接
核心转移（第 2..m 代）‍：对每个区间 [j,k]：

f[i-1][j][k] * (k==n ? pw[i-2] : 1)

表示：当"第 i 代串的末尾部分是第 i−2 代串，前面是第 i−1 代串"时，若区间 [j,k] 的匹配落在第 i−1 代部分（前缀），则乘上 pw[i-2]——因为第 i−2 代作为后缀部分"自由填充"有 pw[i-2] 种选择（后文不约束 j..k 之外的匹配）。仅当 k==n（区间到达串尾）时才需要乘，否则乘 1。
即：第 i 代串 = (第 i-1 代串) 拼接 (第 i-2 代串)。
f[i-2][j][k] * (j==1 ? pw[i-1] : 1)

对称：当区间 [j,k] 落在第 i−2 代部分（后缀）时，前缀是第 i−1 代自由填充，需乘 pw[i-1] 种；仅当 j==1（区间到串首）才乘。
f[i-1][j][l] * f[i-2][l+1][k]

当区间 [j,k] 跨越两个子代边界：左段 [j,l] 在第 i−1 代部分，右段 [l+1,k] 在第 i−2 代部分，枚举分界 l，两边匹配方案数相乘。
输出 f[m][1][n]：整串 s（区间 [1,n]）在第 m 代串中匹配的方案数（模 1e9+7）
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define ll long long
using namespace std;

constexpr int N = 110, mod = 1e9+7;

ll ksm(ll x, ll p) {
    ll ret = 1;
    for (; p; p>>=1, x=x*x%mod)
        if (p&1) ret=ret*x%mod;
    return ret;
}

int n, m;
char s[N];
ll fib[N], pw[N], f[N][N][N];
int main() {
    scanf("%d%d", &n, &m); scanf("%s", s+1);
    fib[0] = fib[1] = 1; pw[0] = pw[1] = 2;
    rep(i,2,m) fib[i] = (fib[i-1]+fib[i-2])%(mod-1), pw[i] = ksm(2, fib[i]);
    rep(i,1,n) f[0][i][i] = s[i]=='0', f[1][i][i] = s[i]=='1';
    rep(i,2,m) rep(j,1,n) rep(k,j,n) {
        f[i][j][k] = (f[i][j][k]+f[i-1][j][k]*(k==n?pw[i-2]:1)%mod)%mod;
        f[i][j][k] = (f[i][j][k]+f[i-2][j][k]*(j==1?pw[i-1]:1)%mod)%mod;
        rep(l,j,k-1) f[i][j][k] = (f[i][j][k]+f[i-1][j][l]*f[i-2][l+1][k]%mod)%mod;
    }
    printf("%lld\n", f[m][1][n]);
    return 0;
}