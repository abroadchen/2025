//
// Created by Psy.C on 2026/10/16.
//
/**
模意义快速幂，用于求逆元和 2^(n-j)
fac[i]：i 的阶乘模 mod。
s[i][j]：第二类斯特林数，表示把 i 个不同元素划分成 j 个非空集合的方案数。
递推：s[i][j] = s[i-1][j-1] + j*s[i-1][j]（新元素要么自成一个集合，要么放进已有的 j 个集合之一）
计算 C(n, r)（参数写作 C(r, n)，含义是 n 个里选 r 个）。
分子是 n·(n-1)·…·(n-r+1)，分母用 fac[r] 的逆元
逐项含义：

s[k][j]：把 k 个"指数"划分成 j 组（第二类斯特林），用于展开 x^k = Σ_j s(k,j)·x^j_（下降阶乘展开）。
C(j, n)：从 n 个中选 j 个。
fac[j]：j 的阶乘。
2^(n-j)：剩下 n-j 个元素每个可取可不取。
这个求和正是组合数学恒等式 Σ_j S(k,j)·C(n,j)·j!·2^(n-j)，其结果为 Σ_{i=0}^{n} C(n,i)·i^k 这类和式的封闭形式（等价于统计 n 个元素、每个元素"出现/不出现"并统计 k 次幂的贡献）。

更经典地，这个结构对应公式：恰好 k 次、从 n 个元素中选任意个组合的某种幂和，即 Σ_{i=0}^n C(n,i)·(i选法)^k 类问题，最终答案形式为带斯特林数展开
预处理斯特林数 + 阶乘：O(N²)（N = k，这里上限 N-5 = 5000），可行。
答案求和：O(k)。
总 O(k²)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
#define int long long
using namespace std;

constexpr int N = 5e3+5, mod = 1e9+7;

int ksm(int a, int b) {
    int ans = 1;
    while (b) {
        if (b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}

int fac[N], s[N][N];
void init() {
    fac[0] = 1;
    rep(i,1,N-5) fac[i] = fac[i-1]*i%mod;
    s[1][1] = 1;
    rep(i,2,N-5) rep(j,1,i) s[i][j] = (s[i-1][j-1]+s[i-1][j]*j)%mod;
}

int C(int r, int n) {
    int ans = 1;
    per(i,n,n-r+1) ans=ans*i%mod;
    return ans*ksm(fac[r], mod-2)%mod;
}


signed main() {
    fast;
    int n, k; cin>>n>>k; init();
    int ans = 0;
    for (int j = 0; j <= k && n - j >= 0; ++j)
        ans = (ans+fac[j]*C(j,n)%mod*s[k][j]%mod*ksm(2ll,n-j)%mod)%mod;
    cout << ans;
    return 0;
}