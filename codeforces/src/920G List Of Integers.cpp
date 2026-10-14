//
// Created by Psy.C on 2026/10/14.
//
/**
v 存 p 的不同质因数。
对 p 的每个质因子子集，now = 子集质因子乘积，flg 用于奇偶加减号（奇数个因子减、偶数个加）。
x/now 是 1..x 中能被 now 整除的个数。
容斥求和：
get
(
x
)
=
∑
S
⊆
v
(
−
1
)
∣
S
∣
⌊
x
∏
i
∈
S
v
i
⌋
get(x)=∑
S⊆v
​
 (−1)
∣S∣
 ⌊
∏
i∈S
​
 v
i
​

x
​
 ⌋

这正是 1..x 中不被任何 p 的质因子整除（即与 p 互质）的数的个数

第 1 步——质因数分解：

用试除法把 p 分解成不同质因子，存入 v。
循环结束后若 p>1，说明还有一个大质因子，加入 v。
第 2 步——关键变换：

get(x) = 1..x 中与 p 互质的个数。
k += get(x)：把"前 k 个比 x 大的互质数"转成"第 k 个互质数出现在全局位置"。
记全局互质数列（按大小排）：
a
1
,
a
2
,
…
a
1
​
 ,a
2
​
 ,…（与 p 互质）。
要求 a 中大于 x 的第 k 个。1..x 里已有 get(x) 个互质数，所以我们要找的是全局第 get(x)+k 个互质数，即把 k 累加上 get(x)。
第 3 步——二分：

get(mid) 单调不减，用二分找最小 mid 使得 get(mid) >= k（全局第 k 个互质数）。
因为 k 已经加上 get(x)，所以二分出来的 mid > x（自动保证了"大于 x"），答案就是那个位置的值。
r 设 1e12 保证足够覆盖（第 k 个互质数不会那么大，k ≤ 1e9 时实际答案远小于 1e12）

要点	说明
容斥	枚举 p 的质因子子集（p 质因子数量少，2^num 小），求互质计数
质因数分解	试除法 O(√p)
二分	O(log 范围) ≈ log(1e12) ≈ 40 次，每次 get 是 O(2^num)
总复杂度	每组 O(√p + log(1e12)·2^num)，num = p 的不同质因子数，很小
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

vector<ll> v;
ll get(ll x) {
    ll ans = 0;
    int num = v.size();
    for (int i = 0; i < 1<<num; ++i) {
        ll now = 1, flg = 1;
        for (int j = 0; j < num; ++j) {
            if ((i>>j)&1) {//选中该质因子
                now *= v[j]; flg *= -1;
            }
        }
        ans += flg*(x/now);
    }
    return ans;
}

ll x, p, k;
int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        cin >> x >> p >> k; v.clear();
        for (ll i = 2; i*i <= p; ++i) {
            if (p%i == 0) v.push_back(i);
            while (p%i == 0) p/=i;
        }
        if (p > 1) v.push_back(p);
        k += get(x);//比 x 大的互质数里第 k 个
        ll l = 1, r = 1e12, ans = -1;
        while (l <= r) {
            ll mid = (l+r)>>1;
            if (get(mid) >= k) { ans = mid; r = mid-1; }
            else l = mid+1;
        }
        cout << ans << '\n';
    }
    return 0;
}