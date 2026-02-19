//
// Created by Psy.C on 2026/2/19.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a, b;
int main() {
    fast;
    cin >> a >> b;
    for (int i = 1; i <= a; ++i) cout << i << ' ';
    for (int i = a+b+1; i >= a+1; --i) cout << i << ' ';
    return 0;
}