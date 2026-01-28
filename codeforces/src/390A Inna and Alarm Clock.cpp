//
// Created by Psy.C on 2026/1/28.
//

#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    set<int> s1, s2;
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y;
        s1.insert(x); s2.insert(y);
    }
    cout << min(s1.size(), s2.size()) << '\n';
    return 0;
}