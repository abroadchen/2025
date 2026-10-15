//
// Created by Psy.C on 2026/10/15.
//
/**
n：物品数；l, r：和的目标区间边界（后文会被改写）。
h[i]：第 i 个物品的"值/重量"。
b[i]：第 i 个物品的类别标记（0 或 1），用于把物品分到两组 st1 / st2。
t1, t2：两组物品各自的个数。
k1：所有 h[i] 之和。
dp[]：容量为 M 的背包 DP 数组。
inf = 1e4, INF = 1e6：数组规模界和 DP 的负无穷初值
读入 n、初始区间 [l, r]、每个物品的 h[i] 和类别 b[i]。
按 b[i] 是否为非零，把 h[i] 分别压入 st2（b 为真）或 st1（b 为 0）
k1 = Σh[i]：所有物品值总和。
把原始 [l, r] 做映射：l = k1-l, r = k1-r，再 swap(l,r)。
效果是：[l, r] 被对称翻转到关于 k1 的另一侧。也就是说，如果原来的题意是对总和 T 提出区间限制 l ≤ T ≤ r，那么翻转到"补集"的容量区间 k1-r ≤ 容量 ≤ k1-l。这通常发生在"一类物品要 +1、另一类要记录满足区间"的场景（与第一段代码的 ans 对称补集逻辑一脉相承）。
注意：这里翻转移交后，l、r 的含义已不再是输入的原始区间边界
对两类物品各自按值排序（DP 前不一定必须，但配合后面分组处理的一致性）
初始化：dp[0]=0，其余为 -INF（负无穷）。
对 st1 组做 0/1 背包，但只用 0/-INF 表示可达性：dp[j] 能否由 st1 中若干物品精确凑出和 j。
仅当 dp[j-st1[i]] == 0（即加之前的状态可达）时，把 dp[j] 置为 0（可达）。
所以这一步只标记 st1 组可凑出的和，不进入区间判定。
简写解读：if (dp[j-st1[i]]==0) dp[j]=0 是"可达"型转移，表示只用 st1 组物品能拼出和 j
对 st2 组做 0/1 背包（从大到小枚举容量）。
转移：dp[j] = max(dp[j], dp[j-st2[i]] + (j>=l&&j<=r))。
含义：在已经用 st1 组拼出基础和的代价之上，再把 st2 组的物品加进来；每到达一个落在 [l, r] 区间内的容量 j，就记 1 分（增加计数）。
由于 dp 之前存储的是"得分/计数"，这次 DP 是在 st1 可达性基础上叠加 st2 的贡献，目标是最大化落在区间内的容量数量
把区间夹到 [0, k1] 范围内。
在 [l, r] 内扫 dp[i] 取最大值作为 ans。
输出 ans（注意原代码没换行，cout << ans;）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; --i)
using namespace std;

constexpr int N = 5e5+5, M = 2e5+5, inf = 1e4, INF = 1e6;

int n, l, r, h[N], b[N], st1[N], st2[N], t1, t2, k1, dp[M];
int main() {
    fast;
    cin >> n >> l >> r;
    rep(i,1,n) cin >> h[i];
    rep(i,1,n) {
        cin >> b[i];
        if (b[i]) st2[++t2] = h[i];
        else st1[++t1] = h[i];
    }
    rep(i,1,n) k1 += h[i];
    l = k1-l, r = k1-r; swap(l, r);
    sort(st1+1, st1+t1+1);
    sort(st2+1, st2+t2+1);
    rep(i,0, inf) dp[i] = -INF; dp[0] = 0;
    rep(i,1,t1) per(j,k1,st1[i]) if (dp[j-st1[i]]==0) dp[j] = 0;
    for (int i = t2; i; --i) per(j,k1,st2[i])
        dp[j] = max(dp[j], dp[j-st2[i]]+(j>=l&&j<=r));
    int ans = 0; l = max(l, 0), r = min(r, k1);
    rep(i,l,r) ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}