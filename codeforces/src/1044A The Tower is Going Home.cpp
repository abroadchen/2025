//
// Created by Psy.C on 2026/11/6.
//

/**
真正学会的起点..
有 n 个 a 值（升序），m 条记录，每条是 (x1,x2,y)。
按 y 分组，相同 y 的多个 (x1,x2) 区间归为同一组（map<int, vector<ii>>）。
对每个 y 组：把该组区间按左端点排序后合并，找到第一个未被覆盖的"洞"。
若当前区间起点 l > lst+1，说明 lst+1 处是空隙 → 返回 lst+1。
否则扩展 lst=r（吞并重叠）。
全连续则洞在 最大右端点+1。
存进 p：每个 y 组产生一个阈值 p[组]=第一个洞的位置。
语义推测：p 值表示"该 y 组要能覆盖/阻止某 a，最小需要多少"
对每个可能的 a[i]（i=1..n+1，a[n+1]=inf 兜底）：
k1 = i-1：需要删掉/改前 i-1 个 a（代价）。
k2 = mp.size() - upper_bound(p, a[i])：p 中 > a[i] 的组数，即需要处理的 y 组数。
ans = min(ans, k1+k2)。
取所有 i 的最小值输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5, inf = 1e9;

int n, m, a[N], ans(inf);
map<int, vector<ii>> mp;
vector<int> p;
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    sort(a+1, a+n+1);
    for (int x1, x2, y; m; m--) {
        cin >> x1 >> x2 >> y;
        mp[y].emplace_back(x1, x2);
    }
    for (auto &[i, v] : mp) {
        ranges::sort(v);
        p.push_back([&]() {
            int lst = 0;
            for (auto [l, r] : v) {
                if (l > lst+1) return lst+1;
                lst = r;
            }
            return v.back().second + 1;
        }());
    }
    ranges::sort(p); a[n+1] = inf;
    rep(i,n+1) ans = min<int>(ans, (i-1)+(mp.size()-(ranges::upper_bound(p, a[i])-p.begin())));
    cout << ans << '\n';
    return 0;
}