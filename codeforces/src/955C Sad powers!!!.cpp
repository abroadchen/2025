//
// Created by Psy.C on 2026/10/19.
//
/***
对 x 求 整数平方根 floor(sqrt(x))（值域内二分）。

ans 记录当前已知满足 m*m <= x 的最大 m；
找到 floor(sqrt(x))。
等价于 (ll)sqrt(x)，但用整数二分避免浮点误差
f(n) = [1, n] 内「非平方的完美幂」个数。

它由两部分组成：

upper_bound(o, n)：o 中 ≤n 的个数。o 存的是指数 ≥3 的非平方完美幂（后面 init 里构造）。
get(n)：floor(sqrt(n))，即 [1,n] 内平方数的个数。
为什么这么加？

完美幂 = 平方数（指数2）∪ 指数≥3 的幂。
题目要求「完美幂但不是平方数」。
指数≥3 且非平方的 → 存进 o（第一项）。
但o也包含了指数≥4、≥6 等的数。指数≥4 的数同时也是平方数（如 2^4=16 也是 4^2），init 里排除了（if (r*r==x) continue）

第一层循环：底数 i 从 2 到 1e6。

为什么到 1e6？因为 i^3 <= 1e18 ⇒ i <= 1e6（(1e6)^3 = 1e18）。超过 1e6 的底数其立方就超上界，无需考虑。
第二层循环：从 cur = i*i*i（指数从 3 开始，跳过平方）开始，不断乘 i（指数逐级增高：i³, i⁴, i⁵, …），直到超过 U = 1e18。

v 收集所有指数 ≥3 的完美幂。
if (cur > U/i) break; 防止 cur*i 溢出 long long（提前判断）
排序 + 去重（不同底数可能产生相同值，如 2^6=64=8^2、4^3=64）。
关键筛选：对每个 v 中的数 x，get(x)=floor(sqrt(x))，若 r*r == x（即 x 是完全平方数）→ continue 跳过；否则（非平方）push 进 o。

为什么排除平方数：题目要求「不是平方数的完美幂」。像 16 = 2^4 = 4^2，既是立方类幂（指数4≥3）又是平方数，这种要在答案里排除（因为它属于平方数那部分，会被 get(n) 计一次）。

这样 o 中的数都是「指数≥3 且本身不是平方数」的完美幂，与「平方数」集合互不相交。所以 f(n) = |o 中 ≤n| + |平方数 ≤n| 就是答案，无重复
solve(l,r) = f(r) - f(l-1)：前缀和差分求区间 [l,r] 内的答案。
init()：程序开始时一次性构造好 v 和 o 集合。
读入 t 组询问，每组输出 [l,r] 内「非平方完美幂」的个数

复杂度：init 构造 O(1e6 × 摊还)，每次询问 O(log|o|)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll get(ll x) {
    ll ans = 0, l = 1, r = 1e9;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (m*m <= x) { ans = m; l = m+1; }
        else r = m-1;
    }
    return ans;
}

vector<ll> o;
ll f(ll n) {
    int ans = upper_bound(o.begin(), o.end(), n) - o.begin();
    return ans + get(n);
}

vector<ll> v;
void init() {
    ll U = 1e18;
    for (ll i = 2; i <= 1000000; ++i) {
        for (ll cur = i*i*i; cur <= U; cur *= i) {
            v.push_back(cur);
            if (cur > U/i) break;
        }
    }
    ranges::sort(v);
    v.erase(ranges::unique(v).begin(), v.end());
    for (ll &x : v) {
        ll r = get(x);
        if (r*r == x) continue;
        o.push_back(x);
    }
}
ll solve(ll l, ll r) { return f(r)-f(l-1); }

int main() {
    fast;
    init();
    int t; cin >> t;
    while (t--) {
        ll l, r; cin >> l >> r;
        cout << solve(l, r) << '\n';
    }
    return 0;
}