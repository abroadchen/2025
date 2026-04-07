//
// Created by Psy.C on 2026/4/4.
//
/**
n：元素总数
m：关系对的数量 约束条件数量
pos[N]：记录每个值对应的位置
dp[N]：动态规划数组，记录最小可达位置

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5, inf = 0x3f3f3f3f;
int n, m, pos[N], dp[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        pos[x] = i;//记录值x出现在位置i
        dp[i] = inf;
    }
    ll ans = 1ll*n*(n-1)/2+n;//长度大于1的区间数量+n个单元素区间
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        if (pos[u] > pos[v]) swap(u, v);//确保左边位置小于右边位置
        dp[pos[u]] = min(dp[pos[u]], pos[v]);//在u的位置记录到达v位置的最小值
    }
    for (int i = n - 1; i >= 1; --i)
        dp[i] = min(dp[i], dp[i+1]);//dp[i]包含从位置i开始能够到达的最远位置
    for (int i = 1; i < n; ++i) {
        if (dp[i] == inf) continue;
        ans -= n - dp[i] + 1;//减去不合法的区间数量（从dp[i]到n的区间）
    }
    cout << ans << '\n';
    return 0;
}