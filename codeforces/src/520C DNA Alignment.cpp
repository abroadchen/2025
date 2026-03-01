//
// Created by Psy.C on 2026/3/1.
//
/**
n：字符总数
mx：出现频率最高的字符的出现次数
l：出现次数等于最大次数的不同字符数
r：总的字符数量（也就是 n）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int mod = 1e9+7;

ll ksm(ll a, ll b) {
    ll ans = 1;
    while (b) {
        if (b&1) ans = ans*a%mod;
        a = a*a%mod;//底数平方，指数相应减半
        b>>=1;
    }
    return ans%mod;
}

ll n, mx;
map<char, ll> mp;///统计每个字符的出现次数
char c;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c; mp[c]++;
        mx = max(mp[c], mx);//维护最高频字符的出现次数
    }
    ll l = 0, r = n;
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        if (mx == it->second) l++;//出现次数为 mx 的不同字符的数量
    }
    ll ans = ksm(l, r);//l 是出现频次最多的字符种类数，r 是总长度
    cout << ans << '\n';
    return 0;
}