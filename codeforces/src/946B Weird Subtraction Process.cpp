//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll a, b;
int main() {
    fast;
    cin >> a >> b;
    while (true) {
        if (a == 0 || b == 0) break;
        if (a >= b*2) a = a%(b*2);
        else if (b >= a*2) b = b%(a*2);
        else break;
    }
    cout << a << ' ' << b << '\n';
    return 0;
}