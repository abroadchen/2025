//
// Created by Psy.C on 2026/1/10.
//
///auto &[x, y]：自动推断类型并解构每个 node 对象
///排序范围从 p[0] 到 p[7]
///首先按 x 坐标升序排序
///如果 x 坐标相同，按 y 坐标升序排序
/*
p[0].x == p[1].x == p[2].x：前3个点有相同的x坐标
p[2].x != p[3].x：第3个点的x坐标不同
p[3].x == p[4].x：第4个点与第3个点x坐标相同
p[4].x != p[5].x：第4个点与第5个点x坐标不同
p[5].x == p[6].x == p[7].x：最后3个点有相同的x坐标
*/
/*
p[0].y == p[3].y == p[5].y：某些点有相同的y坐标
p[5].y != p[1].y：第5个点与第1个点y坐标不同
p[1].y == p[6].y：第1个点与第6个点y坐标相同
p[6].y != p[2].y：第6个点与第2个点y坐标不同
p[2].y == p[4].y == p[7].y：某些点有相同的y坐标
*/
///
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { int x, y; } p[8];//存储8个点的坐标

int main() {
    fast;
    for (auto &[x, y] : p) cin >> x >> y;
    sort(p, p + 8, [](const node a, const node b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    if (p[0].x == p[1].x && p[1].x == p[2].x && p[2].x != p[3].x &&
        p[3].x == p[4].x && p[4].x != p[5].x && p[5].x == p[6].x &&
        p[6].x == p[7].x && p[0].y == p[3].y && p[3].y == p[5].y &&
        p[5].y != p[1].y && p[1].y == p[6].y && p[6].y != p[2].y &&
        p[2].y == p[4].y && p[4].y == p[7].y) {
        cout << "respectable\n";
    } else cout << "ugly\n";
    return 0;
}