//
// Created by Psy.C on 2026/1/21.
//
/**
* 均匀分配策略：将数值 y 分配到前 k 个容器中
前 y%k 个容器分配 (y/k + 1) 个单位
后 k - (y%k) 个容器分配 y/k 个单位
这样确保总数为 y，且分配尽可能均匀
 *更新剩余值：x -= y（实际剩余待分配的值），n -= k（剩余容器数量）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k, l, r, x, y;
    cin >> n >> k >> l >> r >> x >> y;
    for (int i = 1; i <= y % k; ++i) cout << y / k + 1 << ' ';
    for (int i = y % k + 1; i <= k; ++i) cout << y / k << ' ';
    x -= y; n -= k;
    if (n == 0) return 0;
    for (int i = 1; i <= x % n; ++i) cout << x / n + 1 << ' ';
    for (int i = x % n + 1; i <= n; ++i) cout << x / n << ' ';
    return 0;
}