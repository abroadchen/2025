//
// Created by Psy.C on 2026/4/16.
//

#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

constexpr int N = 1e5+5;

vector<int> t[N];
bool vis[N];
int st[N], top;
int query(int x, int y) {
    if (t[x].empty()) return 0;
    if (!vis[x]) st[++top] = x, ranges::sort(t[x]), vis[x] = 1;
    return y >= t[x][0] && y <= t[x].back();
}

struct node {
    int x, y;
    bool operator<(const node& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    node operator-(const node &o) const {
        return {x - o.x, y - o.y};
    }
    ll operator*(const node &o) const {
        return 1ll*x*o.y - 1ll*y*o.x;
    }
};
using Poly = vector<node>;
Poly convexhull(Poly p) {
    if (p.size() <= 1) return p;
    ranges::sort(p, [&](const node &a, const node &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    int n = p.size();
    vector<node> hull(2*n);
    int sz = 0;
    for (int i = 0; i < n; i++) {
        while (sz >= 2 && (hull[sz-1]-hull[sz-2])*(p[i]-hull[sz-1]) < 0)
            sz--;
        hull[sz++] = p[i];
    }
    int t = sz;
    for (int i = n-2; i >= 0; i--) {
        while (sz > t && (hull[sz-1]-hull[sz-2])*(p[i]-hull[sz-1]) < 0)
            sz--;
        hull[sz++] = p[i];
    }
    hull.resize(sz-(sz>1));
    return hull;
}

template<class T>
void clear(T& ct) { ct.clear(); }

vector<ii> now, used;
int n, m;
void get() {
    Poly c; top = 0;
    for (int i = 1, x, y; i <= m; i++) {
        rd(x, y); used.emplace_back(x, y);
        now.emplace_back(x, y); t[x].push_back(y);
        if (x > 1) now.emplace_back(x-1, y);
        if (y > 1) now.emplace_back(x, y-1);
        if (x > 1 && y > 1) now.emplace_back(x-1, y-1);
    }
    ranges::sort(now), now.erase(ranges::unique(now).begin(), now.end());
    for (auto [x, y] : now) if (x < n && y < n) {
        if (query(x, y) && query(x+1, y) && query(x, y+1) && query(x+1, y+1))
            c.push_back({x, y});
    }
    c = convexhull(c);
    cout << c.size() << '\n';
    int sta = 0;
    for (int i = 1; i < c.size(); i++) {
        if (make_pair(c[i].x, c[i].y) < make_pair(c[sta].x, c[sta].y))
            sta = i;
    }
    for (int i = 0; i < c.size(); i++) {
        int idx = (sta + i) % c.size();
        cout << c[idx].x << ' ' << c[idx].y << '\n';
    }
    for (auto a: used | views::keys) clear(t[a]);
    while (top) vis[::st[top--]] = 0;
}

int main() {
    fast;
    while (rd(n, m), n) get();
    return 0;
}