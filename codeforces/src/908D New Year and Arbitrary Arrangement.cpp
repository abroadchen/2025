//
// Created by Psy.C on 2026/10/11.
//
/**

f[i][j]：到达状态 (i, j) 的概率（模意义下）。
这里的 i、j 含义需要结合题目：通常 i 是"白/好事"计数，j 是"坏"计数，或者 s 的长度之类。f[1][0]=1 表示初始状态概率为 1

当 i+j >= k 时，过程终止，不再继续转移。
此时该状态对答案的贡献是 f[i][j] × (当前值)，其中当前值 = i+j + a * b^{-1}（即 i+j + a/b）。
a*ksm(b, mod-2) 就是 a * b^{-1} = a/b，通常这表示"终止后剩余的期望增量"（比如题目里终止后还要固定加 a/b 之类的期望值）
以概率 a*inv 转移到状态 (i+1, j)（增加一个 a 类）。
以概率 b*inv 转移到状态 (i, j+i)（增加 i 个 b 类，或把值 j 变成 j+i）。j+i 依赖当前的 i，这往往是题目的关键规则（b 类操作会按照 i 的量叠加）
输出所有终止状态对应的期望之和，即最终答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e3+5, mod = 1e9+7;

ll ksm(ll b, ll m) {
    ll ret = 1;
    while(m) {
        if (m&1) ret=ret*b%mod;
        b=b*b%mod;
        m>>=1;
    }
    return ret;
}

int k;
ll a, b, inv, f[N][N], ans;
int main() {
    fast;
    cin >> k >> a >> b; inv = ksm(a+b, mod-2); f[1][0] = 1;
    rep(i,1,k) rep(j,0,k) {
        if (i+j >= k)  ans=(ans+f[i][j]*(i+j+a*ksm(b,mod-2)%mod)%mod)%mod;
        else {
            f[i+1][j] = (f[i+1][j] + f[i][j]*a%mod*inv%mod)%mod;
            f[i][j+i] = (f[i][j+i] + f[i][j]*b%mod*inv%mod)%mod;
        }
    }
    cout << ans;
    return 0;
}