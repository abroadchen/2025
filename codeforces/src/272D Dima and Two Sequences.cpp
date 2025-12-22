//
// Created by Psy.C on 2025/12/22.
//
/*
*键(key)：数组元素值
值(value)：该元素出现的次数
 *
 *mp[a[i]]++：在map中将a[i]对应的计数加1
 *cnt += b[i] == a[i]：如果相等则cnt加1，统计相同位置相等的元素个数
 *mp[b[i]]++：在map中将b[i]对应的计数加1
 *cnt > 0：还有相同位置相等的元素可以"消耗"
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100009
using namespace std;


int main() {
    fast;
    ll n, a[N], b[N], cnt = 0, m, ans = 1; cin>>n;
    map<ll,ll> mp;
    for (int i = 0; i < n; ++i) cin>>a[i], mp[a[i]]++;
    for (int i = 0; i < n; ++i) {
        cin>>b[i], cnt += b[i] == a[i], mp[b[i]]++;
    }
    cin>>m;
    for (const auto i : mp) {
        for (int j = 1; j <= i.second; ++j) {
            ll x = j;
            while (cnt > 0 && x % 2 == 0) x /= 2, cnt--;
            ans = ans * x % m;
        }
    }
    cout << ans % m;
    return 0;
}