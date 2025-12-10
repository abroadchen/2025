//
// Created by Psy.C on 2025/12/10.
//
/*
 *O(m+n)：读取边O(m) + 计算度数O(n)
 *
 *1ll * n * (n - 1) * (n - 2) / 6: 计算C(n,3)
 *C(n,3) = n!/(3!(n-3)!) = n×(n-1)×(n-2)/6
*与节点i相连的节点数：d[i]
与节点i不相连的节点数：(n-1-d[i])
通过节点i但不存在的三角形数：d[i] × (n-1-d[i])
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000100
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    int d[N] = {};
    ll t = 0;
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        d[x]++, d[y]++;
    }
    for (int i = 1; i <= n; ++i) t += 1ll * d[i] * (n - 1 - d[i]);
    ll ans = 1ll * n * (n - 1) / 2;
    ans = ans * (n - 2) / 3;
    cout << ans - t / 2 << '\n';
    return 0;
}