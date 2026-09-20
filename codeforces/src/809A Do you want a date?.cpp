//
// Created by Psy.C on 2026/9/20.
//
/**
b[k] = 2^k mod 1e9+7，即"从 k 个元素中任意选若干（每种子集）的数量 = 2^k"。
用于后续统计"以 a[i] 为最大/最小的子集个数"
升序排序是关键：排序后，a[i] 前面的元素都比它小（当它是最小值的候选），后面的都比它大（当它是最大值的候选）。这样"子集个数"就能用下标算出来
(1) b[i-1] = 2^(i-1)：以 a[i] 作为最大值的子集数。因为排序后，a[i] 是子集里最大的，剩下的任意取自它前面的 i-1 个更小元素，共 2^(i-1) 种。

(2) b[n-i] = 2^(n-i)：以 a[i] 作为最小值的子集数。因为 a[i] 是子集里最小的，剩下的任意取自它后面的 n-i 个更大元素，共 2^(n-i) 种。

(b[i-1] - b[n-i]) * a[i]：a[i] 在所有子极差和中贡献的净量 =

作为最大值的次数 2^(i-1) 加上 a[i]
减去作为最小值的次数 2^(n-i) 减去 a[i]
合并即 (2^(i-1) - 2^(n-i)) * a[i]。

把每个元素的净贡献累加，注意 b[i-1] - b[n-i] 可能为负，取模时按 C++ 负数取模会得负数，但最终在多轮加法后取模通常没问题（若担心可加 mod）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5, mod = 1e9+7;
ll a[N], b[N];
int main() {
    fast;
    int n;
    while (cin >> n) {
        b[0] = 1;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            b[i] = (2*b[i-1])%mod;
        }
        sort(a+1, a+n+1);
        ll ans = 0;
        for (int i = 1; i <= n; ++i)
            ans = (ans + (b[i-1] - b[n-i])*a[i]) % mod;
        cout << ans << '\n';
    }
    return 0;
}