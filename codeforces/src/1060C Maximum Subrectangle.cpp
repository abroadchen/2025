//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
有两个数组 a[1..n]、b[1..m]，以及一个值 x。

我们构造一个矩阵：C[i][j] = a[i] * b[j]（即行列值相乘）。对任意"子矩形"（连续若干行 × 连续若干列），它的元素和记为：

sum(子矩形) = (a 中被选连续段的和) × (b 中被选连续段的和)
要求选出元素和 ≤ x 的子矩形，使其面积（行数×列数）最大，输出这个最大面积。

无解时输出 0（即一个都不选）
子矩形 = 选连续的行段 [i1..i2] + 连续列段 [j1..j2]。

其元素和：

Σ C[i][j] = (Σ a[i]) × (Σ b[j])
所以"选若干连续行 + 连续列"的约束分解为两个独立问题：

行段：一段连续 a 的和 = Σa；
列段：一段连续 b 的和 = Σb；
要求 (Σa) × (Σb) ≤ x；
面积 = (行段长度) × (列段长度)

对数组（比如 a），定义：
ma[len] = 在所有长度为 len 的连续子段中，最小的那个子段和。
为什么取最小？因为面积 = len_a × len_b，我们希望在 (Σa)·(Σb) ≤ x 前提下尽量放大两个长度。对固定长度 len，取和最小的子段能最大化满足 ≤ x 的机会（和越小越容易 ≤ x）。同理 mb[len]
外层枚举长度 i（1..n），内层枚举该长度子段的起点 j，sa[i+j-1]-sa[j-1] 是起点为 j、长 i 的子段和（用前缀和 O(1) 求），取最小存入 ma[i]。
对 b 同理得 mb[i]。
初始化 ma[], mb[] 全为 inf，然后取 min。
复杂度两层循环：O(n² + m²)
枚举行长度 i（1..n）、列长度 j（1..m）。
若 ma[i] * mb[j] ≤ x（最小行和×最小列和能满足约束），则可用面积 i*j 更新答案，取最大。
用 (ll) 防止相乘溢出 int。
最终输出 ans（无解时为 0，因为 1×1 也不满足则 ans 保持初始 0）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e3+1e2, inf = 0x3f3f3f3f;

int n, m, a[N], b[N], sa[N], sb[N], ma[N], mb[N], ans;
ll x;
int main() {
    fast; int i, j;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    cin >> x; sa[0] = sb[0] = 0;
    rep(i,n) sa[i] = sa[i-1] + a[i];
    rep(i,m) sb[i] = sb[i-1] + b[i];
    memset(ma, inf, sizeof(ma)); memset(mb, inf, sizeof(mb));
    rep(i,n) rep(j,n+1-i) ma[i] = min(ma[i],sa[i+j-1]-sa[j-1]);
    rep(i,m) rep(j,m+1-i) mb[i] = min(mb[i],sb[i+j-1]-sb[j-1]);
    rep(i,n) rep(j,m) if ((ll)ma[i]*(ll)mb[j] <= x) ans = max(ans, i*j);
    cout << ans << '\n';
    return 0;
}