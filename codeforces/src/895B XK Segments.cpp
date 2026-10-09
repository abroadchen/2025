//
// Created by Psy.C on 2026/10/9.
//
/**
统计满足 a[i] / x == k（或某种整除商条件）的数对/元素个数。代码把每个元素映射到一个“区间”，再二分统计落在区间里的元素个数
先算 p：
若 a[i] % x == 0，p = a[i]；
否则 p = (a[i]/x + 1)*x，即 a[i] 向上取整到 x 的倍数。
即 p = ceil(a[i]/x)·x（a[i] 向上取整到最近的 x 的倍数）。注意整除时 p=a[i] 本身也是 x 倍数，两者一致——其实统一就是 p = ((a[i]+x-1)/x)*x，这里拆开写因为 x 很大时空安全考虑
从 p 出发，构造区间 [l, r) = [p+(k-1)x, p+kx)，长度为 x。
当 k==0 时把左端点改为 a[i]（特殊处理商为 0 的边界）。
用 lower_bound 统计数组中值在 [l, r) 内的元素个数，累加到 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e6;

int a[N+5], ans;
signed main() {
    fast;
    int n, x, k; cin >> n >> x >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    for (int i = 1; i <= n; ++i) {
        int p = a[i]%x;
        if (p == 0) p = a[i]; else p = (a[i]/x+1)*x;
        int l = p+(k-1)*x, r = p+k*x;
        if (k == 0) l = a[i];
        ans += lower_bound(a+1, a+n+1, r) - lower_bound(a+1, a+n+1, l);
    }
    cout << ans << '\n';
    return 0;
}