//
// Created by Psy.C on 2025/9/18.
//

#include <ios>
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int a1, b1, c1, a2, b2, c2; cin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2;

    if ((a1 == 0 && b1 == 0) && (a2 == 0 && b2 == 0) && c1 != c2) {
        cout << 0 << endl;
        return 0;
    }
    if ((a1 == 0 && b1 == 0 && c1 == 0) || (a2 == 0 && b2 == 0 && c2 == 0)) {
        cout << -1 << endl;
        return 0;
    }
    if ((a1 == 0 && b1 == 0 && c1 != 0) || (a2 == 0 && b2 == 0 && c2 != 0) && (c1 == c2)) {
        cout << 0 << endl;
        return 0;
    }
    if (a1 * b2 == b1 * a2 && b2 * c1 == c2 * b1 && c1 * a2 == c2 * a1) {
        cout << -1 << endl;
        return 0;
    }
    if (((a1 * b2) - (a2 * b1)) == 0) {
        cout << 0 << endl;
        return 0;
    }
    cout << 1 << endl;
    
    return 0;
}