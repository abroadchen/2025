//
// Created by Psy.C on 2025/9/16.
//

#include <ios>
#include <iostream>
#include <algorithm>
using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b, x, y;
    cin >> a >> b >> x >> y;

    long long g = gcd(x, y);
    x /= g;
    y /= g;

    long long k = min(a / x, b / y);

    if (k > 0) cout << k * x << " " << k * y << endl;
    else cout << "0 0" << endl;
    
    return 0;
}