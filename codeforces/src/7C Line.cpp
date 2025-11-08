//
// Created by Psy.C on 2025/9/12.
//


#include <iosfwd>
#include <iostream>
using namespace std;

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long A, B, C;
    cin >> A >> B >> C;

    if (A == 0 && B == 0) {
        if (C == 0) cout << "0 0 \n";
        else cout << "-1\n";
        return 0;
    }

    if (A == 0) {
        if (C % B == 0) cout << "0 " << -C / B << "\n";
        else cout << "-1\n";
        return 0;
    }

    if (B == 0) {
        if (C % A == 0) cout << "0 " << -C / A << "\n";
        else cout << "-1\n";
        return 0;
    }

    long long x, y;
    long long gcd = extended_gcd(A, B, x, y);
    if (-C % gcd != 0) {
        cout << "-1\n";
        return 0;
    }

    long long scale = -C / gcd;
    x *= scale;
    y *= scale;

    cout << x << " " << y << "\n";
    return 0;
}