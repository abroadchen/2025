//
// Created by Psy.C on 2025/9/15.
//

#include <ios>
#include <iostream>
using namespace std;

int sumOfDigits(int A, int base) {
    int sum = 0;
    while (A > 0) {
        sum += A % base;
        A /= base;
    }
    return sum;
}

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int A; cin >> A;
    int totalSum = 0, count = A - 2;
    for (int base = 2; base <= A - 1; ++base)
        totalSum += sumOfDigits(A, base);

    int g = gcd(totalSum, count);
    int numerator = totalSum / g;
    int denominator = count / g;

    cout << numerator << "/" << denominator << endl;
    
    return 0;
}