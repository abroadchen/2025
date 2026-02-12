//
// Created by Psy.C on 2026/2/11.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll get(const ll p, const ll a) {//p的a次方
    ll s = 1;
    for (int i = 1; i <= a; ++i) s *= p;
    return s;
}

ll getnum(ll x) {//数字各位数之和
    ll w = 0;
    while (x) {
        w += x % 10;
        x /= 10;
    }
    return w;
}

ll a, b, c;
vector<ll> ans;
int main() {
    fast;
    cin >> a >> b >> c;
    ans.clear();
    for (ll i = 1; i <= 81; ++i) {
        if (const ll x = b * get(i, a) + c; x < 1000000000 && getnum(x) == i)
            ans.push_back(x);
    }
    cout << ans.size() << '\n';
    for (const ll an : ans) cout << an << ' ';
    return 0;
}