//
// Created by Psy.C on 2026/2/10.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, m, t;

int main() {
    fast;
    cin >> n >> m;
    if (n >= m) t = m % 2; else t = n % 2;
    if (t == 0) cout << "Malvika"; else cout << "Akshat";
    return 0;
}