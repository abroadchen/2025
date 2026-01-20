//
// Created by Psy.C on 2026/1/20.
//

#include <iostream>
#include <vector>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10000
using namespace std;

ll pri[] = { 2, 3, 5, 7, 11, 13 };

set<ll> all;
void dfs(const ll lim, const int idx, const ll val) {
    if (val > lim) return;
    all.insert(val);
    if (idx >= 6) return;
    ll t = val;
    while (t <= lim / pri[idx]) {
        t *= pri[idx];
        dfs(lim, idx + 1, t);
    }
    dfs(lim, idx + 1, val);
}

int main() {
    fast;
    ll n; cin >> n;
    dfs(2*n*n, 0, 1);
    const vector res(all.begin(), all.end());
    cout << res[0];
    for (int i = 1; i < n && i < res.size(); ++i)
        cout << ' ' << res[i];
    cout << '\n';
    return 0;
}