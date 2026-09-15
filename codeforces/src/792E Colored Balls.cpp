//
// Created by Psy.C on 2026/9/15.
//
/**
对某个候选值 x：

对每个 a[i]，计算 p = a[i]/x（商）、q = a[i]%x（余数）。
可行性条件：p >= q，即商不小于余数。
若 p == 0（即 a[i] < x，商为0），则该值不可行，直接返回放弃 x。
若可行，则操作次数贡献 (a[i]+x)/(x+1)（即 ceil(a[i]/(x+1))）。
全部可行则用 s 更新全局最优 ans。
换句话说：get(x) 在判断"用基准 x 拆分所有数"是否可行，可行则算出总操作数，并刷新最小值

最优答案只依赖最小元素 a[0] 的候选 x。因为可行性条件 p = a[i]/x >= q，当 a[0] 都被拆分成功，其他更大的 a[i] 通常更容易满足。

而所有可能的候选 x 都落在 a[0] 的"整除分块"里：

枚举 i，a[0]/i 和 a[0]/i+1 覆盖了接近整除的整数值；
i 本身和 a[0]/i-1 覆盖另一类候选。
因为取整分块保证了：所有"可能成为最优的 x"必然出现在离某些 a[0]/i 上下附近的位置（±1），所以只需在这些候选点调用 get，而不必枚举 1..a[0] 全部值（分块把复杂度降到 O(√a[0]) 个候选）。

这就是经典的数论分块（整除分块）枚举，靠 i*i <= a[0] 限定了枚举上界
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 510;
constexpr ll inf = 0x7fffffffffffffff;

int n;
ll a[N], ans(inf);
void get(ll x) {
    ll s = 0;
    if (x == 0) return;
    for (int i = 0; i < n; ++i) {
        ll p = a[i]/x, q = a[i]%x;
        if (p == 0) return;
        if (p >= q) s += (a[i]+x)/(x+1);
        else return;
    }
    ans = min(ans, s);
}

int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    for (int i = 1; i*i <= a[0]; ++i) {
        get(a[0]/i); get(a[0]/i+1);
        get(i); get(a[0]/i-1);
    }
    cout << ans << '\n';
    return 0;
}