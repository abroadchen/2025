//
// Created by Psy.C on 2026/10/14.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int x, y;
int main() {
    fast;
    cin >> x >> y;
    if (y == 0) cout << "No\n";
    else if (x == y-1) cout << "Yes\n";
    else if (x < y-1) cout << "No\n";
    else if ((x-y)%2 == 1 && y != 1) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}