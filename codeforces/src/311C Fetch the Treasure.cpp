//
// Created by Psy.C on 2026/1/3.
//

#include <iostream>
#include <set>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
#define li pair<ll, int>
using namespace std;

template<typename T, typename U>
bool minn(T& a, U b) { return a > b ? a = b, true : false; }

constexpr int N = 1e5+7;
constexpr ll inf = 0x3f3f3f3f3f3f3f3f;

int main() {
    fast;
    ll h, d[N], a[N];
    memset(d, inf, sizeof(d));
    int n, m, k, c[N]; cin >> h >> n >> m >> k; d[0] = k;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> c[i], a[i]--;
    set<ii> s;
    bool b[N];
    for (int i = 1; i <= n; ++i) if (a[i] % k == 0) {
        s.insert({c[i], -i}); b[i] = true;
    }
    while (m--) {
        int op; cin >> op;
        if (op == 1) {
            ll x; cin >> x;
            priority_queue<li, vector<li>, greater<>> q;
            minn(d[x % k], x);
            for (int i = 0; i < k; ++i) if (d[i] < inf) q.emplace(d[i], i);
            while (!q.empty()) {
                const auto u = q.top().second; const ll dis = q.top().first;
                q.pop();
                if (dis > d[u]) continue;
                int v = ((static_cast<int>(u + x) % k) + k) % k;
                if (minn(d[v], dis + x)) q.emplace(d[v], v);
            }
            for (int i = 1; i <= n; ++i) {
                if (b[i]) continue;
                if (d[a[i] % k] > a[i]) continue;
                b[i] = true;
                s.insert({c[i], -i});
            }
        } else if (op == 2) {
            int x, y; cin >> x >> y;
            if (b[x]) {
                s.erase({c[x], -x});
                c[x] -= y;
                s.insert({c[x], -x});
            } else { c[x] -= y; }
        } else {
            if (s.empty()) cout << "0\n"; else {
                cout << s.rbegin()->first << '\n';
                s.erase(*s.rbegin());
            }
        }
    }
    return 0;
}