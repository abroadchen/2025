//
// Created by Psy.C on 2026/9/25.
//
/***
转移时枚举最后一段的起点 j+1（即第 k 段是区间 [j+1, i]）
其中 cost(j+1, i) = 区间 [j+1, i] 里不同元素的个数
lst[i]：第 i 个位置上的数上一次出现的位置（若第一次出现则为 0）。
作用：一段区间 [L, R] 里，某个元素是不是"在本段内第一次出现"，只需判断 lst[i] < L。
于是区间不同元素个数 cost(L, R) = sum over i in [L,R] of [lst[i] < L]
(a) 决策单调性 / 四边形不等式（Knuth / divide-conquer 优化）
tr[k][i] 记录取到 dp[k][i] 最优时，k-1 段的终点 j（决策点）。
决策单调性保证：tr[k][i-1] ≤ 最优j ≤ tr[k+1][i]，从而把枚举 j 的范围压缩，复杂度从 O(n²m) 降到约 O(n·m)。
这就是四边形不等式优化 / divide-and-conquer DP 优化中，用上下界限制枚举范围的标准写法（有些实现也叫 "DP 决策单调性 + 维护最优转移点区间"）
(b) 滚动维护 v[j] = cost(j+1, i)，利用 lst
当枚举到终点 i 时，每新增一个位置 i（往右扩展），对任意起点 j+1：
若 lst[i] < j+1（即 a[i] 在本段 [j+1, i] 内是首次出现），则这段的 distinct 数 +1。
通过 v[j+1] 增量维护，避免每次重新计算区间不同元素数。
u[] 是时间戳数组：u[j+1]==i 表示"j+1 这个状态在当前 i 轮已经更新过 v"，防止重复累加（因为 j 枚举可能重复触到同一 j+1）。这是常见的时间戳去重技巧
(c) DP 转移
枚举最后一段起点 j+1，取 dp[k-1][j] + cost(j+1,i)（v[j+1] 就是 cost）的最大值，并记录最优决策点 j
把前 n 个元素分成恰好 m 段的最大总价值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 35005, M = 55;

int n, lst[N], a[N];
void get() {
    int rec[N]{};
    for (int i = 1; i <= n; ++i) {
        lst[i] = rec[a[i]];//lst[i] = 数值 a[i] 上一次出现的位置
        rec[a[i]] = i;
    }
}

int m, tr[M][N], u[N], dp[M][N], v[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    get();
    for (int i = 1; i <= n; ++i) {
        for (int k = min(i, m); k >= 1; --k) {
            int l = max(tr[k][i-1], k-1),//决策点下界：利用 D&C 优化的 tr[k][i-1]
            r = tr[k+1][i] == 0 ? i-1 : tr[k+1][i];//决策点上界：tr[k+1][i]
            for (int j = l; j <= r; ++j) {
                if (u[j+1] != i) {//时间戳优化：每个 j 只在本次 i 首次访问时更新 v[j+1]
                    u[j+1] = i;//标记 j+1 已在本轮 i 被处理
                    v[j+1] += lst[i] < j+1;//若 a[i] 上一次出现 < j+1，则它在 [j+1,i] 内算"新元素"，贡献+1
                }
                if (dp[k][i] < dp[k-1][j] + v[j+1]) {
                    dp[k][i] = dp[k-1][j] + v[j+1];
                    tr[k][i] = j;
                }
            }
        }
    }
    cout << dp[m][n];
    return 0;
}