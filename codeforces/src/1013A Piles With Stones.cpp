//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

int n;
int main() {
    fast;
    while (cin >> n) {
        int s1 = 0, s2 = 0, x;
        rep(i,n) { cin >> x; s1 = s1 + x; }
        rep(i,n) { cin >> x; s2 = s2 + x; }
        if (s2 <= s1) cout << "Yes\n"; else cout << "No\n";
    }
    return 0;
}