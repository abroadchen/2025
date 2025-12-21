//
// Created by Psy.C on 2025/12/20.
//
/*
*n: 数组长度
q: 查询次数
c[N]: 颜色数组，存储每个位置的颜色
v[N]: 值数组，存储每个位置的数值
dp[N]: 动态规划数组，存储以每种颜色结尾的最大值
*mx: 当前最大值对应的颜色
nxt: 当前次大值对应的颜色
 *
*遍历每个位置 i：
获取当前位置的颜色 col
计算当前值 cur，取两种情况的最大值：
继续之前的同色序列：dp[col] + a * v[i]
开始新的序列：b * v[i]
*如果当前颜色不是最优颜色，则考虑从最优颜色转移过来
如果当前颜色就是最优颜色，则考虑从次优颜色转移过来
*如果当前值比最优值更好，更新最优颜色，必要时更新次优颜色
否则如果当前值比次优值更好且颜色不同，更新次优颜色
*更新当前颜色的最佳值
更新全局最大值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

constexpr ll inf = 1ll<<56;
ll read() {
    int x; cin >> x;
    return 1ll * x;
}


int main() {
    fast;
    int n, q, c[N]; cin >> n >> q;
    ll v[N], dp[N];
    for (int i = 1; i <= n; ++i) v[i] = read();
    for (int i = 1; i <= n; ++i) cin >> c[i];
    while (q--) {
        const ll a = read(), b = read(); ll ans = 0;
        int mx = 0, nxt = 0;
        for (int i = 0; i <= n; ++i) dp[i] = -inf;
        for (int i = 1; i <= n; ++i) {
            const int col = c[i];
            ll cur = max(dp[col] + a * v[i], b * v[i]);
            if (col != mx) cur = max(cur, dp[mx] + b * v[i]);
            else cur = max(cur, dp[nxt] + b * v[i]);
            if (cur > dp[mx]) { if (mx != col) nxt = mx, mx = col; }
            else if (cur > dp[nxt] && col != mx) nxt = col;
            dp[col] = max(dp[col], cur);
            ans = max(ans, cur);
        }
        cout << ans << '\n';
    }
    return 0;
}