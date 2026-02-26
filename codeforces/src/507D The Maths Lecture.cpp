//
// Created by Psy.C on 2026/2/26.
//
/**
N = 1001：数位DP数组的第一维大小
M = 101：模数上限
任何数的0次方是1，1次方是自身
先计算 n^(p/2)
平方得到 n^p
如果p是奇数，再乘以n

n：数字位数
m：结果模数
dp[N][M][2]：记忆化数组
k：整除条件的除数
剪枝优化：如果已经放置了非零数字且余数为0：
剩余x位可以任意填充
有 9×10^(x-1) 种方案（首位9种，其余10种）
边界条件：处理完所有数位
记忆化剪枝：如果状态已计算过，直接返回
确定当前位的起始数字：
最低位可以从1开始（避免前导零）
其他位可以从0开始
枚举当前位的数字：
计算放置数字i对余数的贡献
递归处理下一位
累加方案数
返回当前状态的方案数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1001, M = 101;

ll ksm(const ll n, const ll p, const ll mod) {
    if (p == 0) return 1;
    if (p == 1) return n;
    ll x = ksm(n, p / 2, mod);
    x = x * x % mod;
    if (p&1) x = x*n%mod;
    return x;
}

int n, m, dp[N][M][2], k;

/**
 *
 * @param idx 当前处理的数位位置
 * @param r 当前余数
 * @param flag 是否已经开始放置非零数字
 * @return
 */
int dfs(const int idx, const int r, const bool flag) {
    if (flag && r == 0) {
        const int x = n - idx;
        if (x == 0) return 1;
        return 9*ksm(10, x-1, m)%m;
    }
    if (idx == n) return 0;
    int& mem = dp[idx][r][flag];
    if (mem != -1) return mem; mem = 0;
    const int st = idx + 1 == n ? 1 : 0;
    for (int i = st; i <= 9; ++i) {
        int x = i*ksm(10, idx, k)%k;
        x = (x + r) % k;
        mem = (0ll + mem + dfs(idx+1, x, flag||i>0))%m;//如果之前已经放过非零数字，或者当前放的是非零数字
    }
    return mem;
}

int main() {
    fast;
    cin >> n >> k >> m;
    memset(dp, -1, sizeof dp);
    cout << dfs(0, 0, false) << '\n';
    return 0;
}