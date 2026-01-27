//
// Created by Psy.C on 2026/1/27.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;

struct node { int w, v; } a[N];

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].v, a[i].w = i;
    sort(a + 1, a + 1 + n, [](const node a, const node b) {
        return a.v > b.v;
    });
    cout << a[1].w << ' ' << a[2].v;
    return 0;
}