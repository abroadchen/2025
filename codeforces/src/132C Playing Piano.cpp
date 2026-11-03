//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
n：序列长度。
a[i]：输入的原始数列。
dp[i][j]：DP 回溯数组。含义是 "若位置 i 取标签 j，那么位置 i-1 取的标签值"（即记录前驱）。这与通常存"能否到达/最小值"的 DP 不同，这里 dp 专门用于重建路径
位置 0 的标签可以是 1-5 任意值，前置状态设为 1（占位，表示"可由前面到达"）
若位置 i 用了标签 k，要根据 a[i] 与 a[i+1] 的大小关系给位置 i+1 选标签 j：
a[i] < a[i+1]：必须 k < j（上升 → 标签跟着增大）。
a[i] > a[i+1]：必须 k > j（下降 → 标签跟着减小）。
a[i] == a[i+1]：必须 k ≠ j（相等 → 标签不同）。
满足时，记录 dp[i+1][j] = k，表示"位置 i+1 用 j 时，前一位用 k"。
一个值被反复覆盖也没关系，因为只要找到任意一条可行路径即可
在最后一个位置 n-1，找一个可以用的标签 j（dp[n-1][j] 非 0，即可达）。
从后往前，通过 dp[i][j] 不断取前驱标签，把整个标签序列倒序存入 ans
若找不到任何可行序列（ans 为空），输出 -1（无解）。
否则逆序输出，还原成从位置 0 到 n-1 的正确标签顺序
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+5;

int n, a[N], dp[N][6];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    rep(i,5) dp[0][i] = 1;
    for (int i = 0; i < n-1; i++) rep(j,5) rep(k,5) {
        if (!dp[i][k]) continue;
        if (a[i] < a[i+1] && k < j) dp[i+1][j] = k;
        if (a[i] > a[i+1] && k > j) dp[i+1][j] = k;
        if (a[i] == a[i+1] && k != j) dp[i+1][j] = k;
    }
    vector<int> ans;
    rep(j,5) if (dp[n-1][j]) {
        ans.push_back(j);
        for (int i = n-1; i > 0; i--) {
            j = dp[i][j];//回溯前驱
            ans.push_back(j);
        }
        break;
    }
    if (ans.size() == 0) cout << "-1\n";
    else {
        for (int i = ans.size()-1; i >= 0; i--)
            cout << ans[i] << ' ';
    }
    return 0;
}