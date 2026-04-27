//
// Created by Psy.C on 2026/4/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a, d;
string s;
int main() {
    fast;
    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') a++;
        else d++;
    }
    if (a > d) cout << "Anton";
    else if (d > a) cout << "Danik";
    else cout << "Friendship";
    return 0;
}
