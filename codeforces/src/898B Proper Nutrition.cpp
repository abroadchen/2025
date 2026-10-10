//
// Created by Psy.C on 2026/10/10.
//
/**
i 从 0 枚举到 n/a（因为 i*a 不可能超过 n，即 i <= n/a）
对每个 i，检查剩下部分 n - i*a 能否被 b 整除：
若 (n-i*a) % b == 0，则 j = (n-i*a)/b 是整数，且因为 i<=n/a 保证 n-i*a >= 0，所以 j >= 0，找到一组非负整数解
输出 YES、这组 i 和 j，并立即返回
若循环结束都没找到，输出 NO
方程 a*i + b*j = n，i, j >= 0 有非负整数解当且仅当存在某个 i ∈ [0, n/a] 使 n - a*i 是 b 的倍数。
枚举法因为 i 的上限是 n/a，所以一定能覆盖所有可能的 i，算法正确性有保证
for (i = 0; i <= n/a; ++i)，循环 O(n/a) 次，每次 O(1) 判断。若 a 较小则可能接近 O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, a, b; cin >> n >> a >> b;
    for (int i = 0; i <= n/a; ++i) {
        if ((n-i*a)%b == 0) {
            cout << "YES\n";
            cout << i << ' ' << (n-i*a)/b << '\n';
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}