//
// Created by Psy.C on 2025/12/22.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int t, a; cin >> t;
    while (t--) {
        cin >> a;
        if (360 % (180 - a) == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}