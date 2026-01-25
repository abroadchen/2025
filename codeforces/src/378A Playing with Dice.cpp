//
// Created by Psy.C on 2026/1/24.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int a, b; cin >> a >> b;
    int l1 = 0, l2 = 0, l3 = 0;
    for (int i = 1; i <= 6; ++i) {
        int x = i - a; x = abs(x);
        int y = i - b; y = abs(y);
        if (x < y) l1++;//更靠近a
        else if (x == y) l2++;
        else l3++;//更靠近b
    }
    cout << l1 << ' ' << l2 << ' ' << l3 << '\n';
    return 0;
}