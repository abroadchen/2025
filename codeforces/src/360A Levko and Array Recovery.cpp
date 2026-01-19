//
// Created by Psy.C on 2026/1/19.
//
///O(m×n)，其中m是操作数，n是数组长度。对于大规模数据可能会超时
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define inf 1e9
#define rep(i,n) for (int i=0;i<n;++i)
using namespace std;

struct node { int op, l, r, w; } a[N];

int main() {
    fast;
    int n, m, num[N]; cin >> n >> m;
    rep(i,m) cin >> a[i].op >> a[i].l >> a[i].r >> a[i].w;
    rep(i,n+1) num[i] = inf;
    for (int i = m - 1; i >= 0; --i) {//反向处理操作
        if (a[i].op == 1) {
            for (int j = a[i].l; j <= a[i].r; ++j) {
                if (num[j] - a[i].w <= inf) num[j] -= a[i].w;
            }
        } else {
            for (int j = a[i].l; j <= a[i].r; ++j) {
                if (num[j] > a[i].w) num[j] = a[i].w;
            }
        }
    }
    int ans[N], flag = 0;
    for (int i = 1; i <= n; ++i) ans[i] = num[i];
    rep(i,m) {//正向执行操作验证结果
        if (a[i].op == 1) {
            for (int j = a[i].l; j <= a[i].r; ++j) num[j] += a[i].w;
        } else {
            int mx = -inf;
            for (int j = a[i].l; j <= a[i].r; ++j)
                mx = max(mx, num[j]);
            if (mx != a[i].w) { flag = 1; break; }
        }
    }
    if (flag) cout << "NO\n"; else {//验证失败
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
        cout << '\n';
    }
    return 0;
}