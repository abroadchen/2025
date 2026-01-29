//
// Created by Psy.C on 2026/1/29.
//

#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 200009
#define inf 1e15
using namespace std;

struct node {
    int s, p;
    bool operator<(const node &o) const { return p < o.p; }
} no[N];

int n, k;
bool vis[N];
ll ok(const int p) {
    ll ans = 0; int c1 = 0;
    for (int i = 1; i <= n; ++i) c1++;
    c1 -= k - 1;
    int c2 = 0;
    for (int i = 1; i <= n && c2 < c1; ++i) if (no[i].s == p || no[i].s == p - 1) {
        ans += no[i].p;
        c2++;
        vis[i] = true;
    }
    for (int i = 1; i <= n && c2 < p; ++i) if (!vis[i]) {
        ans += no[i].p;
        c2++;
    }
    memset(vis, false, sizeof vis);
    return ans;
}


int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> no[i].s >> no[i].p;
    sort(no + 1, no + n + 1, [](const node &a, const node &b) {
        return a.s > b.s;
    });
    const int t = no[k].s; sort(no + 1, no + n + 1);
    ll ans = inf;
    for (int i = t; i <= t + 2; ++i) {
        if (i > n) break;
        ans = min(ans, ok(i));
    }
    if (ans == inf) ans = -1;
    cout << ans << '\n';
    return 0;
}