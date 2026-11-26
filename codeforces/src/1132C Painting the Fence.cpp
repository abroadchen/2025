//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
对除 x 外的每条线段 [a[i], b[i]) 做差分：起点 a[i]-1 处 +1，终点 b[i] 处 −1（等价于闭范围 [a[i], b[i]] 每个点加 1）。
a[i]-1 是因为数组下标从 0 开始（rep 是 0 到 n-1）
差分数组做前缀和，p[i] 即位置 i 被多少条（剩余的）线段覆盖
p2[i+1] = 前 i 个位置里恰好被 1 条覆盖的个数。这是一维前缀和，O(1) 区间查询。
对每条保留的线段 i，计算它内部有多少点恰好被 1 条覆盖 = p2[b[i]] - p2[a[i]-1]。
但这里 用 max + 取负 -，即 ct = max(ct, -区间值) 等价于 ct = min(...)，其实是取最小值（负号技巧：max(-x) = -min(x)）。
含义：所有保留线段中，"独有点数"最少的那条的独有点数
p[i] > 0 表示位置 i 被至少 1 条覆盖。ct 加上所有被覆盖的位置数。
这样 ct = "被至少 1 条覆盖的总点数 − 最少独有点线段的独有点数"
枚举删除第 i 条线段，用 solve(i) 得删后"恰好被1条覆盖"的最大点数，全局取 max。
输出最大 ans
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
#define ll long long
using namespace std;

constexpr int N = 5010;

ll p[N], p2[N], ct, m, a[N], b[N], n;
ll solve(ll x) {
    memset(p, 0, sizeof(p)); memset(p2, 0, sizeof(p2));
    ct = LLONG_MIN;
    rep(i,m) if (i != x) p[a[i]-1]++, p[b[i]]--;
    rep(i,n) p[i] += p[i-1];
    rep(i,n) p2[i+1] = p2[i] + (p[i] == 1);
    rep(i,m) if (i != x) ct = max(ct, -(p2[b[i]]-p2[a[i]-1]));
    rep(i,n) ct += p[i] > 0;
    return ct;
}

ll ans;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> a[i] >> b[i];
    rep(i,m) ans = max(ans, solve(i));
    cout << ans;
    return 0;
}