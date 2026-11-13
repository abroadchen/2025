//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
n 棋盘边长，x,y 目标格子坐标，w,b 两个起点到目标的步数
abs(x-1)：从白色起点所在第一行到目标行距离；abs(y-1)：从白色起点所在第一列到目标列距离。
由于白色可沿对角线移动（每次可同时改变行和列），到 (x,y) 的最少步数 = 行差与列差中的较大者…… 但这里用的是 min。
这里代码用的其实是一个简化/特化的公式：当双方都是"可在对角线走"时，某点到角落起点的距离可表示为 max(行差, 列差)；但本代码直接取 min，说明每个角色只沿一条直线（单行/单列）移动，即只走直线不走对角线，因此到目标只需行、列差中较小的那条。
关键：取 min 说明步数 = 只沿一个方向（不相交的直线）移动，即"哪条直线近就走哪条"。本质是在判断目标格离左/上边界近 还是 离右/下边界近
同理：黑色从 (n,n) 出发，到目标格的距离取 abs(x-n)（距底行）、abs(y-n)（距右列）中较小者
谁走的步数少谁先到；平局（w==b）判 White 赢
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, x, y, w, b;
int main() {
    fast;
    cin >> n >> x >> y;
    w = min(abs(x-1), abs(y-1));
    b = min(abs(x-n), abs(y-n));
    if (w <= b) cout << "White\n"; else cout << "Black\n";
    return 0;
}