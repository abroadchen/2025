//
// Created by Psy.C on 2026/9/30.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;

string s[N];
int main() {
    fast;
    int n, i, j; cin >> n;
    for (i = 1; i <= n; ++i) {
        cin >> s[i];
        for (j = i-1; j >= 1; --j)
            if (s[i] == s[j]) {
                cout << "YES\n";
                j = -1;
            }
        if (j == 0) cout << "NO\n";
    }
    return 0;
}