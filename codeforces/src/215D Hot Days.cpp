//
// Created by Psy.C on 2025/12/7.
//
/*
*n：通行证种类数量
m：需要旅行的天数
t：单次通行费用
T：通行证有效期
x：每天通行次数
c：通行证价格
ans：累计最小费用，初始化为0
 *
*如果p ≤ 0，即通行证不划算（单次费用不低于节省值）：
直接使用单次购票策略
费用为：通行证价格c + 每天单次购票费用x * m
*如果p ≥ m，即通行证节省的价值超过所需天数：
直接购买一张通行证即可覆盖所有需求
费用为：通行证价格c
 *
*k = (m + p - 1) / p：需要购买的通行证数量（向上取整）
r1 = c * k：购买k张通行证的费用
r2 = c + x * m：购买一张通行证+单次购票的混合策略费用
选择两者中较小的费用加到总费用中
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int n, m; cin>>n>>m;
    ll t, T, x, c, ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> t >> T >> x >> c;
        const ll p = T - t;//通行证相对于单次购票的节省值
        if (p <= 0) ans += c + x * m;
        else if (p >= m) ans += c;
        else {
            const ll k = (m + p - 1) / p,
            r1 = c * k, r2 = c + x * m;
            ans += min(r1, r2);
        }
    }
    cout << ans << '\n';
    return 0;
}