//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
n：棋盘边长（n×n 的棋盘）。
(ax, ay)：王后的坐标（Q）。
(bx, by)：起点坐标（起始 K 的位置）。
(cx, cy)：终点坐标
起点 (bx,by) 与终点 (cx,cy) 必须位于王后 (ax,ay) 的同一个"对角象限"内，即两者同时满足属于以下四种情况之一：

bx<ax && by<ay && cx<ax && cy<ay：都位于王后左上（左下方）区域；
bx<ax && by>ay && cx<ax && cy>ay：都位于王后右上（左上方）区域；
bx>ax && by<ay && cx>ax && cy<ay：都位于王后右下区；
bx>ax && by>ay && cx>ax && cy>ay：都位于王后右下（右上方）区。
四象限以王后 (ax,ay) 为"十字"的中心划开：

第 1 种：左上；
第 2 种：左下（x 小 y 大）；
第 3 种：右上（x 大 y 小）；
第 4 种：右下。
只有起点和终点落在同一个象限（相对王后）时输出 YES，否则输出 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, ax, ay, bx, by, cx, cy;
signed main() {
    fast;
    cin >> n >> ax >> ay >> bx >> by >> cx >> cy;
    if ((bx<ax&&by<ay&&cx<ax&&cy<ay) || (bx<ax&&by>ay&&cx<ax&&cy>ay) ||
        (bx>ax&&by<ay&&cx>ax&&cy<ay) || (bx>ax&&by>ay&&cx>ax&&cy>ay))
        cout << "YES";
    else cout << "NO";
    return 0;
}