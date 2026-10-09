//
// Created by Psy.C on 2026/10/9.
//
/**
读入棋盘行数
n
n、列数
m
m、以及每个
2
×
2
2×2 子矩阵的乘积要求
k
k（与本位置
a
[
i
]
[
j
]
a[i][j] 是
±
1
±1 相关，k 取 1 或 -1）
当
k
=
−
1
k=−1 且
n
n、
m
m 奇偶性不同时，无解，输出 0。
直觉（组合恒等式）：把所有
2
×
2
2×2 子矩阵的乘积再乘起来，每个棋盘格会被算入
k
k 次贡献……当
n
,
m
n,m 奇偶不同且
k
=
−
1
k=−1 时出现矛盾 → 0
否则方案数 =
2
(
n
−
1
)
(
m
−
1
)
2
(n−1)(m−1)
 。代码用两次快速幂求出
2
(
n
−
1
)
(
m
−
1
)
2
(n−1)(m−1)
 。
含义：前
(
n
−
1
)
×
(
m
−
1
)
(n−1)×(m−1) 个格子可自由设为
±
1
±1（各 2 种选择），其余（最右一行 + 最下一行）被唯一确定以满足所有
2
×
2
2×2 乘积条件
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int mod = 1e9+7;

int ksm(int a, int b) {
    int res = 1; a %= mod;
    assert(b >= 0);
    for (; b; b>>=1) {
        if (b&1) res = res*a % mod;
        a = a*a % mod;
    }
    return res;
}

signed main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    if (k == -1 && (n&1) != (m&1)) cout << "0\n";
    else cout << ksm(ksm(2,n-1), m-1) << '\n';
    return 0;
}