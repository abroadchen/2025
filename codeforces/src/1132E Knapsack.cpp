//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
w：总背包容量上限。
cnt[1..8]：每种单位 i 的数量。
M = 840 = lcm(1,2,...,8)，关键优化基准。
f[N][L*N]：DP 数组，行代表处理到的单位 i，列代表模 840 下的余数（[i][j]）
全部置为 -1（不可达），f[1][0]=0 表示：用第 1 种单位时，余数 0 的"已用 840 整数倍数量"为 0
r = M/i：单位 i 需要多少个才能凑到 840。因 840/i 是 i 能贡献"lcm/单位体"的上限。
若数量不足则取 cnt[i]。
枚举 k（0 到 r）代表用 k 个 i 去凑余数（模 840 部分）。
f[i+1][j+k*i] 转移，并更新剩余 i 单位能换算成多少个"840 的整数倍"：(cnt[i]-k)/(M/i)。
也就是说：每种单位 i 的 M/i 个可以构成一个"840 基数"，DP 只枚举余数部分（0-r）‍，整数倍直接计入新维度，从而把 840 以内的余数空间压缩。构造使复杂度从 O(n·m) 降到 O(8·840·840)
遍历所有余数 j（容量不超过 w）。
如果 f[9][j] 可达，计算能放入的总价值：j + M * min(f[9][j], (w-j)/M)。
j 是余数部分占的体积。
剩余的容量 (w-j) 里的 840 整数倍用 M 去填，最多填 (w-j)/M 个，但受 f[9][j]（拥有的 840 基数总数）限制，取 min。
取所有余数 j 中的最大值。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define int long long
using namespace std;

constexpr int N = 10, L = 900, M = 840;
int w, cnt[N], f[N][L*N];
signed main() {
    fast;
    cin >> w;
    rep(i,1,8) cin >> cnt[i];
    memset(f,-1,sizeof(f)); f[1][0] = 0;
    rep(i,1,8) rep(j,0,M*8) {
        if (f[i][j] == -1) continue;
        int r = M/i;
        if (cnt[i] < r) r = cnt[i];
        rep(k,0,r) f[i+1][j+k*i] = max(f[i+1][j+k*i],f[i][j]+(cnt[i]-k)/(M/i));
    }
    int ans = 0;
    rep(j,0,M*8) {
        if (j > w || f[9][j] == -1) continue;
        ans = max(ans, j+M*(min(f[9][j],(w-j)/M)));
    }
    cout << ans;
    return 0;
}