//
// Created by Psy.C on 2026/2/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, a[5];
int main() {
    fast;
    cin >> n;
    if (n == 0) {
        cout << "YES\n";
        cout << "1\n1\n3\n3\n";
    } else {
        cin >> a[0];
        if (n == 1) {
            cout << "YES\n";
            cout << a[0] << '\n' << a[0]*3 << '\n' << a[0]*3 << '\n';
        }
        else if (n == 2) {
            cin >> a[1];
            sort(a, a + 2);
            if (a[0]*3 < a[1]) cout << "NO\n";
            else {
                cout << "YES\n";
                cout << a[0]*4-a[1] << '\n' << a[0]*3 << '\n';
            }
        }
        else if (n == 3) {
            cin >> a[1] >> a[2];
            sort(a, a + 3);
            if (a[2] == 3*a[0]) {
                cout << "YES\n";
                cout << a[0]*4-a[1] << '\n';
            }
            else if (a[2] < 3*a[0] && a[2] == a[0]*4-a[1]) {
                cout << "YES\n";
                cout << 3*a[0] << '\n';
            }
            else if (a[2]%3 == 0 && a[2]/3*4-a[0] == a[1]) {
                cout << "YES\n";
                cout << a[2]/3 << '\n';
            }
            else cout << "NO\n";
        }
        else if (n == 4) {
            cin >> a[1] >> a[2] >> a[3];
            sort(a, a + 4);
            if (a[3] != 3*a[0] || a[2] != a[0]*4-a[1]) cout << "NO\n";
            else cout << "YES\n";
        }
    }
    return 0;
}