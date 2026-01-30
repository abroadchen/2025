//
// Created by Psy.C on 2026/1/30.
//
/**
* ceil(n/r)：向上取整，计算n/r的上界
(n/r)：表示需要的最小份数（向下取整）
最小份数×最小每份大小
 *
*(n/l)：向下取整，计算最大可能的份数
(n/l)*r：最大份数×最大每份大小
含义：验证n是否不超过最大可能的总量
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll q, n, l, r; cin >> q;
    while (q--) {
        cin >> n >> l >> r;
        if (n < l) {
            cout << "No\n";
            continue;
        }
        if (n >= static_cast<ll>(ceil(n/r))*l && n <= (n/l)*r) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}