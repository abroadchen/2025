//
// Created by Psy.C on 2025/11/15.
//
/*
*a：等差数列首项
d：等差数列公差
n：数列长度
l, r：查询区间[左端点, 右端点]
 *
*边界条件检查：
如果查询上界v小于数列最小值a，返回0
如果查询下界u大于数列最大值a+d*(n-1)，返回0
 *
 *如果查询整个数列区间[1,n]：
*计算在查询范围[u,v]内的实际区间：
l：第一个≥u的元素位置
r：最后一个≤v的元素位置
 *
*计算等差数列区间和：
x = 2*a + (l+r-2)*d：首项与末项之和
y = r-l+1：项数
等差数列求和公式：S = (首项+末项) × 项数 / 2
为了避免除法，通过奇偶性判断来处理：
如果x是奇数，y右移1位（除以2）
如果x是偶数，x右移1位（除以2）
最后取模z返回结果
 *
 *计算中点：mid = (n+1)/2
*如果查询区间完全在左半部分，递归处理左半部分
d<<1表示公差变为2d（因为跳项选择）
*如果查询区间完全在右半部分，递归处理右半部分
a + d：右半部分的首项
l - mid, r - mid：转换为右半部分的相对位置
 *如果查询区间跨越左右两部分，分别计算两部分的和并相加
 *
 *
*每次查询：O(log n)
总复杂度：O(m log n)
 */
#include <cstdio>
using namespace std;

typedef long long ll;
int z;//模数
ll u, v;//查询范围的上下界

int fz(ll a, ll d, ll n, ll l, ll r) {
    if (v < a || u > a + d * (n - 1)) return 0;
    if (l == 1 && r == n) {
        if (u <= a) l = 1; else l = (u - a - 1) / d + 2;
        if (v >= a + d * (n - 1)) r = n; else r = (v - a) / d + 1;
        ll x = a * 2 + (l + r - 2) * d, y = r - l + 1;
        if (x & 1) y >>= 1; else x >>= 1;
        return x % z * (y % z) % z;
    }
    ll mid = (n + 1) >> 1;
    if (r <= mid) return fz(a, d<<1, mid, l, r);
    if (l > mid) return fz(a + d, d<<1, n - mid, l - mid, r - mid);
    return (fz(a, d<<1, mid, l, mid) +
        fz(a + d, d<<1, n - mid, 1, r - mid)) % z;
}


int main() {
    int m; ll n, l, r;
    scanf("%lld%d%d", &n, &m, &z);
    while (m--) {
        scanf("%lld%lld%lld%lld", &l, &r, &u, &v);
        printf("%d\n", fz(1, 1, n, l, r));
    }
    return 0;
}