//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int l1, r1, l2, r2;
int main() {
    fast;
    int T = rd();
    while (T--) {
        l1 = rd(), r1 = rd(), l2 = rd(), r2 = rd();
        if (l1 != r2) cout << l1 << ' ' << r2 << '\n';
        else cout << l1 << ' ' << l2 << '\n';
    }
    return 0;
}