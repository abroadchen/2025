//
// Created by Psy.C on 2026/2/3.
//
/**
 * x(价格), k(固定成本), m(特征数量), s(特征集合)
 *n(物品数量), m(总特征数), b(乘数)
 *
*外层循环遍历所有物品
内层循环更新状态转移方程：对于当前状态j，添加物品i的特征集后变为j|a[i].s，代价为dp[j] + a[i].x
更新最小结果：当所有特征都被覆盖时((1<<m)-1表示所有位都为1)，计算总成本dp[(1<<m)-1] + a[i].k * b
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;

constexpr ull inf = 1e19;
struct node { ull x, k, m, s; } a[110];//最多110个节点

int main() {
    fast;
    int n, m, b; cin >> n >> m >> b;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].k >> a[i].m;
        for (int j = 0; j < a[i].m; ++j) {//读取每个特征
            ull t; cin >> t;
            a[i].s |= 1<<(t-1);
        }
    }
    sort(a + 1, a + n + 1, [](const node& x, const node& y) {
        return x.k < y.k;
    });
    ull dp[1<<21]; dp[0] = 0;//没有特征的状态代价为0
    for (int i = 1; i < 1<<m; ++i) dp[i] = inf;
    ull res = inf;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 1<<m; ++j)
            dp[j|a[i].s] = min(dp[j|a[i].s], dp[j] + a[i].x);
        res = min(res, dp[(1<<m)-1] + a[i].k * b);
    }
    if (res == inf) cout << "-1\n"; else cout << res << '\n';
    return 0;
}