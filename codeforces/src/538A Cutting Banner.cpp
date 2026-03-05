//
// Created by Psy.C on 2026/3/5.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; ++i)
using namespace std;

string s;
int main() {
    fast;
    cin >> s;
    int l = s.size(); bool flag = false;
    rep(i,l) rep(j,l)
        if (s.substr(0,i)+s.substr(j+1) == "CODEFORCES")
            flag = true;
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}