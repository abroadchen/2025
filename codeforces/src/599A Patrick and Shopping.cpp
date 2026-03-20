//
// Created by Psy.C on 2026/3/20.
//
/**
买两个最便宜的汉堡各2个
买两个不同汉堡各2个
买三种汉堡各1个
买两个最便宜的汉堡各2个
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll d1, d2, d3, ans;
int main() {
    fast;
    cin >> d1 >> d2 >> d3;
    ans = min(min((d1<<1)+(d3<<1), (d2<<1)+(d3<<1)),
        min(d1 + d2 + d3, (d1<<1)+(d2<<1)));
    cout << ans << '\n';
    return 0;
}