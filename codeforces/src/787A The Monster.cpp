//
// Created by Psy.C on 2026/9/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e4;
int main() {
    fast;
    int a, b, c, d; cin >> a >> b >> c >> d;
    for (int i = max(b, d); i <= N; ++i) {
        if (i%a == b%a && i%c == d%c) {
            cout << i;
            return 0;
        }
    }
    cout << "-1";
    return 0;
}