//
// Created by Psy.C on 2026/2/23.
//
/**
val / llabs(val) 返回 sign(val)：
如果 val > 0：返回 1
如果 val < 0：返回 -1
如果 val = 0：未定义（除零错误）

对于直线 ax + by + c = 0
将点(x,y)代入得到 ax + by + c
如果结果 > 0：点在直线一侧
如果结果 < 0：点在直线另一侧
如果结果 = 0：点在直线上

时间复杂度：O(n)，其中n是直线数量 空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

inline ll get(ll a, ll b, ll c, ll x, ll y) {
    ll val = x * a + y * b + c;
    return val / llabs(val);
}

ll x1, y11, x2, y2, n;
int main() {
    fast;
    cin >> x1 >> y11 >> x2 >> y2 >> n;
    int cnt = 0;
    for (ll i = 0, a, b, c; i < n; ++i) {
        cin >> a >> b >> c;
        if (get(a, b, c, x1, y11) * get(a, b, c, x2, y2) < 0)
            cnt++;
    }
    cout << cnt << '\n';
    return 0;
}