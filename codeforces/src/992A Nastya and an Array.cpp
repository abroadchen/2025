//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n;
set<int> s;
int main() {
    fast;
    cin >> n;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        if (x == 0) continue;
        s.insert(x);
    }
    cout << s.size() << '\n';
    return 0;
}