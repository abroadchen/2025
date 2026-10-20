//
// Created by Psy.C on 2026/10/20.
//
/**
sum[i] 表示前 i 个元素的和对 p 取模。这样任意区间 [l+1, j] 的和模 p 可以通过 (sum[j] - sum[l] + p) % p 快速得到
dp[i][j] = 将前 j 个元素恰好分成 i 段时的最大"段和模 p 之和"
dp[0][0] = 0：0 个元素分成 0 段，值为 0
其余初始化为 -inf（负无穷大），表示不可行状态
最终答案是 dp[k][n]：将全部 n 个元素分成恰好 k 段的最大值
前 l 个元素分成 i-1 段，最后一段是 [l+1, j]，其和模 p 为 (sum[j]-sum[l]+p)%p。
复杂度为 O(k·n²)，在 n 较大时会超时
pos[mod] = 在所有已处理的切分点中，dp[i-1][l] 的最大值，且满足 sum[l] == mod
也就是说，pos[x] 记录的是："上一个切分点 l 的前缀和模 p 等于 x" 时，对应的 dp[i-1][l] 的最大值。

对于固定的 j，转移方程拆开看：

dp[i][j] = max over l of  ( dp[i-1][l] + (sum[j] - sum[l] + p)%p )
对于一个给定的后缀和模值 (sum[j]-l+p)%p，我们希望 dp[i-1][l] 最大。因此对每个可能的 sum[l] 模值，维护最大的 dp[i-1][l]，记入 pos[sum[l]]
内层循环在计算 dp[i][j] 时，pos 中只包含之前 j' < j 的切分点（因为本轮还没有把当前 j 加入 pos）。

为什么？因为要满足切分点 l < j（当前段至少包含一个元素），所以计算 dp[i][j] 时不能用 l = j 自身作切分。
所以顺序是：先用 pos 算出 dp[i][j]，再把 j 作为候选切分点更新 pos
当分成第 1 段时，切分点 l = 0（即前缀和为 0 的那个位置，也就是数组开头之前），dp[0][0] = 0 作为起点。因为只能从 l=0 开始分第一段，所以只把 pos[0] 初始化为 0，其余 pos 为 -inf

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e4+10, inf = 1e15;

int n, k, p, a[N], sum[N], dp[52][N], pos[110];
signed main() {
    fast;
    cin >> n >> k >> p;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = (sum[i-1] + a[i]) % p;
    }
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= n; ++j) dp[i][j] = -inf;
    dp[0][0] = 0;
    for (int i = 1; i <= k; ++i) {
        for (int j = 0; j < p; ++j) pos[j] = -inf;
        if (i == 1) pos[0] = 0;
        for (int j = 1; j <= n; ++j) {
            for (int l = 0; l < p; ++l)
                dp[i][j] = max(dp[i][j], pos[l]+((sum[j]-l)%p+p)%p);
            pos[sum[j]] = max(pos[sum[j]], dp[i-1][j]);
        }
    }
    cout << dp[k][n];
    return 0;
}