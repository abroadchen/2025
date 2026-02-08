//
// Created by Psy.C on 2026/2/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100001
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    bool f[N]{};
    for (int i = 1, x; i < n; ++i) {
        cin >> x; f[x] = true;
    }
    for (int i = 1; i <= n; ++i)
        if (!f[i]) { cout << i; return 0; }
    return 0;
}