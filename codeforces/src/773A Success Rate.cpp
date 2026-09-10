//
// Created by Psy.C on 2026/9/9.
//
/**
mid*a - p >= 0 → 即 mid*a >= p。直观含义：当"第一项速率 a"作用 mid 步后至少覆盖 p。
mid*b - q >= mid*a - p → 即 mid*b - q >= mid*a - p，整理得 mid*(b-a) >= q - p。含义是"第二项速率 b"在作用 mid 步（并扣除初始 q 偏移）后，要不少于第一项在 mid 步后的结果
也就是要求 mid*a - p ≥ 0 且 mid*b - q 不小于它。可以改写为一个统一区间条件：max(mid*a - p, 0) <= mid*b - q
l = 0, r = inf：二分区间 [0, inf]。
while (l < r)：经典二分模板。
mid = (l+r)/2。
若 check(mid) 为真（mid 可行），说明答案 ≤ mid，收窄右界 r = mid。
否则（mid 不可行），说明需要更大的 mid，l = mid + 1。
循环结束时 l 是最小的满足 check 的 mid。
最后输出：
若 l >= inf（即上界都不可行 → 无解），输出 -1；
否则输出 l*b - q，即把找到的最小可行 mid 代入 mid*b - q 得到最终答案值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int inf = 0x7fffffff;
ll a, b, p, q;
bool check(ll mid) {
    return mid*b - q >= mid*a - p && mid*a - p >= 0;
}

int main() {
    fast;
    int t; cin >> t;
    while (t--) {
        cin >> p >> q >> a >> b;
        ll l = 0, r = inf;
        while (l < r) {
            ll mid = (l+r)/2;
            if (check(mid)) r = mid;
            else l = mid + 1;
        }
        cout << (l >= inf ? -1 : l*b-q) << '\n';
    }
    return 0;
}