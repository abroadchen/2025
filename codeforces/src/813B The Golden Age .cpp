//
// Created by Psy.C on 2026/9/21.
//
/**
用 while 循环求出 x 的幂能达到的个数 cnt（即
x
c
n
t
−
1
≤
r
x
cnt−1
 ≤r 的幂个数）。
依次生成 xx = [1, x, x², …, x^{cnt-1}]，全部 ≤ r。
⚠️ 注意：如果 x == 1，rr /= 1 不会变小，会死循环。所以这道题的约束隐含 x, y ≥ 2
同理生成 yy = [1, y, y², …, y^{cnt-1}]
双层循环枚举所有
x
a
+
y
b
x
a
 +y
b
 。
用 set s 去重（!s.contains + insert）。
只保留落在 [l, r] 内的和，存入 ss（升序待排）
把坏点位置排序后，计算相邻坏点之间、以及端点坏点与区间边界 l、r 之间的"空白段长度"，取最大。
第一个坏点左边空段：ss[0] - l。
中间空段：ss[i] - ss[i-1] - 1。
最后一个坏点右边空段：r - ss[last]。
若 ss 为空（区间内无任何坏点），则整个 [l,r] 都是好段，长度 r-l+1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll x, y, l, r;
vector<ll> xx, yy, ss;
set<ll> s;
int main() {
    fast;
    cin >> x >> y >> l >> r;
    ll t = 1, cnt = 0, rr = r;
    while (rr > 0) { rr /= x; cnt++; }
    for (ll i = 0; i < cnt; ++i) { xx.push_back(t); t *= x; }
    t = 1; cnt = 0; rr = r;
    while (rr > 0) { rr /= y; cnt++; }
    for (ll i = 0; i < cnt; ++i) { yy.push_back(t); t *= y; }
    for (ll i : xx)
        for (ll j : yy)
            if (!s.contains(i+j) && i + j >= l && i + j <= r) {
                s.insert(i + j);
                ss.push_back(i + j);
            }
    ranges::sort(ss);
    ll ans = 0;
    for (ll i = 0; i < ss.size(); ++i) {
        if (i == 0) ans = max(ans, ss[i]-l);
        else ans = max(ans, ss[i]-ss[i-1]-1);
        if (i == ss.size()-1) ans = max(ans, r-ss[i]);
    }
    if (ss.empty()) ans = max(ans, r-l+1);
    cout << ans << '\n';
    return 0;
}