//
// Created by Psy.C on 2025/12/1.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int d, n, x, sum;

int main() {
    fast;
    cin >> d >> n;
    for (int i = 1; i < n; ++i) {
        cin >> x;
        sum += d - x;
    }
    cin >> x;
    cout << sum;
    return 0;
}