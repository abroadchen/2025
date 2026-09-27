//
// Created by Psy.C on 2026/9/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k, ans;
char ch;
map<char, int> mp;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> ch; mp[ch]++;
        ans = max(ans, mp[ch]);
    }
    if (ans <= k) cout << "YES\n"; else cout << "NO\n";
    return 0;
}