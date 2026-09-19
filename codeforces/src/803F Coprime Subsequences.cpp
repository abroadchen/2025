//
// Created by Psy.C on 2026/9/19.
//
/**
标准二进制快速幂，模 1e9+7，算 a^x mod mod。
用于后面算 2^num[i]（子集数量）
g[i]：存储 i 的全部质因子（加上 1）。
mu[i]：莫比乌斯函数：
mu[1]=1
为素数时 mu[i]=-1
线性筛中：
i*p[j] 新数时 mu = -mu[i]
若 i 含因子 p[j]（平方因子）→ mu=0
同时 g[j] 对每个素数 i 用倍数循环填充质因子表
输入 n 个数 x，对每个 x 枚举它的全部质因子 j（含 1），num[j]++。
最终 num[d] = "这 n 个数中，有多少个能被质数集合 d 整除"（对每个质因子分别统计，但这里拆成单个质因子计入 num）。
实际上这里把每个质因子单独计数。num[j] 统计的是出现次数，用于后面计算"以 j 为公共因子的子集数"
对每个数 i：
2^num[i] - 1 = 从出现 i 因子的那些数中选择非空子集的方案数。
乘上 mu[i]。
累加取模（+mod 防负）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+10, mod = 1e9+7;

int ksm(int a, int x) {
    int res = 1;
    while (x) {
        if (x&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        x >>= 1;
    }
    return res;
}

int mu[N], vis[N], p[N], cnt;
vector<int> g[N];
void prime() {
    mu[1] = 1;
    for (int i = 1; i <= N-1; ++i) g[i].push_back(1);
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) p[++cnt] = i, mu[i] = -1;
        for (int j = i; j < N; j += i) g[j].push_back(i);
        for (int j = 1; j <= cnt && p[j]*i < N; ++j) {
            mu[i*p[j]] = -mu[i];
            vis[i*p[j]] = 1;
            if (i%p[j] == 0) { mu[i*p[j]] = 0; break; }
        }
    }
}

int num[N], ans;
int main() {
    fast;
    prime();
    int n; cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        for (int j : g[x]) num[j]++;
    }
    for (int i = 1; i <= N-10; ++i)
        ans = ((ans+mu[i]*(ksm(2, num[i])-1))%mod+mod)%mod;
    cout << ans << '\n';
    return 0;
}