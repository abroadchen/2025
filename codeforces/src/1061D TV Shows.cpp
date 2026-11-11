//
// Created by Psy.C on 2026/11/11.
//

/**
真正学会的起点..
每个任务长度 len×y 的必付费用先累加。
按左端点 l 排序（处理顺序保证后续复用判断正确）
s 保存各已结束的"档"的结束时间 r（每个开着的档记录它何时空闲）
找所有结束时间 ≤ l（即当前任务开始前已空闲）的档中，lower_bound(l) 定位到第一个 ≥ l 的档
若没有空闲档可复用（k==s.begin()，即所有已结束档都晚于当前 l，最早结束的都 ≥ l，无法赶在任务开始前闲置）→ 新开一个档，付 x。
或虽有档但复用的"等待/衔接费用" (l - 最近结束时间)×y ≥ x：说明等它腾出来再用的花费比直接新开还贵 → 新开，付 x
--k 取的是复用最近结束的那个档（*k 是最接近 l 的可用结束时间），支付 (l - 该结束时间) × y 的空闲衔接费，然后复用该档

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; ++i)
#define ll long long
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7;

struct node {
    ll l, r;
    bool operator<(node o) const { return l < o.l; }
} t[N];

ll n, x, y, l, r, ans;
multiset<ll> s;
int main() {
    fast;
    cin >> n >> x >> y;
    rep(i,n) {
        cin >> l >> r; t[i].l = l, t[i].r = r;
        ans = (ans + (r-l)*y%mod) % mod;
    }
    sort(t+1, t+n+1);
    rep(i,n) {
        auto k = s.lower_bound(t[i].l);
        if (k == s.begin() || (t[i].l-*--k)*y >= x) ans = (ans + x%mod) % mod;
        else {
            ans = (ans + (t[i].l-*k)*y%mod) % mod;
            s.erase(k);
        }
        s.insert(t[i].r);
    }
    cout << ans << '\n';
    return 0;
}