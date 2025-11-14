//
// Created by Psy.C on 2025/11/14.
//
/*
*mod = 1e9+7：模数，常用的大质数
N = 1e6+5：阶乘数组大小
M = 1005：动态规划数组大小
*fac[N]：阶乘数组
ifac[N]：阶乘的逆元数组
f[M][M]：动态规划数组
 *
*计算x的y次方模mod的结果
使用快速幂算法优化计算效率
时间复杂度O(log y)
 *
*计算组合数C(n,m) = n!/(m!(n-m)!)
使用预处理的阶乘和阶乘逆元数组加速计算
如果参数非法则返回0
 *
 *如果m=1，直接输出k^n并结束程序
*计算mx为n, m, k中的最大值
预处理阶乘数组：fac[i] = i!
计算最大阶乘的逆元
通过递推计算所有阶乘的逆元：ifac[i-1] = ifac[i] * i
*初始化动态规划数组f[0][0] = 1
填充动态规划表：
//f[i][j]表示将i个不同的球放入j个相同的盒子且无空盒的方案数
i个不同的元素 划分成 j个非空且不可区分的子集 的方案数


第一部分：j * f[i-1][j]
当我们已经将前 i-1 个元素划分成 j 个非空子集时，考虑如何安排第 i 个元素：

第 i 个元素可以放入已有的 j 个子集中的任意一个
因此有 j 种选择
所以这部分贡献是 j * f[i-1][j]

第二部分：f[i-1][j-1]
当我们已经将前 i-1 个元素划分成 j-1 个非空子集时：
第 i 个元素必须单独构成一个新的子集
这样总共就有 j 个子集了
所以这部分贡献是 f[i-1][j-1]




f[i][j] = j * f[i-1][j] + f[i-1][j-1]
这实际上是第二类斯特林数的递推关系
 *
*初始化答案ans = 0
外层循环遍历i从0到min(k,n)
计算中间值t = C(k,i) * i^(n*(m-2))
内层循环遍历j从i到min(k,n)
累加到最终答案：
t * C(k-i, j-i) * C(k-j, j-i) * (f[n][j] * j!)^2
 *
 *
*i^(n*(m-2)) - 幂次项
表示i的(n*(m-2))次方
这通常表示对i个对象进行(n*(m-2))次独立选择或分配
 *
* (f[n][j] * j!)^2
f[n][j]：将n个不同元素划分成j个不可区分子集的方案数（第二类斯特林数）
j!：将j个不可区分的子集进行排列的方式数
f[n][j] * j!：将n个不同元素划分成j个可区分子集的方案数
平方：表示这种划分出现了两次（可能是行和列的双重划分）
 *
 *
 */
#include <algorithm>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;

typedef long long ll;
const int mod = 1e9+7, N = 1e6+5, M = 1005;
int n, m, k, mx;
ll fac[N], ifac[N], f[M][M];

ll power(ll x, ll y) {
    ll res = 1;
    for (; y; y >>= 1, x = x * x % mod) if (y & 1) {
        res = res * x % mod;
    }
    return res;
}

ll C(ll n, ll m) {
    if (m < 0 || m > n) return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
ll sqr(ll x) { return x * x % mod; }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    if (m == 1) { cout << power(k, n) << '\n'; return 0; }
    mx = max({n, m, k});
    fac[0] = 1;
    rep(i,mx) fac[i] = fac[i-1] * i % mod;
    ifac[mx] = power(fac[mx], mod - 2);
    for (int i = mx; i >= 1; --i) ifac[i - 1] = ifac[i] * i % mod;
    f[0][0] = 1;
    rep(i,n) rep(j,n) {
        f[i][j] = (j * f[i - 1][j] + f[i - 1][j - 1]) % mod;
    }
    ll ans = 0;
    for (int i = 0; i <= min(k, n); ++i) {
        ll t = C(k, i) * power(i, n * (m - 2)) % mod;
        for (int j = i; j <= min(k, n); ++j)
            ans = (ans + t * C(k - i, j - i) % mod *
                C(k - j, j - i) % mod *
                sqr(f[n][j] * fac[j] % mod)) % mod;
    }
    cout << ans << '\n';
    return 0;
}