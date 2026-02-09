//
// Created by Psy.C on 2026/2/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x, y, z, a, b, c, k, m;

int main() {
    fast;
    cin >> x >> y >> z >> a >> b >> c >> k;
    (x+y+z+4)/5 + (a+b+c+9)/10 > k ? m = 1 : m = 2;
    if (m == 2) cout << "YES\n"; else cout << "NO\n";
    return 0;
}