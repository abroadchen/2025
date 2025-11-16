//
// Created by Psy.C on 2025/11/16.
//

#include <iostream>
using namespace std;

int n, k, s, p;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    for (cin >> n >> k; n--; s += 3 * k < p ? p - 3 * k : p % k) cin >> p;
    cout << s;
    return 0;
}