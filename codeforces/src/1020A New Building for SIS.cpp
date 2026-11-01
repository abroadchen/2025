//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
n, h：大概代表平面的行数、列数（或网格大小，但代码实际没用到 n, h）。
x, y：竖直方向的传送门区间，即传送门只作用于坐标在 [x, y] 之间（垂直方向范围）。
t：测试组数。
sx, sy, fx, fy：起点和终点的坐标（sx/sy 起点，fx/fy 终点）。
ans：当前答案
读入平面大小和传送门区间，再读入测试组数 t
读入起点 (sx, sy) 和终点 (fx, fy)
传送门只对竖直坐标 [x, y] 区间内的点有效。要在竖直方向不移动的情况下改变水平坐标（即利用传送门），就必须先把自己的 sy 挪进区间 [x, y]：

如果 sy 已经落在 [x, y] 内 → 可以直接一步跨越水平距离 |sx - fx|；
如果 sy < x → 先竖直走到下边界 x，花费 |sy - x|，再传送；
如果 sy > y → 先竖直走到上边界 y，花费 |y - sy|，再传送。
到达目标列后，再竖直移动到终点的 fy，加上竖直差值即可
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int n, h, x, y, t, sx, sy, fx, fy, ans;
int main() {
    fast;
    cin >> n >> h >> x >> y >> t;
    while(t--) {
        ans = 0;
        cin >> sx >> sy >> fx >> fy;
        while (sx != fx) {
            if (x <= sy && sy <= y) {
                ans += abs(sx - fx);
                sx = fx;
            } else if (sy < x) {
                ans += abs(sy - x);
                sy = x;
            } else if (sy > y) {
                ans += abs(y - sy);
                sy = y;
            }
        }
        cout << ans + abs(sy-fy) << '\n';
    }
    return 0;
}