//
// Created by Psy.C on 2026/10/8.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s;
int main() {
    fast;
    int n; cin >> n >> s;
    int l = 0, r = 0, u = 0, d = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == 'L') l++;
        else if (s[i] == 'R') r++;
        else if (s[i] == 'U') u++;
        else if (s[i] == 'D') d++;
    }
    cout << ((min(l,r) + min(u, d))<<1) << '\n';
    return 0;
}