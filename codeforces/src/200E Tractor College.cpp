//
// Created by Psy.C on 2025/12/4.
//
/*
*求解方程 ax + by = gcd(a,b) 的整数解：
当b=0时，gcd(a,0)=a，x=1，y=0
否则递归求解，并更新x和y
 *
*a, b, c：三种不同类型的人数
z：第三类人分配的糖果数
x, y：前两类人分配的糖果数（通过扩展欧几里得算法求得）
a0, b0：约简后的系数
 *
*计算给定k值时的目标值：
xx, yy：根据参数k得到的具体分配方案
返回 |xa - yb| + |yb - zc| 的值
 *
*比较函数，用于三分搜索：
首先检查约束条件（分配数量非负且不超过z）
然后比较目标函数值
 *
*n：总人数，s：总糖果数
统计每种类型的人数（类型3,4,5分别对应cnt[0],cnt[1],cnt[2]）
*a,b,c：各类型人数
ans：最优解，ix,iy,iz：最优解对应的分配方案
 *枚举第三类人每人分得的糖果数z（从1开始，直到总糖果足够分配）
*使用扩展欧几里得算法求解 ax + by = s - z*c：
如果(s-z*c)不能被gcd(a,b)整除，则无整数解
否则求出特解并转换为原方程的解
*使用三分搜索寻找最优的k值：
在[-inf, inf]范围内搜索
根据ok函数比较中间两点的优劣来缩小搜索范围
*验证解的有效性并更新最优解：
检查约束条件：0 ≤ xx ≤ yy ≤ z
如果满足条件且目标值更优，则更新答案
 *
*如果找到有效解，输出最优分配方案
否则输出-1表示无解
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int inf = 1e9+7;
template<typename T>//如果b小于a则更新a并返回true，否则返回false
bool minn(T& a, const T& b) { return b >= a ? false : (a = b, true); }

void gcd(const ll a, const ll b, ll& d, ll& x, ll& y) {
    if (!b) { d = a; x = 1; y = 0; }
    else {
        gcd(b, a % b, d, y, x);
        y -= (a / b) * x;
    }
}

ll a, b, c, z, x, y, a0, b0;
ll f(const ll k) {
    const ll xx = x + k * b0, yy = y - k * a0;
    return abs(xx * a - yy * b) + abs(yy * b - z * c);
}

bool ok(const ll k1, const ll k2) {
    if (x + k1 * b0 < 0) return false;
    if (x + k1 * b0 > z) return true;
    if (y - k1 * a0 < 0) return true;
    if (y - k1 * a0 > z) return false;
    if (x + k2 * b0 < 0) return false;
    if (x + k2 * b0 > z) return true;
    if (y - k2 * a0 < 0) return true;
    if (y - k2 * a0 > z) return false;
    if (x + k1 * b0 > y - k1 * a0) return true;
    if (x + k2 * b0 > y - k2 * a0) return true;
    return f(k1) <= f(k2);
}

int main() {
    fast;
    int n, s; cin >> n >> s;
    int cnt[3] = {};
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        cnt[t - 3]++;
    }
    a = cnt[0], b = cnt[1], c = cnt[2];
    ll ans = inf, ix = 0, iy = 0, iz = 0;
    for (z = 1; z * c <= s; ++z) {
        ll g; gcd(a, b, g, x, y);
        if ((s - z * c) % g) continue;
        const ll k = (s - z * c) / g;
        x *= k, y *= k;
        a0 = a / g, b0 = b / g;
        ll l = -inf, r = inf;
        while (l < r) {
            const ll m1 = l + (r - l) / 3, m2 = r - (r - l) / 3;
            if (ok(m1, m2)) r = m2 - 1;
            else l = m1 + 1;
        }
        const ll xx = x + l * b0, yy = y - l * a0;
        if (0 <= xx && xx <= yy && yy <= z) {
            if (minn(ans, f(l))) {
                ix = xx, iy = yy, iz = z;
            }
        }
    }
    if (ans < inf) cout << ix << ' ' << iy << ' ' << iz << '\n';
    else cout << "-1\n";
    return 0;
}