//
// Created by Psy.C on 2026/4/20.
//
/**
n, m: 网格大小
x, y: 概率参数
k: 总步数
q: 转移概率
a[N]: 二项分布概率数组
s[N]: a的前缀和
f, g, h: 三个DP数组（当前和下一轮）
f1~f2, g1~g2, h1~h2: DP数组的两轮状态
q = x/y mod p（使用费马小定理求逆元）
表示向右移动的概率
a[i]: 在k步中向右移动i步的概率（二项分布）
C: 组合数 C(k,i)
s[i]: a的前缀和

第一个循环（正向）：
F[j]: 计算新的f值
sum: 累积和，用于计算前缀
H[j]: 计算新的h值
第二个循环（反向）：
G[j]: 计算新的g值
sum: 累积和，用于计算后缀
状态交换：
交换数组指针，进入下一轮

计算最终的概率和
f[j]*a[j-1]*s[m-j]: 某种状态的概率贡献
g[j]*a[m-j]*s[j-1]: 另一种状态的概率贡献
h[j]*s[j-1]*s[m-j]: 第三种状态的概率贡献
O(n×m): DP的总复杂度


二项分布公式：
a[i] = C(k, i) * q^i * (1-q)^(k-i)
这是二项分布的概率质量函数
详细解释：
C: 组合数 C(k, i)
ksm(q, i): q^i （向右移动i次的概率）
ksm(mod+1-q, k-i): (1-q)^(k-i) （向左移动k-i次的概率）
mod+1-q 等价于 -q mod p，即 p-q
1ll*: 确保64位整数乘法
边界条件：
if (i <= k): 只有当向右移动的步数不超过总步数时才有意义
else a[i] = 0: 超出范围的概率为0

i ? s[i-1] : 0: 如果i>0，取s[i-1]，否则取0
s[i]: a数组的前缀和，即 s[i] = Σ(a[j]) for j from 0 to i
这样可以快速计算区间概率
组合数递推公式：
C(k, i+1) = C(k, i) * (k-i) / (i+1)
即：C_new = C_old * (k-i) / (i+1)
详细解释：
C: 当前组合数 C(k, i)
*(k-i): 乘以分子 (k-i)
*ksm(i+1, mod-2): 乘以 (i+1) 的模逆元
/ (i+1) 在模意义下变成乘以逆元
费马小定理：
当p是质数时，a^(p-1) ≡ 1 (mod p)
所以 a^(-1) ≡ a^(p-2) (mod p)
因此 1/(i+1) ≡ (i+1)^(mod-2) (mod p)


从第2行到第n行进行DP转移
每次处理一行的状态转移
sum: 累积和，代表前j-1列的某种贡献
s[m-j]: 表示剩余位置的累积概率
F[j]: 新的f状态值
sum: 累加前一项的贡献
f[j]*a[j-1]: f状态在位置j-1的贡献
h[j]*s[j-1]: h状态在前j-1位置的累积贡献
第一项 f[j]*a[j-1]*s[m-j]:
f状态在位置j-1的贡献，乘以右侧累积概率
第二项 g[j]*a[m-j]*s[j-1]:
g状态在位置m-j的贡献，乘以左侧累积概率
第三项 h[j]*s[j-1]*s[m-j]:
h状态在两侧的累积贡献

sum: 从右侧累积的和
s[j-1]: 左侧累积概率
g[j]*a[m-j]: g状态在右侧位置的贡献
h[j]*s[m-j]: h状态在右侧累积的贡献
交换指针，使F,G,H成为当前状态，f,g,h成为临时数组
准备下一轮DP转移
f[i]: 到达位置i的某种概率状态
g[i]: 另一种方向的概率状态
h[i]: 交叉或累积的概率状态

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1507, mod = 1e9+7;

int ksm(int a, int b) {
    int res = 1;
    while (b) {
        if (b&1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        b >>= 1;
    }
    return res;
}

int n, m, x, y, k, q, a[N], s[N], sum, ans;
int *f, *F, *g, *G, *h, *H;
int f1[N], f2[N], g1[N], g2[N], h1[N], h2[N];
int main() {
    fast;
    cin >> n >> m >> x >> y >> k;
    q = 1ll*x*ksm(y, mod-2)%mod;
    for (int i = 0, C = 1; i <= m; ++i) {
        if (i <= k) a[i] = 1ll*C*ksm(q, i)%mod*ksm(mod+1-q, k-i)%mod;
        else a[i] = 0;
        s[i] = ((i ? s[i-1] : 0) + a[i]) % mod;
        C = 1ll*C*(k-i)%mod*ksm(i+1, mod-2)%mod;
    }
    f = f1, F = f2, g = g1, G = g2, h = h1, H = h2;
    for (int i = 1; i <= m; ++i) f[i] = 1;
    for (int i = 2; i <= n; ++i) {
        sum = 0;
        for (int j = 1; j <= m; ++j) {
            F[j] = 1ll*sum*s[m-j]%mod;
            sum = (sum+1ll*f[j]*a[j-1]+1ll*h[j]*s[j-1])%mod;
            H[j] = (1ll*f[j]*a[j-1]%mod*s[m-j]+1ll*g[j]*a[m-j]%mod*s[j-1]+
                1ll*h[j]*s[j-1]%mod*s[m-j])%mod;
        }
        sum = 0;
        for (int j = m; j >= 1; --j) {
            G[j] = 1ll*sum*s[j-1]%mod;
            sum = (sum + 1ll*g[j]*a[m-j]+1ll*h[j]*s[m-j])%mod;
        }
        swap(f, F), swap(g, G), swap(h, H);
    }
    for (int j = 1; j <= m; ++j)
        ans = (ans + 1ll*f[j]*a[j-1]%mod*s[m-j]+1ll*g[j]*a[m-j]%mod*s[j-1]+
            1ll*h[j]*s[j-1]%mod*s[m-j])%mod;
    cout << ans << '\n';
    return 0;
}