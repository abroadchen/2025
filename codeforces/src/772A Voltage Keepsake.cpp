//
// Created by Psy.C on 2026/9/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define db double
using namespace std;
constexpr int N = 1e5+100;

struct node { ll a, b; } c[N];
ll p, n;
bool check(db x) {
    db ans = x*p;
    for (ll i = 1; i <= n; i++)
        if (c[i].a*x > c[i].b)
            ans -= 1.0*c[i].a*x - 1.0*c[i].b;
    if (ans >= 0) return true;
    return false;
}


int main() {
    fast; cin >> n >> p;
    ll s1 = 0, s2 = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> c[i].a >> c[i].b;
        s1 += c[i].a; s2 += c[i].b;
    }
    db l = 0.0, r = 1e19;
    for (ll i = 0; i < 100; i++) {
        db mid = (1.0*l + 1.0*r)/2;
        if (check(mid)) l = mid; else r = mid;
    }
    if (l >= 1e18) printf("-1\n");
    else printf("%.10f\n", l);
    return 0;
}