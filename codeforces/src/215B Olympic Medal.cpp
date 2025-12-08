//
// Created by Psy.C on 2025/12/7.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n; cin>>n;
    vector<double> x(n);
    for (auto &i : x) cin>>i;
    const double r1 = *max_element(x.begin(), x.end());
    ll m; cin>>m;
    vector<double> y(m);
    for (auto &i : y) cin>>i;
    const double p1 = *max_element(y.begin(), y.end());
    ll k; cin>>k;
    vector<double> z(k);
    for (auto &i : z) cin>>i;
    const double p2 = *min_element(z.begin(), z.end());
    double a, b; cin>>a>>b;
    cout << fixed << setprecision(12) <<
        sqrt(b * p1 * pow(r1, 2) / (a * p2 + b * p1)) << '\n';
    return 0;
}