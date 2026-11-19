//
// Created by Psy.C on 2026/11/19.
//

/**
真正学会的起点..
概率型 DP：d[i][j] 表示经过 i 轮后，当前状态处在 j 的概率（模意义下，用 inv[j+1] 表示 1/(j+1)）
d[i+1][k] += d[i][j] * (1/(j+1)),  对 k=0..j
即从状态 j 出发，以等概率 1/(j+1) 转移到 k ∈ {0,1,…,j}（均匀随机地掉到 0..j 的任意一个）。

d[0][y]=1：从 y 出发。经过 m 轮后分布到 d[m][0..y]
加权求和：

sum = ∑ d[m][i] · x^i
d[m] 当作 x 的多项式系数，在 x 处求值——即 d[m] 的概率母函数在 x 点取值（其中 cur 逐步乘以 x 得到 x^i）
标准的试除质因数分解：对每个质因子 i，统计其指数 cnt，累乘 solve(i, cnt)。
最后若 n>1，说明剩下一个大于√n 的质因子，指数为 1，做 solve(n,1)
线性求 1..2000 的模逆，用于 inv[j+1]（即 1/(j+1) mod p）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define int long long
using namespace std;

constexpr int N = 1e4+10, M = 65, mod = 1e9+7, inf = 2e3;

int d[N][M], m, inv[N];
int solve(int x, int y) {
    int sum = 0, cur = 1; memset(d, 0, sizeof d); d[0][y] = 1;
    rep(i,m) rep(j,y+1) if (d[i][j]) rep(k,j+1)
        d[i+1][k] = (d[i+1][k]+d[i][j]*inv[j+1])%mod;
    rep(i,y+1) {
        sum = (sum + cur*d[m][i]) % mod;
        cur = cur*x%mod;
    }
    return sum;
}

int n, ans = 1;
signed main() {
    fast;
    inv[1] = 1;
    for (int i = 2; i <= inf; i++) inv[i] = inv[mod%i]*(mod-mod/i)%mod;
    cin >> n >> m;
    for (int i = 2; i*i <= n; i++) {
        if (n%i) continue;
        int cnt = 0;
        while (n%i == 0) n/=i, cnt++;
        ans = ans*solve(i,cnt)%mod;
    }
    if (n > 1) ans = ans*solve(n,1)%mod;
    cout << ans << '\n';
    return 0;
}