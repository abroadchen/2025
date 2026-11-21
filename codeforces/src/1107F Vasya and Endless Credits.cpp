//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
0x7f = 127
存每个物品的三元信息。
f[N]：物品数组
按 b（衰减速率）‍降序排序——b 大的排前面。直觉：衰减快的任务优先做，损失小
读入 n。
每读入一个物品的 a、b、k，同时设 dp[0][i] = -inf（把第 0 行、第 i 列初始化为"极小值"，标记该状态不可达/不合法）。
按 b 降序排序
当前物品的"基础贡献"
ll w = max(w, f[i].a - f[i].b * f[i].k);

计算从最早可处理时刻 k[i] 起算的衰减后净价值：a[i] - b[i]*k[i]。
w 与它取 max。⚠️ 但 w 从未被初始化，第一次迭代此时是 max(未初始化, 有效值) —— 未初始化读取是未定义行为。若编译器恰好把 w 停在 0（或任意小），则 w 会逐步被赋成"当前及之前任务中最大的一个这样的净收益"。本意大概是 w = max(w, ...) 想表示"取所有已处理物品中净收益最大者"作为统一补贴，但这写法有 UB，应当先用很小的初值（如 w = -inf 或读取第一个物品时初始化）。
结合 dp[i][0] = dp[i-1][0] + w 看，w 像一个"至少能获得的收益"，用于那些不占用新时间槽（列 0，即没有安排到具体位置）的情况。

第 0 列（未占时序槽）转移
dp[i][0] = dp[i-1][0] + w;

相当于：第 i 个物品"不占位置"时，收益沿用前 i-1 个的成果再加 w。
第 j 列（占位置 j）转移（1..n）
dp[i][j] = max(dp[i-1][j] + w, dp[i-1][j-1] + f[i].a - f[i].b*(j-1));

两种选择：
不把物品 i 安排在位置 j：状态由 dp[i-1][j] 加上 w。
把物品 i 安排在位置 j（第 j 个被处理的位置）：收益 = f[i].a - f[i].b * (j-1)（放在位置 j-1 之后，即延迟量 j-1），来自上一物品占位置 j-1 的 dp[i-1][j-1]。
取两者较大。
位置延迟做了 (j-1)，即认为第 j 个处理的位置对应延迟 j-1，衰减 b*(j-1)。
遍历 dp[n][0..n]（处理完所有物品后，占用 0-n 个时序位置的各种情况），取最大值作为答案 ans。
输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 510, inf = 0x7f;
struct node { ll a, b, k; } f[N];
bool cmp(node x, node y) { return x.b > y.b; }

ll ans, dp[N][N];
int main() {
    fast;
    int n; cin >> n;
    rep(i,n) { cin >> f[i].a >> f[i].b >> f[i].k; dp[0][i]  = -inf; }
    sort(f+1,f+n+1,cmp);
    rep(i,n) {
        ll w = max(w, f[i].a-f[i].b*f[i].k);
        dp[i][0] = dp[i-1][0] + w;
        rep(j,n) dp[i][j] = max(dp[i-1][j]+w,dp[i-1][j-1]+f[i].a-f[i].b*(j-1));
    }
    for (int i = 0; i <= n; i++) ans = max(ans, dp[n][i]);
    cout << ans << '\n';
    return 0;
}