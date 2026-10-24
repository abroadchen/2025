//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
f[N][N]：f[j][i] 表示以 j 为起点、长度为 i+1（跨度 i）的区间"异或合并结果"。
mx[N][N]：mx[j][i] 表示 [j, j+i] 这个区间内，f[j][0..i] 的最大值
f[i][0] = a[i]：第 i 个元素、跨度 0 的合并结果就是它本身。
mx[i][0] = a[i]：单元素区间的最大值也是它本身
外层循环 i 从 1 到 n-1，表示区间的跨度（长度 - 1）。
内层循环 j 从 1 到 n-i，遍历所有起点，使区间 [j, j+i] 不越界。
f[j][i] = f[j][i-1] ^ f[j+1][i-1]：
递推公式。区间由两部分组成：以 j 开头跨度 i-1 的部分 [j, j+i-1]，和以 j+1 开头跨度 i-1 的部分 [j+1, j+i]。
两者异或得到跨度 i 的合并结果。这正是题目定义的逐层异或（f[l][r] = f[l][r-1]^f[l+1][r]）。
mx[j][i] = max(f[j][i], max(mx[j][i-1], mx[j+1][i-1]))：
维护 [j, j+i] 内所有 f 值的最大值：取当前 f[j][i]、左边子区间最大值 mx[j][i-1]、右边子区间最大值 mx[j+1][i-1] 三者的最大
读入查询次数 q。
每次查询 [l, r]，区间跨度为 r - l，直接输出 mx[l][r-l]——即之前预处理好的、该区间内所有异或合并结果的最大值。
O(1) 回答每个查询
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
using namespace std;

constexpr int N = 5050;

int n, f[N][N], mx[N][N], i, j, q, l, r;
int main() {
    fast;
    cin >> n;
    rep(i,n) { cin >> f[i][0]; mx[i][0] = f[i][0]; }
    rep(i,n-1) rep(j,n-i) {
        f[j][i] = f[j][i-1]^f[j+1][i-1];
        mx[j][i] = max(f[j][i], max(mx[j][i-1], mx[j+1][i-1]));
    }
    cin >> q;
    rep(i,q) {
        cin >> l >> r;
        cout << mx[l][r-l] << '\n';
    }
    return 0;
}