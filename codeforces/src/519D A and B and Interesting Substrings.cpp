//
// Created by Psy.C on 2026/3/1.
//
/**
v[i]：存储字符'a'+i的所有出现位置
将每个字符的位置按字符种类分组

对每个字符进行处理
mp：存储特定前缀和的出现次数
mp[dp[v[i][0]]] = 1：初始化第一个位置的前缀和
对于后续每个位置：
ans += mp[dp[v[i][j]-1]]：累加之前的前缀和
mp[dp[v[i][j]]]++：更新当前前缀和的计数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    vector<ll> c(26, 0);//权值数组
    for (ll& i : c) cin >> i;
    string s; cin >> s;
    ll n = s.length();
    vector<ll> dp(n+1, 0);
    for (int i = 0; i < n; ++i) dp[i+1] = dp[i] + c[s[i]-'a'];//累加当前字符的权值
    vector<vector<ll>> v(26);
    for (int i = 1; i <= n; ++i) v[s[i-1]-'a'].push_back(i);
    ll ans = 0;
    for (int i = 0; i < 26; ++i) {
        map<ll, ll> mp;
        if (v[i].empty()) continue;
        mp[dp[v[i][0]]] = 1;
        for (int j = 1; j < v[i].size(); ++j) {
            ans += mp[dp[v[i][j]-1]];
            mp[dp[v[i][j]]]++;
        }
    }
    cout << ans;
    return 0;
}