//
// Created by Psy.C on 2026/2/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;

int main() {
    fast;
    cin >> n;
    if (n >= 6) {
        cout << "YES\n";
        cout << "1 + 2 = 3\n";
        cout << "3 - 3 = 0\n";
        for (int i = 1; i <= n; ++i) {
            if (i==1 || i==2 || i==3 || i==4 || i==6) continue;
            cout << i << " * 0 = 0\n";
        }
        cout << "0 + 4 = 4\n";
        cout << "4 * 6 = 24\n";
    }
    else if (n == 4) {
        cout << "YES\n";
        cout << "1 * 2 = 2\n";
        cout << "2 * 3 = 6\n";
        cout << "6 * 4 = 24\n";
    }
    else if (n == 5) {
        cout << "YES\n";
        cout << "3 * 5 = 15\n";
        cout << "2 * 4 = 8\n";
        cout << "1 + 8 = 9\n";
        cout << "9 + 15 = 24\n";
    }
    else cout << "NO\n";
    return 0;
}