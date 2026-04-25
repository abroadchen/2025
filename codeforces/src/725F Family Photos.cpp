//
// Created by Psy.C on 2026/4/25.
//
/**
排序: O(m log m)
遍历: O(n + m)
总体: O(n log n)，其中n是输入规模
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+7;

struct node {
    int x, y;
    bool operator<(const node &o) const {
        return x + y > o.x + o.y;
    }
} a[N], b[N], c[N];

int n, m, ans;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x >> a[i].y >> b[i].x >> b[i].y;
        if (a[i].x + a[i].y > b[i].x + b[i].y)
            c[++m] = a[i], c[++m] = b[i];
        else {
            if (a[i].x - b[i].y > 0) ans += a[i].x - b[i].y;
            else if (a[i].y - b[i].x > 0)
                ans += b[i].x - a[i].y;
        }
    }
    sort(c + 1, c + m + 1);
    for (int i = 1; i <= m; ++i) {
        if (i&1) ans += c[i].x;
        else ans -= c[i].y;
    }
    cout << ans;
    return 0;
}