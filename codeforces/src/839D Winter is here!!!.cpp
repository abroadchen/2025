//
// Created by Psy.C on 2026/9/26.
//
/**
N = 2e5：数组数量上限。
M = 1e6：数值上限（a[i] ≤ 1e6）。
mod = 1e9+7：模数。
add：模加（避免负数，溢出后减 mod）。
sub：模减（负数补 mod）。
mul：模乘（用 1ll 转 long long 防溢出）
二进制快速幂，计算 x^y % mod
线性筛法同时求莫比乌斯函数 mu[]：
mu[1] = 1。
素数 i：mu[i] = -1（即 sub(0,1)）。
用已有素数标记合数：若 i % pri[j] == 0（i 含该素因子的平方），则 mu[i*pri[j]] = 0 并 break；否则 mu[i*pri[j]] = -mu[i]。
这是标准的线性筛 μ，预处理到 M=1e6

读入 n 个数 a[i]。
cnt[x] 记录数 x 出现次数（值域计数）。
m 记录所有数的最大值（值域上限）
这一层把所有倍数累加：cnt[i] 变成"所有值域中 i 的倍数出现的总次数"。
这样 cnt[d] 就表示：有多少个数能被 d 整除。
这是容斥/莫比乌斯反演的关键一步——cnt[d] = 数组中有多少数是 d 的倍数
观察递推：num[i] = 2*num[i-1] + 2^(i-1)。
初值 num[1] = 0 + 2^0 = 1。
解这个递推：num[i] = 2^1 * num[1] ...  让我们算：
num[1] = 1
num[2] = 2*1 + 2^1 = 2 + 2 = 4
num[3] = 2*4 + 2^2 = 8 + 4 = 12
归纳可得 num[i] = i * 2^(i-1)（验证：1=11✓, 4=22✓, 12=3*4✓）。
含义：num[i] = 从 i 个数中选若干个数（非空子集）的所有子集大小之和 = i * 2^(i-1)。

这个值用于计算"从 cnt[d] 个数中枚举选出若干"时的组合贡献

外层循环 i（从 2 到 m）：枚举可能成为"求和值"的基底 d。
内层循环 j：i*j 是 i 的倍数。
利用莫比乌斯反演：

cnt[i*j] = 有多少个数是 i*j 的倍数。
num[cnt[i*j]] = 从这些数中选出非空子集的所有子集大小之和。
用 mu[j] 做容斥系数，把"gcd 是 i 倍数"转化为"gcd 恰好等于 i"的贡献。
cur = Σ_j μ(j) * num[cnt[i*j]]
通过反演，cur 表示"恰好有 gcd = i 的选取方式的贡献归一化量"
即对每个可能的 gcd 值 i，乘以其权值 i，累加
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5, M = 1e6, mod = 1e9+7;
inline int add(const int& x, const int& y) { return (x + y >= mod) ? (x + y - mod) : (x + y); }
inline int sub(const int& x, const int& y) { return (x - y < 0) ? (x - y + mod) : (x - y); }
inline int mul(const int& x, const int& y) { return 1ll*x*y%mod; }

int ksm(int x, int y) {
    int ret = 1;
    while (y) {
        if (y&1) ret = mul(ret, x);
        x = mul(x, x);
        y >>= 1;
    }
    return ret;
}

int mu[M+5];
bool vis[M+5];
vector<int> pri;
void init(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) mu[i] = sub(0, 1), pri.push_back(i);
        for (int j = 0; j < pri.size() && i*pri[j] < n; ++j) {
            vis[i*pri[j]] = true;
            if (i%pri[j] == 0) { mu[i*pri[j]] = 0; break; }
            mu[i*pri[j]] = sub(0, mu[i]);
        }
    }
}

int n, m, a[N+5], cnt[M+5], num[N+5];
int main() {
    fast; init(M);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        cnt[a[i]]++, m = max(m, a[i]);
    }
    for (int i = 1; i <= m; ++i)
        for (int j = i+i; j <= m; j += i)
            cnt[i] = add(cnt[i], cnt[j]);
    for (int i = 1; i <= n; ++i)
        num[i] = add(add(num[i-1], num[i-1]), ksm(2, i-1));
    int ans = 0;
    for (int i = 2; i <= m; ++i) {
        int cur = 0;
        for (int j = 1; j <= m/i; ++j)
            cur = add(cur, mul(mu[j], num[cnt[i*j]]));
        ans = add(ans, mul(i, cur));
    }
    cout << ans;
    return 0;
}