//
// Created by Psy.C on 2026/10/7.
//
/**
s2[i] >= s[i]（不低于基准）；
s2[i] <= s[i] + g[i]（不超过基准+增益上限）；
相邻高度差不超过 1：|s2[i] - s2[i+1]| <= 1。
求满足约束的 s2，使得总提升量 sum = Σ(s2[i]-s[i]) 最小；若不可能，输出 -1
inf 作为哨兵（左右边界没有实际高度约束)
这两次都是松弛：s2[i] 被限制为同时不能超过"上界 s[i]+g[i]"和"相邻位置高度+1"。
s2[i-1]+1 约束：向右邻接（i 必须 ≤ 左边 +1）；
s2[i+1]+1 约束：向左邻接（i 必须 ≤ 右边 +1）。
因为用的是 s2[i+1]（还没更新的原值），所以需要正反两遍才能把左右约束都传播到位（类似 bellman-ford/分治传播）。
若某时刻 s2[i] 被压到 < s[i]，说明即使取最大也不满足相邻约束 → 无解，输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+5;
constexpr ll inf = 0x3f3f3f3f3f3f3f3fLL;
ll n, s2[N], s[N], g[N], sum;
int main() {
    fast;
    cin >> n;
    s2[0] = s2[n+1] = inf;
    for (int i = 1; i <= n; ++i) {
        cin >> s[i] >> g[i];
        s2[i] = s[i] + g[i];
    }
    for (int i = 1; i <= n; ++i) {
        s2[i] = min(s[i]+g[i], min(s2[i-1]+1, s2[i+1]+1));
        if (s2[i] < s[i]) { cout << "-1"; return 0; }
    }
    for (int i = n; i >= 1; --i) {
        s2[i] = min(s[i]+g[i], min(s2[i-1]+1, s2[i+1]+1));
        if (s2[i] < s[i]) { cout << "-1"; return 0; }
    }
    for (int i = 1; i <= n; ++i) sum += s2[i] - s[i];
    cout << sum << '\n';
    for (int i = 1; i <= n; ++i) cout << s2[i] << ' ';
    return 0;
}