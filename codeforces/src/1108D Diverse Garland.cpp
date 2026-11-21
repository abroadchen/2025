//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 2e5+10;

char s[N];
int main() {
    fast;
    int n, cnt = 0; cin >> n;
    rep(i,n) cin >> s[i];
    for (int i = 2; i <= n; i++) if (s[i-1] == s[i]) {
        if (s[i-1] != 'R' && s[i+1] != 'R') { s[i] = 'R'; cnt++; continue; }
        if (s[i-1] != 'G' && s[i+1] != 'G') { s[i] = 'G'; cnt++; continue; }
        if (s[i-1] != 'B' && s[i+1] != 'B') { s[i] = 'B'; cnt++; continue; }
    }
    cout << cnt << '\n';
    rep(i,n) cout << s[i];
    return 0;
}