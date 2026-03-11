//
// Created by Psy.C on 2026/3/12.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (x == 1) {
            cout << "-1\n";
            return 0;
        }
    }
    cout << "1\n";
    return 0;
}