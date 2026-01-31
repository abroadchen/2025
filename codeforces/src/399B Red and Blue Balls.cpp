//
// Created by Psy.C on 2026/1/31.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ull unsigned long long
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    string s; cin >> s;
    ull ans = 0;
    for (int i = 0; i < n; ++i) if (s[i] == 'B')
        ans += static_cast<ull>(pow(2, i));
    cout << ans;
    return 0;
}