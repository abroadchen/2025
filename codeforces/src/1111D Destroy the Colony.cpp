//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
get(c) 把字符映射到 0-51（小写→0..25，大写→26..51）。
cnt[i] = 第 i 种字符出现次数
fac[n/2]*fac[n/2]：把 n 个位置分成两组（每边 n/2）的排列基数。
每遇到一种字符 i，num *= inv[cnt[i]]：除以重复计数，得到"每种字符两两配对"的总排列数（多重集）。
dp 是生成函数背包：dp[j] = 恰好选出总长度 j（由各种字符任意选）的方案数。这里做的是"把所有字符可用的生成函数乘起来"
"可撤销背包"（rollback knapsack）‍：
要回答询问：指定两个位置 i、j，它们的字符必须配对在一起（或不能配在一起），计算方案数。
做法：临时把字符 i（和 j）从生成函数里去掉，用"去掉后剩余字符能凑出 n/2 长的方案数"来算。
res[i][j] = 2 * dp[n/2]：当 i、j 不放回（被撤销），剩余部分凑成 n/2 的方案数乘 2 —— 因为 i 和 j 可以两种顺序配对。
通过先减后加（k 逆序遍历实现原背包的逆操作）实现撤销再恢复，从而在不重做整个背包的前提下，独立求得任意指定对字符的特殊方案数。
对每个询问 (x, y)：取这两个位置的字符类型，查预存好的 res[charX][charY]，再乘以基数 num，得到最终答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<k; ++i)
#define per(i,j,k) for (int i=j; i>=k; --i)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, M = 55, mod = 1e9+7;

ll ksm(ll a, ll n, int m=mod) {
    ll res = 1;
    while (n) {
        if (n&1) res=res*a%mod;
        a=a*a%mod;
        n>>=1;
    }
    return res;
}
int get(int x) {
    if ('a' <= x && x <= 'z') return x - 'a';
    return x - 'A' + 26;
}

ll fac[N], inv[N];
void init() {
    fac[1] = 1;
    rep(i,2,N) fac[i] = fac[i-1]*i%mod;
    inv[N-1] = ksm(fac[N-1],mod-2,mod);
    for (int i = N-2; ~i; --i) inv[i] = inv[i+1]*(i+1)%mod;
}

char s[N];
int q, n, cnt[M], x, y;
ll num, dp[N], res[M][M];
int main() {
    fast;
    init(); cin >> s >> q; n = strlen(s);
    rep(i,0,n) cnt[get(s[i])]++;
    num = fac[n/2]*fac[n/2]%mod; dp[0] = 1;
    rep(i,0,52) if (cnt[i]) {
        num = num*inv[cnt[i]]%mod;
        per(j,n,cnt[i]) dp[j] = (dp[j] + dp[j-cnt[i]])%mod;
    }
    rep(i,0,52) {
        res[i][i] = dp[n/2];//同名配对：直接用全背包方案
        if (cnt[i]) {
            rep(j,cnt[i],n+1) dp[j] = (dp[j] - dp[j-cnt[i]]+mod)%mod;//撤销 i 的影响
            rep(j,i+1,52) if (cnt[j]) {
                rep(k,cnt[j],n+1) dp[k] = (dp[k] - dp[k-cnt[j]]+mod)%mod;//再撤销 j
                res[i][j] = res[j][i] = 2ll*dp[n/2]%mod;//i 与 j 必须不同的方案
                per(k,n,cnt[j]) dp[k] = (dp[k] + dp[k-cnt[j]]+mod)%mod;//加回 j
            }
            per(j,n,cnt[i]) dp[j] = (dp[j] + dp[j-cnt[i]]+mod)%mod;//加回 i
        }
    }
    while (q--) {
        cin >> x >> y;
        cout << num*res[get(s[x-1])][get(s[y-1])]%mod << '\n';
    }
    return 0;
}