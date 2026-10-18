//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, s, h, mx;
string s1, s2;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s1 >> s2;
        if (s2 == "soft") ++s; else ++h;
    }
    if (s > h) mx = s; else mx = h;
    for (int i = 1; i <= n; ++i) {
        int k = (i*i+1)>>1;
        if (i*i >= n && k >= mx) {
            cout << i << '\n';
            return 0;
        }
    }
    return 0;
}