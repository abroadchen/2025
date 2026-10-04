//
// Created by Psy.C on 2026/10/4.
//
/**
每个物品有 c 份、两种单价（a 和 b）。
若 a > b 就先全选 a（贪心取大者），把损失 a-b 与份数 c 存入 b1，并累加份数到 s1。
反正若 b > a（或相等走 else）就先全选 b，存入 b2，累加 s2
m 是某种「总容量/总需求」的模数。s1、s2 分别是两组选出来的份数总和。这里关键是：s1 + s2 > m 意味着两组的总份数（取模后的和）超过 m，此时不需要做任何"往下取整"调整，直接输出贪心最大答案。
当 s1 + s2 <= m 时，需要调整，使两组份数之和能凑成 m 的倍数（或满足某种分配约束）。做法是从损失最小的一组开始，把一部分从「取大者」切到「取小者」
排序后从小损失开始切：这保证用最小的总损失去把 s1 和 s2 分别降到「模 m 后的剩余」需要的水平。
c1、c2 分别是两组需要付出的「最小损失和」。
ans - min(c1, c2)：最终答案取两组中损失较小的一组来修正，整体仍是贪心最优 + 最小代价修正
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

int ans, s1, s2, c1, c2;
vector<ii> b1, b2;
signed main() {
    fast;
    int n, m; cin >> n >> m;
    for (int c, a, b; n--; )
        if (cin >> c >> a >> b, a > b) {
            ans += a*c;
            b1.emplace_back(a-b, c);
            s1 += c;
        } else {
            ans += b*c;
            b2.emplace_back(b-a, c);
            s2 += c;
        }
    s1 %= m, s2 %= m;
    if (s1 + s2 > m) return cout << ans, 0;
    ranges::sort(b1); ranges::sort(b2);
    for (auto [k1, k2] : b1) {
        c1 += min(k2, s1)*k1;
        s1 -= min(k2, s1);
        if (s1 <= 0) break;
    }
    for (auto [k1, k2] : b2) {
        c2 += min(k2, s2)*k1;
        s2 -= min(k2, s2);
        if (s2 <= 0) break;
    }
    cout << ans - min(c1, c2);
    return 0;
}