//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
n 是操作次数。
mx、my 是累积维护的两个关键值：
mx：所有已插入物品中 min(x,y) 的最大值（即每个物品较短边的最大值）；
my：所有已插入物品中 max(x,y) 的最大值（即每个物品较长边的最大值
遇到 +：插入一个 x × y 的物品。

更新 mx = max(mx, min(x, y))：让"最短边"记录变得尽可能大；
更新 my = max(my, max(x, y))：让"最长边"记录变得尽可能大。
为什么这么做是充分的？把所有物品都旋转到"短边一致朝下"来看：最"难装"的那个物品，取决于它最短边是否超宽、最长边是否超高。只要维护好"所有物品最短边的最大值 mx"和"所有物品最长边的最大值 my"，如果最严苛的这两个值都能放进去，那么所有物品都能放进去（只需保证盒子足够大即可——因为只要能放下最坏的，逐个旋转摆放总能放下所有）
遇到 ?：查询盒子 h × w 能否装下所有已插入物品。
判断：因为盒子也可以旋转，所以有两种放置方式——
方式一：mx <= h 且 my <= w；
方式二：mx <= w 且 my <= h（旋转盒子 90°）。
只要满足其中一种，就输出 YES，否则输出 NO
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int mx = 0, my = 0;
    for (int i = 0; i < n; ++i) {
        char op; cin >> op;
        if (op == '+') {
            int x, y; cin >> x >> y;
            mx = max(mx, min(x,y)), my = max(my, max(x,y));
        }
        if (op == '?') {
            int h, w; cin >> h >> w;
            (mx <= h && my <= w) || (mx <= w && my <= h) ? cout << "YES\n" : cout << "NO\n";
        }
    }
    return 0;
}