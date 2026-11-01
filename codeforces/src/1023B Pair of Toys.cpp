//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
要找 1 ≤ a < b ≤ n，且 a + b = k。
从大到小看，b 的最大取值：既不能超过 n，也不能让 a 小于 1，即 b ≤ k-1。所以 r = min(k-1, n) 是 b 的最大值。
对于给定的 b，a = k - b。要求 a ≥ 1 且 a < b（即 a ≤ b-1）。
进一步，a = k-b 要满足 a ≥ 1，即 b ≤ k-1。
而 a < b 等价于 k - b < b，即 b > k/2，所以最小的 b 是 k - r 取整相关。这里 l = max(1, k-r) 给出了 b 的下界（实际是让 a 不重复计数的下界）。
实际上这行等价于确定区间 [l, r]，其中每个合法的 b 对应一个合法的 a = k - b ∈ [1, l)
如果下界 l ≥ r，说明区间为空，不存在满足条件的数对，输出 0
区间 [l, r] 里的整数值 b 每一个都对应一个合法 a，理论上数对数量是 (r-l+1)。
但由于要求 a < b（不重复、有顺序），真正的对数要除以 2 取整：即满足 a + b = k 的有序正整数解中，a ≤ n, b ≤ n 且 a ≠ b 的组合数的一半。
(r-l+1)/2 整数除法起到向下取整的作用，保证统计的是"数对"而非"排列"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k;
int main() {
    fast;
    while (cin >> n >> k) {
        ll r = min(k-1, n), l = max(1ll, k-r);
        if (l >= r) { cout << "0\n"; return 0; }
        cout << (r-l+1)/2 << '\n';
    }
    return 0;
}