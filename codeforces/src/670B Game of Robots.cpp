//
// Created by Psy.C on 2026/4/12.
//
/**
第1组：1个元素
第2组：2个元素
第3组：3个元素
...
第i组：i个元素

i = 1: 检查第k个元素是否在第1层
第1层有1个元素（第1个元素）
如果k ≤ 1，说明目标就在第1层，退出
否则，说明不在第1层，从k中减去第1层的元素数：k = k - 1
i = 2: 检查第k个元素是否在第2层
第2层有2个元素（第2,3个元素）
如果k ≤ 2，说明目标就在第2层，退出
否则，说明不在第2层，从k中减去第2层的元素数：k = k - 2
i = 3: 检查第k个元素是否在第3层
第3层有3个元素（第4,5,6个元素）
如果k ≤ 3，说明目标就在第3层，退出
否则，说明不在第3层，从k中减去第3层的元素数：k = k - 3
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, k, a[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (k <= i) break;
        k = k - i;
    }
    cout << a[k] << '\n';
    return 0;
}