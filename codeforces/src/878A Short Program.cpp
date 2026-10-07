//
// Created by Psy.C on 2026/10/6.
//
/**
x = 1023 = 全 1（10 位）
y = 0 = 全 0。
这两个是"探针"：分别代表全 1 和全 0 的 10 位输入
对全1探针 x 和全0探针 y 施加同样的完整操作序列。
操作数 m 是 0-1023 的 10 位整数。
执行完，x = 全1输入经过整个序列的结果，y = 全0输入经过整个序列的结果
(1,1) → an=1,o=1 → (b&1)^0|1 = 1 恒1 ✓
(1,0) → an=1 → (b&1)^0|0 = b 恒等 ✓
(0,1) → an=1,xo=1 → (b&1)^1|0 = ¬b 取反 ✓
(0,0) → 0 → 恒0 ✓
输出 3（3 个操作），然后依次 & an、^ xo、| o。这三个掩码拼起来就是对任意输入与原序列等价的 3 个操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int x = 1023, y, an, o, xo;
int main() {
    fast;
    int n; cin >> n;
    while (n--) {
        char a; int m; cin >> a >> m;
        if (a == '&') x &= m, y &= m;
        if (a == '|') x |= m, y |= m;
        if (a == '^') x ^= m, y ^= m;
    }
    int res = 1, u, v;
    for (int i = 0; i < 10; ++i) {
        u = x&1, v = y&1;
        if (u == 1) {
            if (v == 1) { an += res; xo += 0; o += res; }
            else { an += res; xo += 0; o += 0; }
        } else {
            if (v == 1) { an += res; xo += res; o += 0; }
            else { an += 0; xo += 0; o += 0; }
        }
        x >>= 1, y >>= 1;
        res <<= 1;
    }
    cout << "3\n& " << an << "\n^ " << xo << "\n| " << o << '\n';
    return 0;
}