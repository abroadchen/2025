//
// Created by Psy.C on 2026/4/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int n, m;
int main() {
    fast;
    cin >> n >> m;
    int mat[n][m], r[n], c[m], i, j;
    for (i = 0; i < n; ++i) r[i] = 1;
    for (i = 0; i < m; ++i) c[i] = 1;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j) {
            int x; cin >> x;
            if (x) { r[i] = 0; c[j] = 0; }
        }
    return 0;
}