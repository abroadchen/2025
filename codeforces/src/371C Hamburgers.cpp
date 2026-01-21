//
// Created by Psy.C on 2026/1/21.
//
/**
* c[i]: 初始拥有的第i种原料数量
p[i]: 第i种原料的单价
q: 总预算
x[i]: 配方中第i种原料的需求量
 *
*计算不花钱能生产的最大产品数量
用现有库存直接满足需求的部分
 *
*max(t * x[i] - c[i], 0ll): 第i种原料还需购买的数量
* p[i]: 购买成本
 *
 *O(log(q + Σc[i]))，主要是二分搜索的时间复杂度
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define inf 1<<30
using namespace std;

ll x[3], c[3], p[3], q;
bool ok(const ll t) {//能否额外生产 t 个产品
    ll sum = 0;
    for (int i = 0; i < 3; ++i)
        sum += max(t * x[i] - c[i], 0ll) * p[i];
    return q >= sum;
}


int main() {
    fast;
    string s;
    cin >> s >> c[0] >> c[1] >> c[2] >> p[0] >> p[1] >> p[2] >> q;
    for (const char i : s) {//统计配方中各种原料的需求量
        if (i == 'B') ++x[0];
        if (i == 'S') ++x[1];
        if (i == 'C') ++x[2];
    }
    ll mn = inf, ans = 0;
    for (int i = 0; i < 3; ++i) {
        if (x[i] == 0) continue;
        mn = min(mn, c[i]/x[i]);
    }
    ans += mn;
    for (int i = 0; i < 3; ++i) c[i] -= x[i] * mn;
    ll l = 0, r = q + c[0] + c[1] + c[2];
    while (l < r) {//能额外购买的最大生产数量
        if (const ll mid = (l + r + 1) >> 1; ok(mid)) l = mid;
        else r = mid - 1;
    }
    cout << ans + l << '\n';
    return 0;
}