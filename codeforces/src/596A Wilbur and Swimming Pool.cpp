//
// Created by Psy.C on 2026/3/20.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 0x3f3f3f3f;
struct node { int x, y; } p[10];
int n;
int main() {
    fast;
    cin >> n;
    int mnx = inf, mny = inf, mxx = -inf, mxy = -inf;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        mnx = min(mnx, p[i].x); mxx = max(mxx, p[i].x);
        mny = min(mny, p[i].y); mxy = max(mxy, p[i].y);
    }
    if (n == 1) cout << -1 << '\n'; else {
        int ans = (mxx - mnx) * (mxy - mny);
        if (mxx == mnx || mxy == mny) cout << -1 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}