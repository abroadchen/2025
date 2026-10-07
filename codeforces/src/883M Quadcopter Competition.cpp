//
// Created by Psy.C on 2026/10/7.
//
/**
起点 = 终点：输出 10。
含义解析：要从这里出发再回到原格的最短"车走 + 王步"混合步数。车走一步可沿直线任意距离，王每步只能走一格（含斜向）。回到原点至少需要"车出去、车回来"，在王棋子里这是最短"往返"概念
同列（x 相同）‍：2*|Δy| + 6
同行（y 相同）‍：2*|Δx| + 6
既不同行也不同列：2*(|Δx|+|Δy|) + 4
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { int x, y; } a, b;
int main() {
    fast;
    cin >> a.x >> a.y >> b.x >> b.y;
    if (a.x == b.x && a.y == b.y) cout << "10\n";
    else if (a.x == b.x) cout << 2*abs(a.y-b.y)+6 << '\n';
    else if (a.y == b.y) cout << 2*abs(a.x-b.x)+6 << '\n';
    else cout << 2*abs(a.y-b.y)+2*abs(a.x-b.x)+4 << '\n';
    return 0;
}