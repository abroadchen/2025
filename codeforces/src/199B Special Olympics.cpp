//
// Created by Psy.C on 2025/12/4.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll sqr(const ll x) { return x * x; }
bool isr(const ll px, const ll py, const ll cx, const ll cy, const ll r, const ll R) {
    const ll d = sqr(px - cx) + sqr(py - cy);
    return d > sqr(r) && d < sqr(R);
}

bool ok(const ll px, const ll py, const ll x1, const ll y1, const ll r1,
    const ll R1, const ll x2, const ll y2, const ll r2, const ll R2) {
    return isr(px, py, x1, y1, r1, R1) ||
        isr(px, py, x2, y2, r2, R2);
}

int main() {
    fast;
    ll x1, y1, r1, R1, x2, y2, r2, R2;
    cin>>x1>>y1>>r1>>R1; cin>>x2>>y2>>r2>>R2;
    vector<tuple<ll,ll,ll>> c = {
        {x1, y1, r1},
        {x1, y1, R1},
        {x2, y2, r2},
        {x2, y2, R2}
    };
    int ans = 0;
    for (auto& i : c) {
        const ll cx = get<0>(i), cy = get<1>(i), cr = get<2>(i);
        bool in;
        if (cr > 1) in = ok(cx + cr - 1, cy, x1, y1, r1, R1, x2, y2, r2, R2);
        else in = ok(cx + cr/2, cy, x1, y1, r1, R1, x2, y2, r2, R2);
        const bool out = ok(cx + cr + 1, cy, x1, y1, r1, R1, x2, y2, r2, R2);
        if (in != out) ans++;
    }
    cout << ans << '\n';
    return 0;
}