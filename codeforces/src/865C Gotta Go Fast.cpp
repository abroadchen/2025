//
// Created by Psy.C on 2026/10/4.
//
/**
n 个物品，每个物品有：选中时加 a[i]、不选中加 b[i]（或类似含义），以及以 p[i]% 概率选中。
sm = Σ b[i]，即所有"损耗/增益"的上界（DP 的容量维度 M=5000）。
s：某个目标阈值。
f[i][j]：从第 i 个物品开始决策、当前"累积值"为 j 时的某种"代价/期望"
f[n+1][j] 边界：超过阈值 s 的 j（j>s）要付出 mid 的额外惩罚（j+mid），否则为 0（=j? 不，是 =i，即 0——注意写了 i，实为 0）。
实际上 f[n+1][i] = i>s ? i+mid : i，当 i<=s 时等于 i？这里其实是以 0 为基准，写法让人困惑，但意图是：超过 s 就惩罚 mid。
状态转移：对第 i 个物品，若当前累计 j > s 已经超限，就只付 j+mid（惩罚路径，不再继续选）；否则在两种选择中取期望更小的：
以 p[i]% 概率选 a（变化 +a[i]）、以 (1-p)% 概率选 b（变化 +b[i]）。
取 min(直接结束 = j+mid, 继续决策的期望值)。
返回 f[1][0] < mid：判断从初始 j=0 开始、走完全部物品的最优期望代价是否 < mid
对 mid 做二分，check(mid) 返回真（f[1][0] < mid）则说明 mid 偏大，把上界 r 下调；否则上调 l。最终 l 收敛到本问题的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define eps 1e-11
using namespace std;
constexpr int N = 55, M = 5e3+5, inf = 1e9;

int sm, n, s, a[N], b[N], p[N];
ld f[N][M], l, r;
bool check(ld mid) {
    for (int i = 0; i <= sm; ++i) f[n+1][i] = i > s ? i + mid : i;
    for (int i = n; i >= 1; --i) {
        for (int j = 0; j <= sm; ++j)
            f[i][j] = j > s ? j+mid : min(j+mid,
                p[i]/100.0*f[i+1][j+a[i]]+(1-p[i]/100.0)*f[i+1][j+b[i]]);
    }
    return f[1][0] < mid;
}

int main() {
    fast;
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i] >> p[i], sm += b[i];
    r = inf;
    while (l+eps < r) {
        ld mid = (l+r)/2;
        if (check(mid)) r = mid; else l = mid;
    }
    printf("%.10Lf", l);
    return 0;
}