//
// Created by Psy.C on 2026/2/23.
//
/**
第一维表示线段树节点，第二维存储模M的各种余数情况
val存储原始数组值
i % val[l] == 0 时为2，否则为1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 100001, M = 60;

int tr[N<<2][M], val[N];
void build(const int k, const int l, const int r) {
    if (l == r) {
        for (int i = 0; i < M; ++i)
            tr[k][i] = 1+!(i%val[l]);
        return;
    }
    const int mid = (l+r)>>1;
    build(k<<1, l, mid); build(k<<1|1, mid+1, r);
    for (int i = 0; i < M; ++i)
        tr[k][i] = tr[k<<1][i] + tr[k<<1|1][(tr[k<<1][i]+i)%M];
}

void update(const int k, const int l, const int r, const int x) {
    if (l > x || r < x) return;
    if (l == r && l == x) {
        for (int i = 0; i < M; ++i)
            tr[k][i] = 1+!(i%val[l]);
        return;
    }
    if (const int mid = (l+r)>>1; x <= mid) update(k<<1, l, mid, x);
    else update(k<<1|1, mid+1, r, x);
    for (int i = 0; i < M; ++i)
        tr[k][i] = tr[k<<1][i] + tr[k<<1|1][(tr[k<<1][i]+i)%M];
}

int ans;
void query(const int k, const int l, const int r, const int x, const int y) {
    if (l > y || r < x) return;
    if (l >= x && r <= y) {
        ans += tr[k][ans%M];
        return;
    }
    const int mid = (l+r)>>1;
    if (x <= mid) query(k<<1, l, mid, x, y);
    if (y > mid) query(k<<1|1, mid+1, r, x, y);
}

int n, q, x, y;
char op;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> val[i];
    build(1, 1, n);
    cin >> q;
    while (q--) {
        cin >> op >> x >> y;
        if (op == 'C') {
            val[x] = y;
            update(1, 1, n, x);
        } else {
            ans = 0;
            query(1, 1, n, x, y-1);
            cout << ans << '\n';
        }
    }
    return 0;
}