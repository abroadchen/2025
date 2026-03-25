//
// Created by Psy.C on 2026/3/25.
//
/**
判断点c是否在直线段ab的延长线上（x坐标相同但y坐标超出范围）(y坐标相同但x坐标超出范围）
存储三个点的坐标
a统计x坐标相同的点对数，b统计y坐标相同的点对数

统计平行于坐标轴的边数
所有点共线（要么x相同，要么y相同）→ 1个矩形
两个方向各有一对点共线 → 2个矩形
只有一个方向有共线点（垂直方向）
检查是否有点在另外两点构成的线段延长线上 点在线段延长线上 → 2个矩形
点在中间 → 3个矩形
只有一个方向有共线点（水平方向)
检查是否有点在另外两点构成的线段延长线上 点在线段延长线上 → 2个矩形
点在中间 → 3个矩形
没有共线点 → 3个矩形

三点共线（a=3或b=3）：只能形成1个矩形
两对共线（a=1且b=1）：形成2个矩形
单方向共线（a=1或b=1）：
若第三个点在共线两点的延长线上 → 2个矩形
否则 → 3个矩形
无共线：形成3个矩形
几何意义：
三个点可以形成3个两两配对的矩形（以每对点作为对角顶点）
当存在共线情况时，某些矩形会退化或合并
O(1)，只有固定的几个判断条件
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define o1(a,b,c) x[a]==x[b]&&(y[c]<min(y[a],y[b])||y[c]>max(y[a],y[b]))
#define o2(a,b,c) y[a]==y[b]&&(x[c]<min(x[a],x[b])||x[c]>max(x[a],x[b]))
using namespace std;

int x[3], y[3];
int main() {
    fast;
    for (int i = 0; i < 3; ++i) cin >> x[i] >> y[i];
    int a = 0, b = 0, ans;
    for (int i = 0; i < 2; ++i)
        for (int j = i + 1; j < 3; ++j) {
            if (x[i] == x[j]) a++;
            if (y[i] == y[j]) b++;
        }
    if (a == 3 || b == 3) ans = 1;
    else if (a == 1 && b == 1) ans = 2;
    else if (a == 1) {
        if (o1(0,1,2)||o1(0,2,1)||o1(1,2,0)) ans = 2;
        else ans = 3;
    } else if (b == 1) {
        if (o2(0,1,2)||o2(1,2,0)||o2(0,2,1)) ans = 2;
        else ans = 3;
    } else ans = 3;
    cout << ans << '\n';
    return 0;
}