//
// Created by Psy.C on 2026/3/11.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
string s;
int main() {
    fast;
    cin >> n >> s;
    int z = 0, o = 0;
    for (auto x : s) {
        if (x == '0') z++;
        else o++;
    }
    cout << n - 2*min(z, o) << '\n';
    return 0;
}