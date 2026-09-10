//
// Created by Psy.C on 2026/9/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        ll n, x; cin >> n >> x;
        ll ans = 0;
        vector<ll> arr(n);
        map<ll, ll> mp;
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];
            mp[arr[i]]++;
        }
        ranges::sort(arr);
        for (int i = 0; i < n; ++i) {
            if (mp[arr[i]] <= 0) continue;
            if (mp[arr[i]*x] > 0) mp[arr[i]*x]--;
            else ans++;
            mp[arr[i]]--;
        }
        cout << ans << '\n';
    }
    return 0;
}