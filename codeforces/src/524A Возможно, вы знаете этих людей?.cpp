//
// Created by Psy.C on 2026/3/2.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int n, k[N], s;
double m, l;
int main() {
    fast;
    cin >> n >> m;
    k[0] = 2, k[1] = 5, k[2] = 8;
    for (int i = 0; i < 3; ++i) {
        l = k[i]*n;
        s += (int)ceil(l/m);
    }
    cout << s << '\n';
    return 0;
}