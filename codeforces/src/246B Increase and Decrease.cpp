//
// Created by Psy.C on 2025/12/16.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int sum = 0, a;
    for (int i = 0; i < n; ++i) { cin >> a;  sum += a; }
    cout << (sum % n == 0 ? n : n - 1) << '\n';
    return 0;
}