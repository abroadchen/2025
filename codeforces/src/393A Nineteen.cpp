//
// Created by Psy.C on 2026/1/29.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    string s; cin >> s;
    int n = 0, e = 0, i = 0, t = 0;
    for (const char j : s) {
        if (j == 'n') n++;
        else if (j == 'e') e++;
        else if (j == 'i') i++;
        else if (j == 't') t++;
    }
    if (n < 3) cout << 0; else {
        n -= 1; n /= 2; e /= 3;
        const int ans = min(n, min(i, min(e, t)));
        cout << ans << '\n';
    }
    return 0;
}