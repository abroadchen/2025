//
// Created by Psy.C on 2026/4/7.
//
///时间复杂度：O(n√max(a_i) + π(max(a_i))×20)，其中π是素数计数函数
/**
S = 2^(n-1)，这个值在组合数学中经常表示"一半子集"的大小
mul(S, cnt[i][j]) 表示平凡情况下的贡献
从总和中减去这部分平凡贡献

x 是经过修正的净贡献（去除了平凡贡献）
j 是指数权重（当前处理的是j次幂）
mul(x, j) 是加权贡献
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5, M = 2.6e4, mod = 1e9+7;
///vis标记合数，pri素数数组，pid素数编号，tot素数个数
bool vis[N];
int pri[M], pid[N], tot;
void pre() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i])//i是素数
            pri[tot] = i, pid[i] = tot++;//记录素数及其编号
        for (int j = 0; j < tot; ++j) {//枚举已知素数
            if (i*pri[j] >= N) break;
            vis[i*pri[j]] = true;//标记合数
            if (i%pri[j] == 0) break;//避免重复标记
        }
    }
}
///第i个素数的j次幂出现了多少次
int cnt[M][20];
void de(int x) {//分解x的质因数
    for (int i = 0; x > 1; ++i) {
        int p = pri[i];
        if (p*p > x) break;
        if (x%p != 0) continue;
        int e = 0;
        while (x%p == 0) { x /= p; e++; }//p的指数
        cnt[i][e]++;//该指数出现次数
    }
    if (x > 1) cnt[pid[x]][1]++;//x本身是大质数
}

ll mul(ll a, ll b) { return a*b%mod; }
ll ksm(ll a, int p) {
    ll ans = 1;
    while (p) {
        if (p&1) ans = mul(ans, a);
        a = mul(a, a);
        p >>= 1;
    }
    return ans;
}
void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}
void sub(ll& a, ll b) {
    a -= b;
    if (a < 0) a += mod;
}

int n, a[N];
ll fac[N], inv[N], Cn[N];
int main() {
    fast;
    pre(); cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    //预处理阶乘
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = mul(fac[i-1], i);
    //预处理逆元
    inv[n] = ksm(fac[n], mod - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = mul(inv[i+1], i+1);
    //预处理组合数并求前缀和
    for (int i = 0; i <= n; ++i)
        Cn[i] = mul(mul(fac[n], inv[i]), inv[n-i]);
    for (int i = 1; i <= n; ++i)
        add(Cn[i], Cn[i-1]);//一维前缀和
    for (int i = 1; i <= n; ++i)
        add(Cn[i], Cn[i-1]);//二维前缀和
    for (int i = 1; i <= n; ++i) de(a[i]);//对每个数进行质因数分解
    ll ans = 0, S = ksm(2, n-1);
    for (int i = 0; i < tot; ++i) {
        int t = n;//剩余数量
        for (int j = 1; j < 20; ++j) t -= cnt[i][j];//减去各种指数的个数
        for (int j = 1; j < 20; ++j) if (cnt[i][j]) {//如果该指数存在
            int l = t, r = l + cnt[i][j] - 1;
            t += cnt[i][j];//更新剩余数量
            ll x = Cn[r];
            if (l) sub(x, Cn[l-1]);
            sub(x, mul(S, cnt[i][j]));//减去平凡情况
            add(ans, mul(x, j));//乘以指数权重
        }
    }
    cout << ans << '\n';
    return 0;
}