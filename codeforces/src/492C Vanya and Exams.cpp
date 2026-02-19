//
// Created by Psy.C on 2026/2/19.
//
/**
n: 课程数量
r: 每门课的最高分
avg: 目标平均分
sum: 需要增加的总分数
v: 存储(pair<成本/分, 可提升分数>)的向量

    if (sum >= v[i].second)                     // 需要的分数≥当前课程可提升量
        ans += v[i].first*v[i].second,          // 成本 = 单位成本 × 可提升量
        sum -= v[i].second;                     // 减少还需提升的分数
    else                                        // 需要的分数<当前课程可提升量
        ans += sum*v[i].first,                  // 成本 = 单位成本 × 实际需要量
        sum -= sum;                             // 已完成目标

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<ll, ll>
using namespace std;

ll n, r, avg, sum;
vector<ii> v;

int main() {
    fast;
    cin >> n >> r >> avg;
    sum = avg * n;//总目标分数
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;//a:当前分数, b:每分成本
        sum -= a;//还需增加的分数
        v.emplace_back(b, r-a);
    }
    ranges::sort(v);
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (sum <= 0) break;//达到目标
        if (sum >= v[i].second)
            ans += v[i].first*v[i].second, sum -= v[i].second;
        else
            ans += sum*v[i].first, sum -= sum;
    }
    cout << ans << '\n';
    return 0;
}