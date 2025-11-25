//
// Created by Psy.C on 2025/11/23.
//

#include <algorithm>
#include <iostream>
using namespace std;

int n, k, l, c, d, p, nl, np;
int main() {
    ostream::sync_with_stdio(false);
    cin >> n >> k >> l >> c >> d >> p >> nl >> np;
    cout << min(p / (n * np), min((k * l) / (n * nl),
        (c * d) / n));
    return 0;
}