//
// Created by Psy.C on 2026/3/31.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n;
string s[N];
map<string, int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> s[i];
    for (int i = n; i >= 1; --i) {
        if (mp[s[i]]) continue;
        mp[s[i]] = 1, cout << s[i] << '\n';
    }
    return 0;
}