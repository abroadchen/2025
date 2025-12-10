//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    int cnt = 0;
    ll a[15];
    for (int i = 0; i < 4; ++i) cin >> a[i];
    sort(a, a + 4);
    for (int i = 0; i < 4; ++i) if (a[i] != a[i + 1]) ++cnt;
    cout << 4 - cnt << '\n';
    return 0;
}