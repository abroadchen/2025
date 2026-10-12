//
// Created by Psy.C on 2026/10/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


signed main() {
    fast;
    int x1 = rd(), x2 = rd(), x3 = rd();
    if (x1 == 1 || x2 == 1 || x3 == 1) { cout << "YES"; return 0; }
    if (x1 == 2 && x2 == 2 || x1 == 2 && x3 == 2 || x2 == 2 && x3 == 2) { cout << "YES"; return 0; }
    if (x1 == 3 && x2 == 3 && x3 == 3) { cout << "YES"; return 0; }
    if ((x1==2&&x2==4&&x3==4)||(x2==2&&x1==4&&x3==4)||(x1==4&&x2==4&&x3==2)) {
        cout << "YES"; return 0;
    }
    cout << "NO";
    return 0;
}