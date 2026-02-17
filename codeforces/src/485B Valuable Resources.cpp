//
// Created by Psy.C on 2026/2/17.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr ll inf = 1000000000;

int n;
ll a, b, mxa=-inf, mxb=-inf, mna=inf, mnb=inf;
int main() {
    fast;
    cin >> n;
    while (n--) {
        cin >> a >> b;
        mxa = max(mxa, a); mxb = max(mxb, b);
        mna = min(mna, a); mnb = min(mnb, b);
    }
    const ll ans = max(mxa-mna, mxb-mnb);
    cout << ans*ans;
    return 0;
}