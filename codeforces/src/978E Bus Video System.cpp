//
// Created by Psy.C on 2026/10/22.
//
/**
读入 n（操作数）和 w（水箱容量上限）。
逐个读入 a[i]，维护累计前缀和 sum。
记录前缀和的最大值 mx 和最小值 mn。
初始 sum=0 时即以 0 起步统计：mn 初始为 0，mx 初始为 0
设初始水量为 x。过程中的每个前缀 t，实际水量 = x + t，必须满足 0 ≤ x + t ≤ w，即对于所有前缀 t：
下限约束：x + mn ≥ 0  →  x ≥ -mn
上限约束：x + mx ≤ w  →  x ≤ w - mx
所以合法 x 的范围是 [-mn, w - mx]，x 取整数。
取值个数 = (w - mx) - (-mn) + 1 = w - mx + mn + 1。
若该值 ≤ 0（下界 > 上界）则无解，输出 0（用 max(..., 0) 保护）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, w, a, mx, mn, sum;
int main() {
    fast;
    cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        cin >> a; sum += a;
        mx = max(mx, sum); mn = min(mn, sum);
    }
    cout << max(w-mx+mn+1, 0ll);
    return 0;
}