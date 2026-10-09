//
// Created by Psy.C on 2026/10/9.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll sz, v, tot, cnt;
vector<ll> vc;
int main() {
    fast;
    cin >> cnt;
    for (int i = 1; i <= cnt; ++i) { cin >> v; tot += v; }
    for (int i = 1; i <= cnt; ++i) { cin >> sz; vc.push_back(sz); }
    ranges::sort(vc);
    if (vc[cnt-1]+vc[cnt-2] >= tot) cout << "YES"; else cout << "NO";
    return 0;
}