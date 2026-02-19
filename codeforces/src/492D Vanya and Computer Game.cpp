//
// Created by Psy.C on 2026/2/19.
//
/**
对于每个查询 k，找出生产 k 个物品所需的最短时间
确定最后一个是哪个人生产的

在时间 mid 内，Vova 能生产 mid/x 个物品
在时间 mid 内，Vanya 能生产 mid/y 个物品
总共能生产 mid/x + mid/y 个物品
我们要找最小的 mid 使得 mid/x + mid/y >= k

时间复杂度：O(n log(max_time))，其中n是查询次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll t=1;
void get() { t <<= 50; }//2^50

ll n, x, y;
int main() {
    fast; get();
    cin >> n >> x >> y;
    for (ll i = 0, k; i < n; ++i) {
        cin >> k;
        ll ans = 0, l = 0, r = t;
        while (l <= r) {
            if (const ll mid = (l + r) >> 1; mid/x + mid/y >= k) {
                ans = mid;//满足条件的时间
                r = mid - 1;//尝试找更小的时间
            } else l = mid + 1;
        }
        if (ans%x == 0 && ans%y == 0) cout << "Both\n";//同时完成
        else if (ans%x == 0) cout << "Vova\n";//每 x 分钟生产一个物品
        else if (ans%y == 0) cout << "Vanya\n";//每 y 分钟生产一个物品
    }
    return 0;
}