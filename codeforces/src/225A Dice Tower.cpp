//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, t, x, y; cin >> n >> t;
    while (n--) {
        cin >> x >> y;
        if (x == y || x == t || y == t ||
            x == 7 - t || y == 7 - t || x + y == 7) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}