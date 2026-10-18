//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int main() {
    fast;
    int t = 1;
    while (t--) {
        int n, q; cin >> n >> q;
        for (int i = 1, t; i <= q; ++i) {
            cin >> t;
            while (true) {
                if (t&1) {
                    cout << (t+1)/2 << '\n';
                    break;
                }
                int res = n - t/2;
                t += res;
            }
        }
    }
    return 0;
}