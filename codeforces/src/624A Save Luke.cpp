//
// Created by Psy.C on 2026/3/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double d, l, v1, v2, ans;
int main() {
    fast;
    cin >> d >> l >> v1 >> v2;
    ans = (l - d) / (v1 + v2);
    printf("%.20lf\n", ans);
    return 0;
}