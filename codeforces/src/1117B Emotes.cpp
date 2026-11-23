//
// Created by Psy.C on 2026/11/23.
//

/**
真正学会的起点..
维护最大值 m1、次大值 m2、以及最大值出现次数 cnt
若最大值有多个（cnt>1）：可以全用最大值 m1 填满 m 个，总和 m⋅m1。
若最大值只有一个（cnt==1）：必须穿插一个次大值——最优是"最大值/次大值交替"，那么次大值放
这就是"相邻不同"约束下用两种元素交替排列的最大和
最大有多个：仍全用 m1。
唯一最大：m/(k+1) 个位置必须放次大值（因为要保证与最大值的间隔），其余放最大值
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, k, ans;
int main() {
    fast;
    cin >> n >> m >> k;
    ll m1 = 0, m2 = 0, cnt = 1;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x > m1) m2 = m1, m1 = x, cnt = 1;
        else if (x > m2) m2 = x;
        else if (x == m1) cnt++;
    }
    if (k == 1) {
        if (cnt == 1) ans = (m-m/2)*m1+(m/2)*m2;
        else if (cnt > 1) ans = m*m1;
    } else {
        if (cnt > 1) ans = m*m1;
        else if (cnt == 1) ans = m/(k+1)*m2 + (m-m/(k+1))*m1;
    }
    cout << ans << '\n';
    return 0;
}