//
// Created by Psy.C on 2026/11/16.
//

/**
真正学会的起点..
把 (组号, 权值) 排序，相同组号聚在一起
x = m 初始化为要选的总数。
对每一组：组的范围是 [i, j)。
循环 k = i .. j-2：把组内除最后一个之外的所有权值都扔进 v。
为什么留最后一个？因为最终 ans 要累加的是"从各组挑出来的额外"最小项，而每组至少留 1 个（那个"必须的1个"是免费/底数，不加进去）。所以每组至少有一个作为底数，其余的进 v 参与选择。
用 ranges::sort(a) 升序后，去掉的是组内最大/最后那个，把较小的都进候选。
--x：没组都占掉 1 个名额，x 就是"还剩多少名额可以从 v 里挑"。
关键语义：x 初始 = m，每过一组 --x 表示这组的必选 1 个名额先扣掉。最终 x = 还需要从 v（各组除各自保留的一个外）里选出的个数
把 v（所有"可再选"的权值）升序排序。
ans 累加前 x 个（最小的） → 得到最小组条件约束下的总权值

每种颜色必须买它颜色里最便宜的那件（保底），这 不同颜色数 件先确定下来，也正好对应每组留 1 个。
掏出每颜色剩下的较便宜的商品，混一起排序，再挑最便宜的补足到 m 件
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
#define ii pair<int, int>
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector<ii> a(n);
    rep(i,n) cin >> a[i].first;
    rep(i,n) cin >> a[i].second;
    ranges::sort(a);
    int x = m;
    vector<int> v;
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && a[j].first == a[i].first) ++j;
        for (int k = i; k+1 < j; ++k) v.push_back(a[k].second);
        --x;
    }
    ranges::sort(v);
    ll ans = 0;
    rep(i,x) ans += v[i];
    cout << ans << '\n';
    return 0;
}