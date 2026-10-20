//
// Created by Psy.C on 2026/10/20.
//

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


int main() {
    fast;
    long long n = rd();
    if (n == 0) cout << "Ehab";
    else if (n&1) cout << "Ehab";
    else cout << "Mahmoud";
    return 0;
}