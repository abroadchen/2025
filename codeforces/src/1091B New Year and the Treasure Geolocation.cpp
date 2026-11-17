//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll s1, s2;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= 2*n; i++) {
        cin >> x, s1 += x;
        cin >> x, s2 += x;
    }
    cout << s1/n << ' ' << s2/n;
    return 0;
}