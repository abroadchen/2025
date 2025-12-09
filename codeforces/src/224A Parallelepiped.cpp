//
// Created by Psy.C on 2025/12/9.
//

#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int ab, bc, ac; cin >> ab >> bc >> ac;
    const int a = static_cast<int>(sqrt(ab * ac / bc)),
    b = static_cast<int>(sqrt(ab * bc / ac)),
    c = static_cast<int>(sqrt(bc * ac / ab));
    cout << 4 * (a + b + c) << '\n';
    return 0;
}