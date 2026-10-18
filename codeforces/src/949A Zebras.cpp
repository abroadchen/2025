//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 2e5+5;
char s[N];
int l, cnt, mx;
vector<int> q[N];
int main() {
    fast;
    cin >> s; l = strlen(s);
    rep(i,l) {
        if (s[i] == '0') q[cnt++].push_back(i+1);
        else {
            if (cnt == 0) { cout << -1 << '\n'; return 0; }
            q[--cnt].push_back(i+1);
        }
        mx = max(mx, cnt);
    }
    if (cnt != mx) { cout << -1 << '\n'; return 0; }
    cout << cnt << '\n';
    rep(i,cnt) {
        cout << q[i].size();
        for (int j : q[i]) cout << ' ' << j;
        cout << '\n';
    }
    return 0;
}