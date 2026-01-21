//
// Created by Psy.C on 2026/1/21.
//
/**
*s[N]：前缀和数组
x[N]：坐标数组
d[N]：代价数组
k：需要选择的点数
 *
*cnt：累积代价
ans：最小累积代价
p：最优区间的右端点
 *
* x[j+1], x[j+2], ..., x[i] 是选中的k个点
(k-1)*(x[i] + x[j]): 与区间端点相关的项
2*(s[i-1] - s[j]): 中间点的贡献
 *
*时间复杂度: O(n log n)，主要消耗在排序
空间复杂度: O(n)
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300010
using namespace std;

struct node {
    ll x, y;//x: 坐标值 y: 原始索引
    friend bool operator<(const node a, const node b) {
        return a.x < b.x;
    }
} a[N];

int main() {
    fast;
    ll n; cin >> n;
    ll s[N], x[N], d[N], k; s[0] = 0;
    for (ll i = 1; i <= n; ++i) { cin >> a[i].x; a[i].y = i; }
    cin >> k;
    sort(a + 1, a + n + 1);
    for (ll i = 1; i <= n; ++i) x[i] = a[i].x;//排序后的坐标值从a[i].x复制到x[i]
    for (ll i = 1; i <= n; ++i) s[i] = s[i-1] + x[i];
    int j = 0;
    for (ll i = k + 1; i <= n; ++i) {
        ++j;
        d[i] = (k - 1) * (x[i] + x[j]) - 2 * (s[i-1] - s[j]);
    }
    ll cnt = 0, ans = 0, p = k;
    for (ll i = k + 1; i <= n; ++i) {
        cnt += d[i];
        if (ans > cnt) { ans = cnt; p = i; }//累积代价并寻找最优的右端点p
    }
    //最优区间内各点的原始索引
    for (ll i = p - k + 1; i <= p; ++i) cout << a[i].y << '\n';
    return 0;
}