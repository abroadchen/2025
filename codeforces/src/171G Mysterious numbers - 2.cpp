//
// Created by Psy.C on 2025/11/28.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    int a, b, c; cin >> a >> b >> c;
    ll f[30]; f[0] = a; f[1] = b;
    for (int i = 2; i <= c; ++i) f[i] = f[i - 1] + f[i - 2];
    cout << f[c];
    return 0;
}