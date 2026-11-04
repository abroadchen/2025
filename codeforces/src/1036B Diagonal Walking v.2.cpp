//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
交换 n 和 m，保证 n <= m，后续判断都以较大值为基准
如果较大的 m 已经大于 k，说明无法满足条件，直接输出 -1 并结束本轮
(m - n) 为奇数	k--	k 减 1，翻转奇偶性
(m - n) 为偶数 但 (k - m) 为奇数	k -= 2	k 减 2，保持奇偶性不变（差 2 仍是同奇偶）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll t, n, m, k;
int main() {
    fast;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        if (n > m) swap(n, m);
        if (m > k) { cout << "-1\n"; continue; }
        if ((m-n)&1) k--;
        else if ((k-m)&1) k -= 2;
        cout << k << '\n';
    }
    return 0;
}