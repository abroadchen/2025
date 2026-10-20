//
// Created by Psy.C on 2026/10/20.
//
/**
i 从 1 开始，每次乘以 2（i = 1, 2, 4, 8, ...），即 i 依次取 2 的幂（二进制位权）‍。
对每个 i 累加 i*(x/2)。
最终输出 ans

for (ll i = 1; i <= n; i *= 2ll)

遍历所有 ≤ n 的 2 的幂：1、2、4、8、16、…
这里的 i 代表一个二进制位的位权（即第 k 位，k = log2(i)）。
2. ll x = ceil((double)n/i);

计算 n / i 并向上取整，得到 x = ceil(n/i)。
它的意义：1..n 中，第 k 位（位权 i）上"会参与计数"的数的个数区间的边界。
实际上 ceil(n/i) 表示：从 1 到 n，二进制第 k 位为 1 的数的个数，与"按位翻转周期"有关。
3. ans += i*(x/2);

x/2：ceil(n/i) 整除 2，表示在"每 2i 个连续数形成一个完整周期"中，第 k 位为 1 的那一段的次数（即周期数）。
i * (x/2)：每个周期里第 k 位为 1 的连续个数就是 i 个，乘以周期数得到总数中"第 k 位为 1 的数的个数 × 位权"。
累加到 ans。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, ans;
int main() {
    fast;
    cin >> n;
    for (ll i = 1; i <= n; i *= 2ll) {
        ll x = ceil((double)n/i);
        ans += i*(x/2);
    }
    cout << ans;
    return 0;
}