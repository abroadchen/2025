//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
v[i]：第 i 个物品的数值。
c[i]：第 i 个物品的花费。
f[i][k]：以第 i 个物品作为第 k 个（1/2/3）所选元素的上升子序列的最小总花费。
ans(inf)：最终答案，初始为无穷
第一步：f[i][1] = c[i]

以第 i 个物品作为三元组的第一个元素，最小花费就是它自身的 c[i]。
第二步：for k=2..3 转移

f[i][k] = 以 i 结尾、长度为 k 的递增子序列的最小花费。
枚举所有 j < i（用 rep(j,i-1)，即 j 从 1 到 i-1），若 v[j] < v[i]（保证严格递增），则可以用 f[j][k-1] + c[i] 构成"长度 k 以 i 结尾"的子序列。
对所有这样的 j 取 min
对所有"以 i 结尾、长度为 3"的子序列最小花费取 min，得到全局最小三元组花费。
若 ans 仍为 inf，说明不存在任何严格递增的三元组 → 输出 -1；否则输出 ans。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=(n); i++)
using namespace std;

constexpr int N = 3007, inf = 0x3f3f3f3f;

int n, i, j, k, v[N], c[N], f[N][4], ans(inf);
int main() {
    fast;
    cin >> n;
    rep(i,n) cin >> v[i];
    rep(i,n) cin >> c[i];
    memset(f, 0x3f, sizeof f);
    rep(i,n) {
        f[i][1] = c[i];
        for (k = 2; k <= 3; k++)
            rep(j,i-1) if (v[j] < v[i])
                f[i][k] = min(f[i][k], f[j][k-1]+c[i]);
    }
    rep(i,n) ans = min(ans, f[i][3]);
    cout << (ans == inf ? -1 : ans) << '\n';
    return 0;
}