//
// Created by Psy.C on 2026/1/13.
//
/**
* n：数组h的长度
m：数组p的长度
h[N]：房屋位置数组
p[N]：邮筒位置数组
 *
 *tp = 0：邮筒指针，从第0个开始
*遍历每个房屋
如果邮筒用完了就停止
*pre：房屋i最近的邮筒位置
如果当前邮筒在房屋左边，使用当前邮筒
 *如果房屋到最近邮筒距离超过x，返回false
*d：当前房屋到邮筒的距离
nxt：计算当前邮筒能服务的最远位置
移动邮筒指针，跳过被当前邮筒服务的邮筒
 *
 *O((n+m) * log(max_pos))
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100010
using namespace std;

int n, m;
ll h[N], p[N];
bool ok(const ll x) {
    ll tp = 0;
    for (int i = 0; i < n && tp < m; ++i) {
        ll pre = h[i];
        if (p[tp] <= h[i]) pre = p[tp];
        if (h[i] - pre > x) return false;
        const ll d = h[i] - pre; ll nxt = max((x - d) / 2, x - 2 * d);
        nxt += h[i];
        while (tp < m && p[tp] <= nxt) tp++;
    }
    return tp == m;
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < m; ++i) cin >> p[i];
    ll l = 0, r = p[m-1] + h[n-1];
    while (l < r) {
        if (const ll mid = (l + r) >> 1; ok(mid)) r = mid; else l = mid + 1;
    }
    cout << r << '\n';
    return 0;
}