//
// Created by Psy.C on 2026/1/11.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b, c, d; cin >> a >> b >> c >> d;
    int ans1, ans2;
    if (b * c >= a * d) { ans1 = b * c - a * d; ans2 = b * c; } else {
        ans1 = a * d - b * c; ans2 = a * d;
    }
    const int ans = __gcd(ans1, ans2);
    cout << ans1 / ans << '/' << ans2 / ans << '\n';
    return 0;
}