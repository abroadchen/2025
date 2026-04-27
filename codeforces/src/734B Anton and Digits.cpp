//
// Created by Psy.C on 2026/4/27.
//
/**
首先用n2, n5, n6三者的最小值组成一种价值为256的组合
然后用剩余的n2和n3组成另一种价值为32的组合
最终求出总的最大价值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n2, n3, n5, n6;
int main() {
    fast;
    cin >> n2 >> n3 >> n5 >> n6;
    int mn = min(n2, min(n5, n6));
    ll ans = mn*256; n2 -= mn; n5 -= mn; n6 -= mn;
    mn = min(n3, n2);
    ans += mn*32;
    cout << ans << '\n';
    return 0;
}