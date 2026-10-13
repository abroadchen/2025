//
// Created by Psy.C on 2026/10/12.
//
/**
ks[i] = 从数 i 经过"反复取 popcount"到达 1 的迭代步数。
递推：i 的下一步变成 pc(i)（一个 ≤ 30 的数），所以 ks[i] = ks[pc(i)] + 1。
边界：ks[0] 默认 0、ks[1] 默认 0（即 1 本身算 0 步到达 1）。
因为 popcount 最大只到数本身的位数（这里数位 ≤ 1000，但 dp 里传给 ks 的是某数的 1 个数，≤ 数位长度），而真正被 ks 索引的是"1 的个数 cnt"，cnt ≤ 数位长度。这里 ks[cnt] 用于判定从当前得到的 cnt 继续迭代到 1 还需要多少步
n：从高位开始还剩多少位没填。
cnt：已经填出的位数中"1"的个数。
f：前导零标志（当前位是否是这个数的最高非零位，即是否填的是首位 1；用于避免把前导 0 计入 cnt、也避免数 0 被算进去）。
lim：是否仍贴着上界 bs（受前缀限制）
若 cnt==1 && f：这个数就是 1 本身（唯一一位 1 且是最低位），step(1)=0，不可能是 k 步 → 返回 0。
否则若 cnt 非 0：这个数有 cnt 个 1，那么它第 1 次 popcount 得到 cnt，之后还需要 ks[cnt] 步从 cnt 迭代到 1。总步数 = 1 + ks[cnt]，要求等于 k，即 ks[cnt] == k-1。返回该布尔值。
若 cnt==0（全是 0，即数 0）：返回 0（不算）。
状态递推：up = lim ? bs[n] : 1 是当前位置可填的最高值；枚举填 0/1；若填 1 则 cnt 加一。f 记录这一位是否填 1（用于上面 cnt==1&&f 的判定）。lim 沿用标准数位 DP 的上界传递。

dp[n][cnt][f] 记忆化 !lim 的分支（自由填写的部分），消除重复计算
k==0 特判：只有数 1 的 popcount 迭代步数为 0，直接输出 1（排除了 0）。
把二进制字符串 s（长度即数位个数）逆序放进 bs，使 bs[最高位] 在前，供 dfs 从高位往低位填。
从最高位 dfs(s.size()) 开始统计，得到 step(x)==k 的 x ∈ [1, X] 的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pc __builtin_popcount
using namespace std;

constexpr int N = 1e3+5, mod = 1e9+7;

int dp[N][N][2], ks[N], k;
bitset<N> bs;
int dfs(int n, int cnt=0, bool f=0, bool lim=1) {
    if (!lim && ~dp[n][cnt][f]) return dp[n][cnt][f];
    if (!n) return cnt==1&&f ? 0 : cnt&&ks[cnt]==k-1;
    int ret = 0, up = lim ? bs[n] : 1;
    for (int i = 0; i <= up; ++i)
        ret = (ret + dfs(n-1, cnt+i, i, lim&&i==up))%mod;
    if (!lim) dp[n][cnt][f] = ret;
    return ret;
}

void init() {
    for (int i = 2; i <= N-5; ++i)
        ks[i] = ks[pc(i)] + 1;
}

string s;
int main() {
    fast;
    init(); memset(dp, -1, sizeof(dp));
    cin >> s >> k;
    if (k == 0) return cout << 1, 0;
    for (int i = 0; i < s.size(); ++i)
        bs[s.size()-i] = s[i]^48;
    cout << dfs(s.size());
    return 0;
}