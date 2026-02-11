//
// Created by Psy.C on 2026/2/11.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;

int main() {
    fast;
    cin >> n;
    int flag = 0;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        if (x != y) { flag = 1; break; }
    }
    if (flag == 0) cout << "Poor Alex";
    else cout << "Happy Alex";
    return 0;
}