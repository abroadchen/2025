//
// Created by Psy.C on 2026/10/18.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

struct node {
    int l, r, d;
    vector<int> e, s;
} v[N];

int n, t, ans;
vector<int> s;
int get(int x) {
    if (v[x].d) return v[x].r ? n : v[x].l;
    s.push_back(x); v[x].d = v[x].l = ++t;
    for (int i : v[x].e) v[x].l = min(v[x].l, get(i));
    if (v[x].l == v[x].d) {
        for (int y = 0; y != x; s.pop_back()) {
            y = s.back();
            v[y].r = x; v[x].s.push_back(y);
            if (x != y) v[x].e.insert(v[x].e.end(), v[y].e.begin(), v[y].e.end());
        }
        bool b = 0;
        for (int i : v[x].e) b |= v[i].r != x;
        (!b && (!ans || v[x].s.size() < v[ans].s.size())) && ((ans=x));
    }
    return v[x].l;
}

int m, h, a[N];
int main() {
    fast;
    cin >> n >> m >> h;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        if ((a[x]+1)%h == a[y]) v[x].e.push_back(y);
        if ((a[y]+1)%h == a[x]) v[y].e.push_back(x);
    }
    for (int i = 1; i <= n; ++i) get(i);
    cout << v[ans].s.size() << '\n';
    for (int i : v[ans].s) cout << i << ' ';
    return 0;
}