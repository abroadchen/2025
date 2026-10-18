//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, num;
int main() {
    fast;
    while (cin >> n) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            cin >> num;
            ans += abs(num);
        }
        cout << ans << '\n';
    }
    return 0;
}