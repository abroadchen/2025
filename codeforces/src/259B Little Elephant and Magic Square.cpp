//
// Created by Psy.C on 2025/12/19.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x11, x12, x13, x21, x22, x23, x31, x32, x33;
    cin >> x11 >> x12 >> x13 >> x21 >> x22 >> x23 >> x31 >> x32 >> x33;
    const int sum = (x12 + x13 + x21 + x23 + x31 + x32) / 2;
    x11 = sum - x12 - x13;
    x22 = sum - x21 - x23;
    x33 = sum - x31 - x32;
    cout << x11 << ' ' << x12 << ' ' << x13 << '\n';
    cout << x21 << ' ' << x22 << ' ' << x23 << '\n';
    cout << x31 << ' ' << x32 << ' ' << x33 << '\n';
    return 0;
}