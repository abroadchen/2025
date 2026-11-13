//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
dp[i][0]：走到第 i 步、落在 x[i] 时的最小"额外操作次数"（res 越大越差，inf 表示不可达）。
dp[i][1]：走到第 i 步、落在 y[i] 时的情况（对称）。
dp[0][0] = dp[0][1] = 0：起点，两步初始化为 0，表示还没消耗任何操作。
每次读入 x[i]、y[i] 时先把 dp[i][*] 设为 inf（初始不可达），然后通过 solve 逐步转移
计算 dp[i][0] 时，把"来源"的两个量 dp[i-1][0]（从上一行 x 列来）和 dp[i-1][1]（从上一行 y 列来）作为前两个参数传入。
计算 dp[i][1] 时对称：源分别是 dp[i-1][1] 和 dp[i-1][0]，且把 x、y 互换。
solve 返回的是从某个来源到达当前状态的最小代价
af：来源 A 的成本（如上一行同类列的成本）
bf：来源 B 的成本（如上一行异类列的成本）
xi：当前行的 x 值
yi：当前行的 y 值
逻辑：

只有 af <= k 或 bf <= k 时才可能成功转移（成本超过 k 说明上一个状态不可用）。
用向上取整计算需要的分组数 sum，构造出当前状态应等于 yi。
分两种匹配情况：
当 yi == sum 时，能精确匹配，代价为某个表达式（用 af+xi-sum*k 或 xi-sum*k）。
当 yi 落在 (sum, xi*k]（或 (sum, (xi-1)*k+k-bf]）区间时，用一次额外操作（代价 1）‍即可覆盖。
返回所有可行情况中的最小代价，都不可行则返回 inf
如果最后一步两种选择（x 或 y）都不可达（都是 inf），说明走不到终点，输出 "NO"。
否则说明存在可行的走法，输出 "YES"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 3e5+5, inf = 0x3f3f3f3f;

int k;
int solve(int af, int bf, int xi, int yi) {
    int res = inf;
    if (af <= k) {
        int sum = (af+xi+k-1)/k-1;//向上取整除法
        if (yi == sum) res = min(res, af+xi-sum*k);
        else if (yi > sum && yi <= 1ll*xi*k) res = min(res, 1);
    }
    if (bf <= k) {
        int sum = (xi+k-1)/k-1;
        if (yi == sum) res = min(res, xi-sum*k);
        else if (yi > sum && yi <= 1ll*(xi-1)*k+k-bf) res = min(res, 1);
    }
    return res;
}

int n, dp[N][2], x[N], y[N];
int main() {
    fast;
    cin >> n >> k; dp[0][0] = dp[0][1] = 0;
    rep(i,n) { cin >> x[i]; dp[i][0] = inf; }
    rep(i,n) { cin >> y[i]; dp[i][1] = inf; }
    rep(i,n) {
        dp[i][0] = solve(dp[i-1][0], dp[i-1][1], x[i], y[i]);
        dp[i][1] = solve(dp[i-1][1], dp[i-1][0], y[i], x[i]);
    }
    if (dp[n][0] == inf && dp[n][1] == inf) cout << "NO\n"; else cout << "YES\n";
    return 0;
}