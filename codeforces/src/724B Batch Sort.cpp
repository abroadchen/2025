//
// Created by Psy.C on 2026/4/24.
//
/**
对每行进行检查
统计每行中不等于其列号的元素个数(ans)
如果某行中有恰好1个或至少3个元素不等于其列号，则返回false
只有当每行都恰好有0个或2个元素不等于其列号时才返回true

如果原始矩阵就满足条件，直接输出"YES"
遍历所有可能的列对(i,j)
交换这两列的所有元素
检查交换后的矩阵是否满足条件
如果满足则输出"YES"
立即恢复原来的列顺序（再次交换）
O(n×m²×n) = O(n²m²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, m, a[30][30];
bool check() {
    ll ans = 0;
    for (ll i = 1; i <= n; ++i) {
        ans = 0;
        for (ll j = 1; j <= m; ++j)
            if (a[i][j] != j) ans++;
        if (ans == 1 || ans >= 3) return false;
    }
    return true;
}

int main() {
    fast;
    cin >> n >> m;
    for (ll i = 1; i <= n; ++i)
        for (ll j = 1; j <= m; ++j) cin >> a[i][j];
    if (check() == true) {
        cout << "YES\n";
        return 0;
    }
    for (ll i = 1; i <= m+1; ++i)
        for (ll j = i+1; j <= m; ++j) {
            for (ll k = 1; k <= n; ++k) swap(a[k][i], a[k][j]);
            if (check() == true) {
                cout << "YES\n";
                return 0;
            }
            for (ll k = 1; k <= n; ++k) swap(a[k][i], a[k][j]);
        }
    cout << "NO\n";
    return 0;
}