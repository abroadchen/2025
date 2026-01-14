//
// Created by Psy.C on 2026/1/13.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
using namespace std;


int main() {
    fast;
    int n, a[N], cnt = 0; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) if (a[i] != a[i+1]) cnt++;
    cout << cnt << '\n';
    return 0;
}