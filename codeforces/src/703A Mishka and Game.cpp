//
// Created by Psy.C on 2026/4/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
int main() {
    fast;
    cin >> n;
    int m = 0, c = 0;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b;
        if (a > b) m++;
        if (a < b) c++;
    }
    if (m > c) cout << "Mishka\n";
    else if (m < c) cout << "Chris\n";
    else cout << "Friendship is magic!^^\n";
    return 0;
}