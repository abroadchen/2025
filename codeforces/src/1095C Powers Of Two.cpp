//
// Created by Psy.C on 2026/11/18.
//

/**
真正学会的起点..
每一项 ≥ 1（最小是 2⁰ = 1），k 项之和至少是 k，所以若 n < k 必然无解
num[i] = 二进制第 i 位是 0 还是 1（即 2^i 这一项出现几次，初始为 0 或 1）。
tot = n 中 1 的个数 = 能达到的最少项数
最少项数是 tot（二进制分解，不能拆得更少），若 k < tot，无法达到，无解
现在还需要增加 k - tot 项。
每次循环：把一个 2 的幂拆成两个 2^{i-1}（即 2^i → 2^{i-1} + 2^{i-1}），这样项数 +1，数值不变。
while (num[len]==0) len--：从最高位往下找第一个非零位去拆。
循环做 k-tot 次，正好达到 k 项。
对每一位 i，输出 num[i] 个 2^i，即按方案输出 k 个 2 的幂
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

int n, k, num[N], len(-1), tot;
int main() {
    fast;
    cin >> n >> k;
    if (n < k) { cout << "NO\n"; return 0; }
    while (n) { num[++len] = n&1; tot += num[len]; n >>= 1; }
    if (k < tot) { cout << "NO\n"; return 0; }
    k -= tot;
    while (k--) {
        while (num[len] == 0) len--;//找最高非零位
        num[len]--; num[len-1] += 2;//该位出现次数 -1 拆成两个更小的 2 的幂
    }
    cout << "YES\n";
    for (int i = 0; i <= len; i++)
        for (int j = 1; j <= num[i]; j++) cout << (1<<i) << ' ';
    return 0;
}