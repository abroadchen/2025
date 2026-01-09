//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;

int n, a[N];
int query(int x, const int y) {
    int res = 0;
    while (x <= y) {
        for (int i = 1; i <= n; ++i) if (a[i] == x) x++;
        res++;
    }
    return res;
}


int main() {
    fast;
    int m; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cin >> m;
    for (int i = 1, op, x, y; i <= m; ++i) {
        cin >> op >> x >> y;
        if (op == 1) cout << query(x, y) << '\n';
        if (op == 2) swap(a[x], a[y]);
    }
    return 0;
}