//
// Created by Psy.C on 2026/9/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string s, s2;
int main() {
    fast;
    cin >> s >> s2;
    for (int i = 0; i < s.size(); ++i)
        if (s[i] < s2[i]) {
            cout << -1 << '\n';
            return 0;
        }
    cout << s2 << '\n';
    return 0;
}