//
// Created by Psy.C on 2026/2/16.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, c;
int main() {
    fast;
    cin >> a >> b >> c;
    const int t[] = {
        a + b + c, a*b+c, a+b*c, a*b*c, (a+b)*c, a*(b+c)
    };
    int res = t[0];
    for (int i = 1; i < 6; ++i)
        if (res < t[i]) res = t[i];
    cout << res;
    return 0;
}