//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector e(n, vector(n, false));
    vector v(n, vector(n, vector<int>()));
    for (int i = 0, x, y, k; i < m; ++i) {
        cin >> x >> y; x--, y--; e[x][y] = true;
        cin >> k; v[x][y].resize(k);
        rep(j, k) { cin >> v[x][y][j]; v[x][y][j]--; }
    }
    vector<tuple<int,int,int,vector<int>>> f[2][2];
    rep(x,n) rep(y,n) if (e[x][y]) rep(i,v[x][y].size()+1) {
        if ((!i || v[x][y][i-1]==x) && (i==v[x][y].size() || v[x][y][i]==y)) {
            vector<int> l, r; l.assign(v[x][y].rend()-i, v[x][y].rend());
            if (!l.empty()) {
                bool ok = true;
                for (int j = 0; j+1<l.size() && l.size()<=2*n+1; ++j) {
                    if (!e[l[j+1]][l[j]]) { ok = false; break; }
                    auto& f = v[l[j+1]][l[j]];
                    l.insert(l.end(), f.rbegin(), f.rend());
                }
                if (!ok || l.size() > 2*n+1) break;
            }
            r.assign(v[x][y].begin()+i, v[x][y].end());
            if (!r.empty()) {
                bool ok = true;
                for (int j = 0; j+1<r.size() && r.size()<=2*n+1; ++j) {
                    if (!e[r[j]][r[j+1]]) { ok = false; break; }
                    auto& f = v[r[j]][r[j+1]];
                    r.insert(r.end(), f.begin(), f.end());
                }
                if (!ok || r.size() > 2*n+1) break;
            }
            vector<int> a;
            a.insert(a.end(), l.rbegin(), l.rend());
            a.insert(a.end(), r.begin(), r.end());
            f[!l.empty()][!r.empty()].emplace_back(l.empty() ? x : l.back(),
                r.empty() ? y : r.back(), l.size() + r.size(), a);
        }
    }
    return 0;
}