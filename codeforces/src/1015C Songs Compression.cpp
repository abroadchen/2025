//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
g[i].a：某项切换前的值（较大）。
g[i].b：某项切换后的值（较小）。
g[i].d = a - b：切换该项能节省的量。
n：项目数；m：允许的总成本上限。
s1、s2：累加和（见下）。
x：需要削减的总量；s：已累计削减量；cnt：需要切换的项目数
s1 = 全用 a 的总成本（最坏情况）。
s2 = 全用 b 的总成本（最好情况）
s2 > m：即使把每一项都切成 b（降到最低），总成本仍大于上限 m，无论如何都做不到 → 输出 -1。
s1 <= m：一个都不切换（全是 a）总成本就已经 ≤ m → 输出 0
排序依据：cmp 使 g[i].d 从大到小，即把"节省最多的项目"排前面。
x = s1 - m：要让总成本从 s1 降到 m 以下，需要削减的总量就是 s1 - m。
从节省量最大的项目开始，逐个累加节省量 s，每切一个 d，直到 s >= x，此时统计已切换的项目数 cnt。
贪心正确性：要最少动几个项目达到目标，显然优先选节省量大的，所以按 d 降序贪心即可
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

struct node { ll a, b, d; } g[N];
inline int cmp(const node &a, const node &b) { return a.d > b.d; }

ll n, m, s1, s2, x, s, cnt;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> g[i].a >> g[i].b; g[i].d = g[i].a - g[i].b;
        s1 = s1 + g[i].a; s2 = s2 + g[i].b;
    }
    if (s2 > m) { cout << -1 << '\n'; return 0; }
    if (s1 <= m) { cout << 0 << '\n'; return 0; }
    sort(g+1, g+n+1, cmp);
    x = s1 - m;
    for (int i = 1; i <= n; i++) {
        if (s >= x) break;
        s = s + g[i].d; cnt++;
    }
    cout << cnt << '\n';
    return 0;
}