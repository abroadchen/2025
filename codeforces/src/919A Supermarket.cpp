//
// Created by Psy.C on 2026/10/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define inf 0x3f3f3f3f
using namespace std;

int n, m;
double a, b, p(inf);
int main() {
    fast;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            cin >> a >> b;
            if (a/b < p) p = a/b;
        }
        printf("%.8lf\n", m*p);
    }
    return 0;
}