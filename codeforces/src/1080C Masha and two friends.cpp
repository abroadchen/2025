//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
左上 (x1,y1) 到右下 (x2,y2)
设该矩形的总格数为 b（= 宽 × 高）。黑格数公式是：

先取 b/2；
若矩形第一格是黑格（条件 (x1+y1) 为奇数，因为黑白按 x+y 奇偶相间）‍且总格数为奇数，则多 +1。
即：黑 = 总格数/2 + (起点是黑 && 总数奇)。这覆盖了两格一比和起点奇偶带来的误差。
白格数 = 总格数 − 黑格数。
返回两矩形的交集矩形（四个方向取重叠部分）。若不相交则会出现 x1>x2 或 y1>y2，这时 in 得到的矩形为空，靠 fb/fw 里的 if 返回 0。
先用 c[0]（整个棋盘）算初始白格 w、黑格 b
再取两个矩形的交集 c[3] = c[1] ∩ c[2]。

第一步：矩形 1 翻转颜色（黑↔白）
数一下矩形 1 内原本是黑的格数（c[1].fb()），它们翻转后变白；但其中落在交叠区 c[3] 的那些（c[3].fb()）之后还会被矩形 2 涂白，为避免后面重复算，这里处理"净翻转"部分。

第二步：矩形 2 全部涂白

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct node {
    ll x1, y1, x2, y2;
    ll fb() {
        if (x1 > x2 || y1 > y2) return 0;
        ll b = (x2-x1+1)*(y2-y1+1);
        return b/2+(x1+y1&1 && b&1);
    }
    ll fw() {
        if (x1 > x2 || y1 > y2) return 0;
        return (x2-x1+1)*(y2-y1+1) - fb();
    }
    node in(const node &o) const {
        node ret{};
        ret.x1 = max(x1, o.x1), ret.x2 = min(x2, o.x2);
        ret.y1 = max(y1, o.y1), ret.y2 = min(y2, o.y2);
        return ret;
    }
} c[4];

int main() {
    fast;
    int q, n, m, x1, y1, x2, y2;
    for (cin >> q; q; q--) {
        cin >> n >> m; c[0] = {1,1,n,m};
        for (int i = 1; i <= 2; i++) {
            cin >> x1 >> y1 >> x2 >> y2;
            c[i] = {x1,y1,x2,y2};
        }
        ll w = c[0].fw(), b = c[0].fb();
        c[3] = c[1].in(c[2]);
        w += c[1].fb() - c[3].fb(); b -= c[1].fb() - c[3].fb();
        b += c[2].fw(); w -= c[2].fw();
        cout << w << ' ' << b << '\n';
    }
    return 0;
}