//
// Created by Psy.C on 2026/2/14.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    if (n&1) cout << 9 << ' ' << n-9;
    else cout << 8 << ' ' << n-8;
    return 0;
}