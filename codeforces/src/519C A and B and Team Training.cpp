//
// Created by Psy.C on 2026/3/1.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b, d;
int main() {
    fast;
    cin >> a >> b;
    if (a <= 1 && b <= 1) cout << 0;
    else if (b > a*2+2) cout << a;
    else if (a > b*2+2) cout << b;
    else {
        d = (a + b)/3;
        cout << d;
    }
    return 0;
}