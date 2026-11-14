//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
f[i][j]：前 i 个数中恰好选 j 个，且第 i 个必取时的最大和。
转移方程 f[i][j] = max(f[u][j-1] + a[i])，其中 u ∈ [i-k, i-1]。
q[] 是单调队列（存下标），用于把"找 max(f[i-1][u])"这一循环降至 O(1)
外层循环 rep(i,m) 只做了 m 轮，而不是按 a 的位置 n 轮。结合，本应在 j（位置）外层、i（个数）内层；但用户代码把两个维度交换了——外层是"选了几个"（i），内层是"位置下标"（j）。二者 DP 是等价的（都是填同样规模的状态表）。

每步含义：

if (l<=r && q[l]<j-k) l++：单调队列维护的是候选下标 u，要求 u ≥ j-k，所以队头小于 j-k 的过期下标被弹出的 if (l <= r && q[l] < j-k) l++ 模式。
if (l<=r) f[i][j] = f[i-1][q[l]] + a[j]：队头 q[l] 是在 [j-k, j-1] 范围内 f[i-1][u] 最大的那个 u，用它转移。
while (l<=r && f[i-1][j] >= f[i-1][q[r]]) r--：维护队列单调递减——f[i-1][j] 比队尾更优时弹出队尾的同类 while 维护模式。
q[++r] = j：j 入队，作为后续位置的新候选。
这样，找最大 U 的代价从 O(k) 降为均摊 O(1)
遍历 [n-k+1, n]，取 f[m][i] 的最大值。
含义：第 m 个（最后一个）被选的元素下标 i 必须满足 n - i ≤ k（与末尾 n 的间隔 ≤ k），保证尾边界约束成立。
初始 ans=-1，若全为负无穷则输出 -1（无解
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 5005;
constexpr ll inf = 1e18;

ll f[N][N], a[N];
int n, k, m, q[N];
int main() {
    fast;
    for (auto &i : f) for (auto &j : i) j = -inf;
    cin >> n >> k >> m;
    rep(i,n) cin >> a[i]; f[0][0] = 0;
    rep(i,m) {
        int l = 0, r = -1;
        for (int j = 0; j <= n; j++) {
            if (l <= r && q[l] < j-k) l++;
            if (l <= r) f[i][j] = f[i-1][q[l]] + a[j];
            while (l <= r && f[i-1][j] >= f[i-1][q[r]]) r--;
            q[++r] = j;
        }
    }
    ll ans = -1;
    for (int i = n-k+1; i <= n; i++) ans = max(ans, f[m][i]);
    cout << ans;
    return 0;
}