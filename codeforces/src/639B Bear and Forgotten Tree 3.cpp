//
// Created by Psy.C on 2026/3/31.
//
/**
n：树中节点总数
d：树的直径（最长路径长度）
h：从节点1开始的最大深度
直径减去高度不能大于高度本身
几何意义：从根节点出发的最长路径不能比通过根节点的最长路径还长
当直径为1时，意味着只有两条相邻的边
如果节点数≥3，则不可能构造出直径为1的树

构造从节点1开始的主干路径，长度为h
连接边：1-2, 2-3, ..., h-(h+1)
从节点1开始的第二条链，长度为d-h
连接方式是依次扩展，形成从1出发的分支
将剩余的 n-d-1 个节点全部连接到深度为h的节点上
这样确保这些节点不会增加直径长度

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, d, h;
int main() {
    fast;
    cin >> n >> d >> h;
    if (d - h > h) {
        cout << -1 << '\n';
        return 0;
    }
    if (d == 1) {
        if (n >= 3) {
            cout << -1 << '\n';
            return 0;
        }
    }
    int x = 1;
    for (int i = 1; i <= h; ++i) {
        cout << x << ' ' << x + 1 << '\n';
        x++;
    }
    int y = 1;
    for (int i = 1; i <= d-h; ++i) {
        cout << y << ' ' << x + 1 << '\n';
        y = ++x;
    }
    for (int i = 1; i <= n-d-1; ++i)
        cout << h << ' ' << ++x << '\n';
    return 0;
}