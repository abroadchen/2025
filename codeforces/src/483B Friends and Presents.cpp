//
// Created by Psy.C on 2026/2/17.
//
/**
mid - mid/x >= c1：

mid/x: 在mid个物品中有多少个是x的倍数
mid - mid/x: 剩余不是x倍数的物品数量
这个数量要≥c1
mid - mid/y >= c2：

mid/y: 在mid个物品中有多少个是y的倍数
mid - mid/y: 剩余不是y倍数的物品数量
这个数量要≥c2
mid - mid/x/y >= c1 + c2：

mid/x/y: 在mid个物品中有多少个既是x倍数又是y倍数（即xy的倍数）
mid - mid/x/y: 剩余不是xy倍数的物品数量
这个数量要≥c1+c2

时间复杂度：O(log(inf)) ≈ O(34)
空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr ll inf = 10000000000;
int c1, c2, x, y;

int main() {
    fast;
    cin >> c1 >> c2 >> x >> y;
    ll l = 1, r = inf, mid = 0;
    while (l < r) {
        mid = (l + r)>>1;
        if (mid - mid/x >= c1 && mid - mid/y >= c2 &&
            mid - mid/x/y >= c1 + c2) r = mid;
        else l = mid + 1;
    }
    cout << l << '\n';
    return 0;
}