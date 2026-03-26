//
// Created by Psy.C on 2026/3/26.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int x1, y1; cin >> x1 >> y1;
    int x2, y2; cin >> x2 >> y2;
    cout << max(abs(x2 - x1), abs(y2 - y1));
    return 0;
}