//
// Created by Psy.C on 2026/10/2.
//
/**
n = 数组长度，x = 目标异或和
当 n==2 且 x==0 时：两个正整数异或为 0 要求两数相等，而题目（通常）要求互不相同 / 或非零限制，导致无解 → 输出 NO
n==1

数组 [x]，异或和 = x。✅
n==2

数组 [0, x]，异或和 = 0^x = x。✅
使用 0 是允许的（该题允许 0）。
n>=3

先输出 1,2,...,n-3 共 n-3 个数，记它们异或和为 p。
还差 3 个位置，要让总异或 = x。已有部分异或 p，剩下 3 个数异或应 = p ^ x。
用 2^18、2^19 和第三个数构造：
若 p == x：第三个数取 (2^18)^(2^19)，则 (2^18)^(2^19)^[(2^18)^(2^19)] = 0，总异或 = p = x。✅
否则（p≠x）：用 0, 2^19, (2^19)^p^x 三个数，其异或 = 0 ^ 2^19 ^ (2^19^p^x) = p^x，总异或 = p ^ (p^x) = x。✅
这里用 2^18、2^19 这种大数是为了避免前 n-3 个数（1..n-3，都较小）与新补的数冲突/重复（保证互不相同的合法构造）。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;


signed main() {
    fast;
    int n, x; cin >> n >> x;
    if (n == 2 && !x) cout << "NO\n";
    else {
        cout << "YES\n";
        if (n == 1) cout << x << '\n';
        if (n == 2) cout << "0 " << x << '\n';
        if (n >= 3) {
            int p = 0;
            for (int i = 1; i <= n-3; ++i) {
                cout << i << ' ';
                p ^= i;
            }
            if (p == x) cout << (1ll<<18) << ' ' << (1ll<<19) << ' ' << ((1ll<<18)^(1ll<<19)) << '\n';
            else cout << "0 " << (1ll<<19) << ' ' << ((1ll<<19)^p^x) << '\n';
        }
    }
    return 0;
}