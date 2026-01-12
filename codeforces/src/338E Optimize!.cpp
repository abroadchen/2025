//
// Created by Psy.C on 2026/1/11.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 150000
#define inf 0x3f3f3f3f
using namespace std;

struct node { int l, r, mn, lz; } s[(N<<2)+5];

void build(const int k, const int l, const int r) {
    s[k].l = l; s[k].r = r;
    if (l == r) { s[k].mn = -l; return; }
    const int mid = (l + r) >> 1;
    build(k<<1, l, mid); build(k<<1|1, mid+1, r);
    s[k].mn = min(s[k<<1].mn, s[k<<1|1].mn);
}

void pushdown(const int k) {
    if (s[k].lz != 0) {
        s[k<<1].mn += s[k].lz; s[k<<1].lz += s[k].lz;
        s[k<<1|1].mn += s[k].lz; s[k<<1|1].lz += s[k].lz;
        s[k].lz = 0;
    }
}

void modify(const int k, const int l, const int r, const int x) {
    if (l > r) return;
    if (l <= s[k].l && s[k].r <= r) {//使用懒惰标记优化性能
        s[k].mn += x; s[k].lz += x; return;
    }
    pushdown(k);
    if (const int mid = (s[k].l + s[k].r) >> 1; r <= mid) modify(k<<1, l, r, x);
    else if (l > mid) modify(k<<1|1, l, r, x);
    else modify(k<<1, l, mid, x), modify(k<<1|1, mid+1, r, x);
    s[k].mn = min(s[k<<1].mn, s[k<<1|1].mn);
}

int main() {
    fast;
    int n, m, k, a[N+5], b[N+5], pos[N+5]; cin >> n >> m >> k;
    for (int i = 1; i <= m; ++i) cin >> a[i]; a[0] = -inf;//哨兵值
    sort(a + 1, a + m + 1); build(1, 1, m);
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
        pos[i] = static_cast<int>(lower_bound(a, a + m + 1, k - b[i]) - a);
    }
    for (int i = 1; i < m; ++i) modify(1, pos[i], m, 1);
    int ans = 0;
    for (int i = m; i <= n; ++i) {
        modify(1, pos[i], m, 1);//每次加入一个新元素，移除一个旧元素
        if (s[1].mn >= 0) ans++;
        modify(1, pos[i-m+1], m, -1);
    }
    cout << ans << '\n';
    return 0;
}