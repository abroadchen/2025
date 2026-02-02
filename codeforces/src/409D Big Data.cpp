//
// Created by Psy.C on 2026/2/2.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x; cin >> x;
    switch(x) {
        case 1: case 4: case 6: case 8: case 9: case 10: case 13: case 15:
            cout << "1\n"; break;
        case 2: case 3: case 5: case 7: case 11: case 12: case 14: case 16:
            cout << "0\n"; break;
        default:
            cout << "ERROR\n";
    }
    return 0;
}