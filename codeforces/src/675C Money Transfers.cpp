//
// Created by Psy.C on 2026/4/13.
//
/**
sum: 前缀和
ans: 记录前缀和出现的最大次数
mp: 映射前缀和值到其出现次数
n - ans: 需要删除的最少元素个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll x, sum, ans;
map<ll, ll> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x; sum += x; mp[sum]++;
        ans = max(ans, mp[sum]);
    }
    cout << n - ans << '\n';
    return 0;
}