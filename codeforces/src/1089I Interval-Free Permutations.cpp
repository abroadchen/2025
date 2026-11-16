//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
读询问数 q 和模数 md。
定义 add/sub（加法/减法取模）、mul（用 long long 防止中间溢出后取模）
fac[i] = i!（模 md）。N = 400 为上限
rep(i,N) 这里 i 从 1 到 N。
w[i] 初始为 i!，然后对 j < i-1（rep(j,i-1) 即 j 从 1 到 i-2）减去 w[j] * (i-j)!。
这是一个递推求解：w[i] = i! - Σ_{j} w[j]·(i-j)!，它把某个生成函数"除自身"后求系数——典型如 w = W − (W卷积阶乘) 表示"不含某结构的组合计数"。这形式常见于 "环/排列中某元素" 之类。数学上是解 W(x)(1 - E(x)) = E(x) 型关系中提取单个结构系数的过程。
等效可理解为：w 是满足 w[0]=0（约定）下，Σ_{结构} w[j]·fac[i-j] 与 fac[i] 的递推
rep 都从 1 开始。转移：

dp[i][j] += dp[i-k][j-1] × k!
dp[i][j] 可理解为：把大小为 i 的对象分成 j 个部分，其中每个部分大小为 k，且每个部分内部有 k! 种排列方式。
这是经典的分拆/组合计数 DP：把 n 个元素分成 j 组，每组 k 个元素有序排列（乘 k!），相当于有标号的重组。组合意义类似 "有标号集合的划分且每组带顺序"
f[i] 初始为 i!。
减去 2·w[j]·(i-j)!（对 j 从 1 到 i-2）。
再减去 dp[i][j]·f[j]（j 从 3 到 i-1）。
最后把 f[2] 直接设为 2。
这是一个包含-排除 / 容斥式的递推：从 i!（所有排列）中减去"含某种禁忌结构"的计数。w 和 dp 都是辅助序列，f 是最终答案——典型如 "不含某类型子结构的排列 / 某自由度的对象计数"
对每个询问输出 f[n]（模 md）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define vi vector<int>
#define ll long long
using namespace std;

constexpr int N = 400;

int main() {
    fast;
    int q, md; cin >> q >> md;
    auto add = [&](int &x, int y) { x += y; if (x >= md) x -= md; };
    auto sub = [&](int &x, int y) { x -= y; if (x < 0) x += md; };
    auto mul = [&](int x, int y) { return (ll)x*y%md; };
    vi fac(N+1); fac[0] = 1;
    for (int i = 0; i < N; ++i) fac[i+1] = mul(fac[i], i+1);
    vi w(N+1);
    rep(i,N) {
        w[i] = fac[i];
        rep(j,i-1) sub(w[i], mul(w[j], fac[i-j]));
    }
    vector dp(N+1,vi(N+1)); dp[0][0] = 1;
    rep(i,N) rep(j,i) rep(k,i) add(dp[i][j], mul(dp[i-k][j-1], fac[k]));
    vi f(N+1);
    rep(i,N) {
        f[i] = fac[i];
        rep(j,i-1) sub(f[i], mul(2,mul(w[j],fac[i-j])));
        for (int j = 3; j < i; ++j) sub(f[i], mul(dp[i][j], f[j]));
    }
    f[2] = 2;
    while (q--) {
        int n; cin >> n;
        cout << f[n] << '\n';
    }
    return 0;
}