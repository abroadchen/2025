//
// Created by Psy.C on 2025/11/23.
//
/*
*n, m：网格的行数和列数
x, y：当前位置坐标
k：移动指令数量
step(0)：总步数，初始化为0
dx, dy：每次移动的x和y方向增量
 *
*计算在x方向上最多能走多少步才碰到边界：
如果向右移动(dx>0)：距离右边界的步数 = (n-x)/dx
如果向左移动(dx<0)：距离左边界的步数 = (x-1)/(-dx)
如果不移动(dx=0)：设为无穷大INT_MAX
 */
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;
ll n, m, x, y, k, step(0), dx, dy;

int main() {
    ostream::sync_with_stdio(false);
    cin >> n >> m >> x >> y >> k;
    for (ll i = 0, fac1, fac2; i < k; ++i) {
        cin >> dx >> dy;
        if (dx > 0) fac1 = (n - x) / dx;
        else if (dx < 0) fac1 = (x - 1) / (-1*dx);
        else fac1 = INT_MAX;
        if (dy > 0) fac2 = (m - y) / dy;
        else if (dy < 0) fac2 = (y - 1) / (-1*dy);
        else fac2 = INT_MAX;
        const ll res = min(fac1, fac2);//本次移动能走的最大步数
        x += dx * res;
        y += dy * res;
        step += res;
    }
    cout << step;
    return 0;
}