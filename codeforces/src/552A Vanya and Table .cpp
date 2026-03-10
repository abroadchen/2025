//
// Created by Psy.C on 2026/3/10.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    int sum = 0, x1, y1, x2, y2;
    while (n--) {
        cin >> x1 >> y1 >> x2 >> y2;
        sum += (x2 - x1 + 1) * (y2 - y1 + 1);
    }
    cout << sum << '\n';
    return 0;
}