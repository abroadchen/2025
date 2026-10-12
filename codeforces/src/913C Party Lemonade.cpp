//
// Created by Psy.C on 2026/10/12.
//
/**
拆 L 为二进制位：把 l 一位位拆开存入 x[]（x[0] 是 LSB）。len = 二进制位数。
输入并做"前缀最小单价"：c[i] = min(c[i], c[i-1]<<1)。
c[i-1]<<1 表示"用两个（更短的）规格 i-1 去凑一个规格 i 的代价 2*c[i-1]"。
取 min，即：如果直接买规格 i 比"买两个规格 i-1"更贵，就更新成后者。这保证从低到高，c[i] 始终是"凑出长度 2^i 的最小代价"。
补充更长规格：对于 i ≥ n 的位（超出输入种类），c[i] = c[i-1]<<1——没有直接单价，只能由更短的加倍来替代
遍历所有需要用到的位（到 max(n,len) 为止）：
ans = min(ans, c[i])：关键贪心——始终维护"用单价 c[i] 就可以凑出 ≥ 2^i 的长度"，即如果仅买一个规格 i 就已经超过/达到所需，用更小的当前答案来兜底（因为长度可以超出 L）。
若 x[i] == 1（L 的该二进制位为 1），ans += c[i]——选上这一位。
因为后缀位（更高位）可能在某轮更新 ans，且 ans 是"买够至少 L"的最小值，所以 min 兜底保证了允许"买得比 L 略多"也能算出更优解
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 35;

int n, l, x[N], len, c[N], ans;
signed main() {
    fast;
    cin >> n >> l;
    while (l) { x[len++] = l&1; l >>= 1; }
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        if (i) c[i] = min(c[i], c[i-1]<<1);
    }
    for (int i = n; i < len; ++i) c[i] = c[i-1]<<1;
    for (int i = 0; i < max(n, len); ++i) {
        ans = min(ans, c[i]);
        if (x[i]) ans += c[i];
    }
    cout << ans << '\n';
    return 0;
}