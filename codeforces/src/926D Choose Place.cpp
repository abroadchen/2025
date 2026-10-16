//
// Created by Psy.C on 2026/10/15.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int f[][9] = {
    0,0,0,0,0,0,0,0,0,
    0,3,3,0,4,4,0,3,3,
    0,3,3,0,4,4,0,3,3,
    0,2,2,0,3,3,0,2,2,
    0,2,2,0,3,3,0,2,2,
    0,1,1,0,2,2,0,1,1,
    0,1,1,0,2,2,0,1,1
}, mxx, mxy, mx;


char c[7][9];
int main() {
    fast;
    for (int i = 1; i <= 6; ++i)
        for (int j = 1; j <= 8; ++j) {
            cin >> c[i][j];
            if (c[i][j] == '.' && f[i][j] > mx) {
                mxx = i; mxy = j;
                mx = f[i][j];
            }
        }
    for (int i = 1; i <= 6; ++i) {
        for (int j = 1; j <= 8; ++j) {
            if (i == mxx && j == mxy) cout << 'P';
            else cout << c[i][j];
        }
        cout << '\n';
    }
    return 0;
}