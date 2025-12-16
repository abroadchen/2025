//
// Created by Psy.C on 2025/12/15.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
using namespace std;

int min(const int a, const int b) { return a < b ? a : b; }
int max(const int a, const int b) { return a > b ? a : b; }

int vx, vy;
vector<int> c;
struct node {
    int l, r, h, d;
    void init(const int x, const int y, const int _h) {
        h = _h;
        int a[4], b[4], idx = 0;
        for (int i = x; i <= x + 1; ++i) {
            for (int j = y; j <= y + 1; ++j) {
                a[idx] = i * vy - j * vx;
                b[idx] = i * vx + j * vy;
                idx++;
            }
        }
        int mn = a[0], mx = a[0], mb = b[0];
        for (int i = 1; i < 4; ++i) {
            if (a[i] < mn) mn = a[i];
            if (a[i] > mx) mx = a[i];
            if (b[i] < mb) mb = b[i];
        }
        l = mn * 2; r = mx * 2; d = mb;
        c.push_back(l); c.push_back(r);
    }
    bool operator<(const node& o) const { return d < o.d; }
};
vector<node> cb;
map<int,int> mp;

struct sgt { int l, r, laz, val; } tr[N<<2];
void build(const int rt, const int l, const int r) {
    tr[rt].l = l; tr[rt].r = r;
    const int mid = (l + r) >> 1;
    tr[rt].laz = tr[rt].val = 0;
    if (l == r) return;
    build(rt<<1, l, mid);
    build(rt<<1|1, mid+1, r);
}

void down(const int rt) {
    if (tr[rt].laz) {
        tr[rt<<1].laz = max(tr[rt].laz, tr[rt<<1].laz);
        tr[rt<<1|1].laz = max(tr[rt].laz, tr[rt<<1|1].laz);
        tr[rt<<1].val = max(tr[rt].laz, tr[rt<<1].val);
        tr[rt<<1|1].val = max(tr[rt].laz, tr[rt<<1|1].val);
        tr[rt].laz = 0;
    }
}

int query(const int rt, const int l, const int r) {
    if (tr[rt].l == l && tr[rt].r == r) return tr[rt].val;
    down(rt);
    const int mid = (tr[rt].l + tr[rt].r) >> 1;
    if (r <= mid) return query(rt<<1, l, r);
    if (l > mid) return query(rt<<1|1, l, r);
    return min(query(rt<<1, l, mid), query(rt<<1|1, mid+1, r));
}

void up(const int rt) {
    tr[rt].val = min(tr[rt<<1].val, tr[rt<<1|1].val);
}

void update(const int rt, const int l, const int r, int val) {
    if (tr[rt].l == l && tr[rt].r == r) {
        tr[rt].laz = max(tr[rt].laz, val);
        tr[rt].val = max(tr[rt].val, val);
        return;
    }
    down(rt);
    const int mid = (tr[rt].l + tr[rt].r) >> 1;
    if (r <= mid) update(rt<<1, l, r, val);
    else if (l > mid) update(rt<<1|1, l, r, val);
    else {
        update(rt<<1, l, mid, val);
        update(rt<<1|1, mid + 1, r, val);
    }
    up(rt);
}

int main() {
    fast;
    int n; cin >> n >> vx >> vy; cb.clear(); mp.clear();
    int flag = 0;
    vector<vector<int>> h(n, vector<int>(n));
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        cin >> h[i][j];
    }
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        if (h[i][j] > 0) {
            node t{}; t.init(i, j, h[i][j]);
            cb.push_back(t);
        }
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    sort(cb.begin(), cb.end());
    const int sz = static_cast<int>(c.size()); build(1, 1, sz);
    ll ans = 0;
    for (int i = 0; i < n; ++i) mp[c[i]] = i + 1;
    for (auto& i : cb) {
        i.l = mp[i.l];
        i.r = mp[i.r];
        if (i.r < i.l) swap(i.l, i.r);
        if (i.r > i.l) i.r--;
    }
    for (const auto& i : cb) {
        if (i.l > i.r) continue;
        const int ret = query(1, i.l, i.r);
        if (ret < i.h) {
            ans += i.h - ret;
            update(1, i.l, i.r, i.h);
        }
    }
    cout << ans << '\n';
    return 0;
}
