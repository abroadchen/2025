//
// Created by Psy.C on 2026/3/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int k;
int main() {
    fast;
    cin >> k;
    if (k%2) {
        cout << "YES\n";
        if (k == 1) {
            cout << "2 1\n1 2\n";
            return 0;
        }
        cout << 2*(k+2) << ' ' << k*(k+2) << '\n';
        for (int i = 1; i <= k+2; ++i)
            for (int j = i + 1; j <= k+2; ++j) {
                if ((j%2==1 || j==2) && j==i+1) continue;
                cout << i << ' ' << j << '\n';
                cout << i+k+2 << ' ' << j+k+2 << '\n';
            }
        cout << 2 << ' ' << k+4 << '\n';
    } else cout << "NO\n";
    return 0;
}