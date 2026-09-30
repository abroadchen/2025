//
// Created by Psy.C on 2026/9/30.
//
/**
给一个数组 a[1..n] 和三个系数 p, q, r，要找下标 i ≤ j ≤ k，使得

p*a[i] + q*a[j] + r*a[k]
最大。每个变量都可以独立选数组中的任意一段位置，但下标要满足 i ≤ j ≤ k 的先后顺序。允许选同一个位置（i=j=k
dp[0][i] : 在前 i 个元素里选一个位置作为 "第一段" 的最大值  → 即 max(p*a[x])  (x ≤ i)
dp[1][i] : 前 i 个元素里选好第一段和第二段的最大值          → max(p*a[x]+q*a[y])  (x≤y≤i)
dp[2][i] : 前 i 个元素里选好第一、二、三段的最大值          → max(p*a[x]+q*a[y]+r*a[z])  (x≤y≤z≤i)
用三维"(0/1/2)"分别表示已经确定了几个段。
初始 dp[*][0] 都设为负无穷，表示"还没有任何元素可选"时无法得到合法值。这样保证第一段必须真正选到一个元素
dp[0][i] = max(dp[0][i-1], p*a[i])：第一段要么在 i-1 之前已选好（沿用），要么就用 a[i]。取 max 是因为 p 可为负，选最大值即可（经典"最大子段"式前缀最优）。
dp[1][i] = max(dp[1][i-1], dp[0][i]+q*a[i])：在已经"选好第一段、并把 a[i] 当作第二段"的组合 vs 前面更优的第二段组合，取 max。
dp[2][i] = max(dp[2][i-1], dp[1][i]+r*a[i])：同理确定三段。
每个转移都是 max(不选当前下标的段, 用当前下标做该段)，而由于 dp 前缀已经包含"更早位置"的最优解，i≤j≤k 的次序自然得到保证（因为转移是自左向右递推，后一段总是在前一段的右侧或同一位置）
dp[2][n] = 前 n 个元素里选好三段的最大值，即题目所求的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
constexpr ll inf = -8e18;
ll n, p, q, r, dp[3][N];
int a[N];
int main() {
    fast;
    cin >> n >> p >> q >> r;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    dp[0][0] = dp[1][0] = dp[2][0] = inf;
    for (int i = 1; i <= n; ++i) {
        dp[0][i] = max(dp[0][i-1], p*a[i]);
        dp[1][i] = max(dp[1][i-1], dp[0][i]+q*a[i]);
        dp[2][i] = max(dp[2][i-1], dp[1][i]+r*a[i]);
    }
    cout << dp[2][n] << '\n';
    return 0;
}