//
// Created by Psy.C on 2025/11/19.
//

#include <vector>
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n, sum = 0; cin >> n;
    vector<ll> v(n);
    for (ll i = 0; i < n; ++i) { cin >> v[i]; sum += v[i]; }
    ll mean = sum / n;
    if (mean * n != sum) { cout << "0"; return 0; }
    vector<int> lst;
    for (ll i = 0; i < n; ++i) if (v[i] == mean) lst.push_back(i+1);
    cout << lst.size() << '\n';
    for (auto x : lst) cout << x << ' ';
    return 0;
}