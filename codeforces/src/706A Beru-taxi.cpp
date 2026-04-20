//
// Created by Psy.C on 2026/4/19.
//
/**
sx, sy: 起始点坐标
x, y: 当前点坐标
v: 速度
m: 点的数量
计算起始点(sx,sy)到当前点(x,y)的直线距离
公式：√[(sx-x)² + (sy-y)²]
res*1./v: 时间 = 距离 ÷ 速度
res*1.: 将res转换为double类型
更新最小时间
O(m): 遍历所有目标点一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int inf = 0x7fffffff;
int sx, sy, x, y, v, m;
int main() {
    fast;
    cin >> sx >> sy;
    double mn = inf;
    cin >> m;
    while (m--) {
        cin >> x >> y >> v;
        double res = sqrt((sx-x)*(sx-x)+(sy-y)*(sy-y));
        if (res*1./v < mn) mn = res*1./v;
    }
    printf("%.7f\n", mn);
    return 0;
}