//
// Created by Psy.C on 2025/12/18.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m; cin>>n>>m;
    const int mn = min(n, m), d = n + m - 1 - mn;
    cout << d << ' ' << mn << '\n';
    return 0;
}