//
// Created by Psy.C on 2026/4/15.
//
/**
计算满足某种条件的(i,j)对的个数：

对于每个i ∈ [1,n]，计算有多少个j ∈ [1,m]满足条件
条件可能是：(i+j)%5 == 0 或类似的同余条件
x = 5 - i%5是使得(i+x)%5 == 0的最小正整数
在[1,m]范围内，满足条件的j的个数是max(0, (m-x)/5+1)
时间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m;
int main() {
    fast;
    cin >> n >> m;
    if (m < n) swap(n, m);
    ll ans = 0;
    for (ll i = 1; i <= n; ++i) {
        ll x = 5 - i%5;//i距离下一个5的倍数的距离
        if (m >= x) ans += (m-x)/5+1;//满足条件的数的个数
    }
    cout << ans;
    return 0;
}