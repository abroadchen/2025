//
// Created by Psy.C on 2025/9/14.
//

#include <ios>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long x; cin >> x;
    x = abs(x);

    long long n = 0, sum = 0;
    while (sum < x || (sum - x) % 2 != 0) {
        n++;
        sum += n;
    }

    cout << n << endl;
    return 0;
}