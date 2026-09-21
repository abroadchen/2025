//
// Created by Psy.C on 2026/9/21.
//
/**
num 记录该圆被多少个外层（半径更大的）圆相交/包含。
按半径从大到小排序，保证处理外层优先
两圆圆心距离平方 < 半径和平方 → 视为相交（重叠）。
注意：这是包含/重叠的粗判定，不是严格"内含"判断
两圆圆心距离平方 < 半径和平方 → 视为相交（重叠）。
注意：这是包含/重叠的粗判定，不是严格"内含"判断
get(u) = π·r² 为圆面积。
层级为 0 或奇数 → 加；偶数 → 减
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define pi acos(-1)
using namespace std;
constexpr int N = 1e3+5;
struct node { db x, y, r; int num; } a[N];
bool cmp(node p, node q) { return p.r > q.r; }
bool check(node u, node v) {
    return (u.x - v.x)*(u.x - v.x) + (u.y - v.y)*(u.y - v.y) <
        (u.r + v.r)*(u.r + v.r);
}
db get(node u) { return u.r*u.r*pi; }

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y >> a[i].r;
    sort(a+1, a+1+n, cmp);
    for (int i = 1; i <= n; ++i)
        for (int j = i+1; j <= n; ++j)
            if (check(a[i], a[j])) a[j].num++;
    db ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!a[i].num) ans += get(a[i]);
        else if (a[i].num&1) ans += get(a[i]);
        else ans -= get(a[i]);
    }
    printf("%.8f\n", ans);
    return 0;
}