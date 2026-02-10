//
// Created by Psy.C on 2026/2/10.
//
/**
f[MAXN+5]：预计算的主要函数值数组
sf2[MAXN+5]：f[i]*i²的前缀和
sf1[MAXN+5]：f[i]*i的前缀和
sf0[MAXN+5]：f[i]的前缀和
计算1²+2²+...+x² = x(x+1)(2x+1)/6，模MOD

欧拉函数筛：
phi[1]=1：φ(1)=1
!vis[i]：如果i未被标记，则i是素数
pr[++prcnt]=i,phi[i]=i-1：添加素数i，φ(i)=i-1
线性筛：对于i和素数pr[j]，标记i*pr[j]为合数
i%pr[j]==0：如果i能被pr[j]整除，φ(i*pr[j])=φ(i)*pr[j]
否则：φ(i*pr[j])=φ(i)*φ(pr[j])

f[i] = i²：初始值
f[i] += 2*getsum2(i-1)：加上2*(1²+2²+...+(i-1)²)
f[i] -= 2*i*(i-1)：减去2i(i-1)

对于每个i，更新其所有大于i的倍数j
f[j] += 2*i*φ(j/i)：加入欧拉函数相关的贡献
这是一种数论变换，类似狄利克雷卷积

sf2[i]：∑(f[j]*j²) for j=1 to i
sf1[i]：∑(f[j]*j) for j=1 to i
sf0[i]：∑f[j] for j=1 to i

[(n+1)*(m+1)*sf0[min(n,m)] +
         (MOD-sf1[min(n,m)])*(n+1+m+1) +
         sf2[min(n,m)]] % MOD

预处理：O(n log n) - 线性筛 + 数论变换
单次查询：O(1) - 使用预计算的前缀和
空间复杂度：O(n) - 多个数组存储
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000005
#define mod 1000000007
using namespace std;

int get(const int x) {
    return 1ll*x*(x+1)*(2*x+1)/6%mod;
}

int phi[N], vis[N], pr[N], cnt, f[N], s2[N], s1[N], s0[N];
void init(const int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) pr[++cnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= cnt && pr[j]*i <= n; ++j) {
            vis[pr[j]*i] = 1;
            if (i%pr[j] == 0) {
                phi[pr[j]*i] = phi[i] * pr[j];
                break;
            }
            phi[pr[j]*i] = phi[pr[j]] * phi[i];
        }
    }
    for (int i = 1; i <= n; ++i) {
        f[i] = 1ll*i*i%mod;
        f[i] = (f[i] + 2ll*get(i-1))%mod;
        f[i] = (f[i] - 2ll*i*(i-1)%mod + mod)%mod;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + i; j <= n; j += i)
            f[j] = (f[j] + 2ll*i*phi[j/i])%mod;
    for (int i = 1; i <= n; ++i) {
        s2[i] = (s2[i-1] + 1ll*f[i]*i%mod*i)%mod;
        s1[i] = (s1[i-1] + 1ll*f[i]*i)%mod;
        s0[i] = (s0[i-1] + f[i])%mod;
    }
}


int main() {
    fast;
    init(1e6);
    int q; cin >> q;
    while (q--) {
        int n, m, res = 0; cin >> n >> m;
        cout << (1ll*(n+1)*(m+1)%mod*s0[min(n,m)]+
            1ll*(mod-s1[min(n,m)])*(n+1+m+1)+s2[min(n,m)])%mod << '\n';
    }
    return 0;
}