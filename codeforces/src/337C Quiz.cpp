//
// Created by Psy.C on 2026/1/11.
//
/**
* 组合结构：2^cnt 通常表示从cnt个元素中选择子集的方式数
排除空集：2^cnt - 1 表示非空子集的数量
扩展到k个单位：乘以k表示每种子集选择对应k个单位
对称性或双向性：乘以2可能表示某种对称关系或双向计算
 *
*cnt = n/k - (n-m)：
n/k：在前n个位置中，完整的k长度段的数量
n-m：非特殊位置的数量（因为总共有n个位置，m个特殊位置）
cnt：表示某种超出范围的k段数量
cnt * k：
表示 cnt 个完整的k长度段所包含的位置总数
m - cnt * k：
从m个特殊位置中减去 cnt * k 个位置
这可能表示剩余的未被特殊处理的特殊位置数量
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define mod 1000000009
using namespace std;

ll qsm(ll a, ll b) {
    ll mul = 1;
    while (b) {
        if (b & 1) mul = mul * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return mul;
}

int main() {
    fast;
    ll n, m, k; cin >> n >> m >> k;
    if (const ll x = n - m, y = n / k; y <= x) cout << m % mod << '\n'; else {
        const ll cnt = y - x; ll ans = (qsm(2, cnt) * k - k) * 2 % mod;
        ans += m - cnt * k;
        cout << ans % mod << '\n';
    }
    return 0;
}