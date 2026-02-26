//
// Created by Psy.C on 2026/2/26.
//
/**
r：圆的半径
x, y：起始点坐标
x1, y11：目标点坐标
dx：x方向距离的平方
dy：y方向距离的平方
dx + dy：欧几里得距离的平方
sqrt(dx + dy)：两点间的直线距离
2*r：每次移动的最大距离（直径）
ceil(...)：向上取整得到最少步数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll r, x, y, x1, y11;
int main() {
    fast;
    cin >> r >> x >> y >> x1 >> y11;
    const ll dx = (x-x1)*(x-x1), dy = (y-y11)*(y-y11),
    ans = ceil(sqrt(dx + dy)/(2*r));
    cout << ans << '\n';
    return 0;
}