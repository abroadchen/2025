//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
Ax + By + C = 0 是一条直线。
起点 (xa,ya)、终点 (xb,yb)
先把答案初始化为两点间的 曼哈顿距离（即不改变方向、直接走棋盘的折线路径）作为候选上界
ay：直线与经过起点、保持 y=ya 的水平线交点（该交点的 x 坐标）。
ax：直线与经过起点、保持 x=xa 的竖直线交点（该交点的 y 坐标）。
同理 by、bx 对应终点 (xb,yb)。
这些都用于把"跨越直线"的路径拆成三段来逼近
每种候选都是"竖/横向走到直线上一点 → 直线段（欧氏距离）→ 再走向终点"的三段路径：

d1：起点先水平走到直线（|ay−xa|），沿直线走到 (xb,bx)，再从 (xb,bx) 竖直走到终点（|bx−yb|）。
d2：起点水平走到直线，沿直线走到 (by,yb)，再从 (by,yb) 横向走回终点（|by−xb|）。
d3：起点先竖直走到直线（|ax−ya|），沿直线到 (xb,bx)，再竖直回终点。
d4：起点竖直走到直线，沿直线到 (by,yb)，再横向回终点。
即 4 种"交点组合"（起点侧两种走向 × 终点侧两种走向），取其中最短
在曼哈顿基准与四条候选路径中取最小值。
输出保留 10 位小数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
using namespace std;

db dis(db x, db y, db u, db v) {
    return sqrt((x-u) * (x-u) + (y-v) * (y-v));
}

int A, B, C, xa, ya, xb, yb;
int main() {
    fast;
    cin >> A >> B >> C >> xa >> ya >> xb >> yb;
    db ans = 1.0*abs(ya-yb) + abs(xa-xb);
    db ay = (1.0*-B*ya-C)/A, ax = (1.0*-A*xa-C)/B;
    db by = (1.0*-B*yb-C)/A, bx = (1.0*-A*xb-C)/B;
    db d1 = 1.0*abs(ay-xa)+dis(ay,ya,xb,bx)+abs(bx-yb);
    db d2 = 1.0*abs(ay-xa)+dis(ay,ya,by,yb)+abs(by-xb);
    db d3 = 1.0*abs(ax-ya)+dis(xa,ax,xb,bx)+abs(bx-yb);
    db d4 = 1.0*abs(ax-ya)+dis(xa,ax,by,yb)+abs(by-xb);
    ans = min(ans, min(min(d1,d2), min(d3,d4)));
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}