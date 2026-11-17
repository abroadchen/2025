//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
a、b：两种资源（或两类单位）各自的总量上限。

w1、w2：每单位消耗权重
w1 = ceil(n/2)（向上取整），w2 = floor(n/2)（向下取整）——即奇偶划分（比如两种位置的配额）。

k：每天的需求系数。

t：搜索区间上界（可能是总资源或允许的天数上界）。
给定候选天数 x。
p = min(x, a)：资源 a 在 x 天里可用数量上限（x 天内每天至多用 1，总量不超过 a）。
q = min(x, b)：资源 b 同理。
sz = p*w1 + q*w2：两种资源加权后的总"产能"。
判定：若 sz >= x*k，说明 x 天内能达成 X ≥ 每天 k 的需求，返回 true。
这就是贪心+单调的可行性判断：产能随 x 单调不减，所以可以二分

读入参数并初始化权重
标准二分：l=0, r=t。
mid = (l+r)/2。
若 check(mid) 成立（可行），记录 ans = mid 并向右缩 l = mid+1 找更大可行值；
否则向左 r = mid-1。
ans 是不变量：'最后一个成功被记录的 mid'
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b, w1, w2, k;
bool check(ll x) {
    ll p = min(x, a), q = min(x, b);
    ll sz = p*w1 + q*w2;
    return sz >= x*k;
}

ll t, n, ans;
int main() {
    fast;
    cin >> t >> n >> a >> b >> k; w1 = (n+1)/2, w2 = n/2;
    ll l = 0, r = t;
    while (l <= r) {
        ll mid = (l+r)>>1;
        if (check(mid)) { ans = mid; l = mid+1; } else r = mid-1;
    }
    cout << ans << '\n';
    return 0;
}