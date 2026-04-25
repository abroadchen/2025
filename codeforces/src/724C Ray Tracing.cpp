//
// Created by Psy.C on 2026/4/24.
//
/**
求解 ax + by = gcd(a,b) 的解
当 b = 0 时，x = 1, y = 0 是解
递归调用并更新 y 的值
求解 ax + by = c 的整数解
若 c 不被 gcd(a,b) 整除则无解
否则调整得到特解并转换为最小正整数解

计算四个不同方向上的最小值
mx 是 n 和 m 的最小公倍数相关的上界
尝试四种不同的 dx, dy 组合 (-x,-y), (-x,y), (x,-y), (x,y)
返回满足条件的最小值或 -1（无解）

单次查询时间复杂度约为 O(log(min(n,m)))
总体复杂度 O(k * log(min(n,m)))，其中 k 是查询次数
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1, y = 0; return a; }
    ll r = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}

ll eq(ll a, ll b, ll c, ll &x, ll &y) {
    ll g = ex_gcd(a, b, x, y);
    if (c % g) return -1;
    ll res = b/g; x *= c/g;//调整特解
    if (res < 0) res = -res;
    x = (x%res + res)%res;//取最小正整数解
    return 0;
}

ll n, m;
ll get(ll dx, ll dy, ll x) {
    ll k, s;
    if (eq(2*n, -2*m, -dx+dy, k, s) == -1)//求解 2*n*k - 2*m*s = -dx+dy
        return x + 1;//无解时返回超出范围的值
    ll tx = 2*k*n + dx;//计算目标值
    if (tx < 0 || tx > x) return x + 1;
    return tx;
}
ll mn(ll a, ll b) { return a < b ? a : b; }

ll out(ll x, ll y) {
    ll g = __gcd(n, m), mx = 1ll*m/g*n, ans = mx + 1;
    ans = mn(ans, get(-x, -y, mx));
    ans = mn(ans, get(-x, y, mx));
    ans = mn(ans, get(x, -y, mx));
    ans = mn(ans, get(x, y, mx));
    if (ans == mx + 1) return -1;
    return ans;
}

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

int k;
int main() {
    rd(n), rd(m), rd(k);
    for (int i = 0; i < k; ++i) {
        ll x, y; rd(x), rd(y);
        printf("%lld\n", out(x, y));
    }
    return 0;
}