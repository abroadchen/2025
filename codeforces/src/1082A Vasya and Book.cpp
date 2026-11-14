//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
每组读入 n（总位置数）、x（起点）、y（终点）、d（固定步长），mn 重置
如果 |x-y| 恰好是 d 的整数倍，说明不用中转，可以直接从 x 一步 d 地走到 y，步数 = 差值/d
条件 (y-1)%d==0：终点 y 到位置 1 的距离被 d 整除，即从位置 1 能直接到达 y。
步数 = (x-1+d-1)/d（x 走到 1 的步数，向上取整因为 1→x 不整除时也要走）＋ (y-1)/d（1 走到 y）。

(x-1+d-1)/d 是 ceil((x-1)/d)，因为从 1 每次走 d 到 x，不整除时多走一步
条件 (n-y)%d==0：终点 y 到位置 n 的距离被 d 整除，即从位置 n 能直接到达 y。
步数 = (n-x+d-1)/d（x 走到 n，向上取整）＋ (n-y)/d（n 走到 y）
三种情况都试完后，如果 mn 仍为 INT_MAX（没有任何一种可行），输出 -1；否则输出最小步数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;


int T, n, x, y, d, mn = INT_MAX;
signed main() {
    fast;
    cin >> T;
    while (T--) {
        mn = INT_MAX;
        cin >> n >> x >> y >> d;
        if (abs(x-y)%d == 0) mn = min(mn, abs(x-y)/d);
        if ((y-1)%d == 0) mn = min(mn, (x-1+d-1)/d+(y-1)/d);
        if ((n-y)%d == 0) mn = min(mn, (n-x+d-1)/d+(n-y)/d);
        if (mn == INT_MAX) mn = -1;
        cout << mn << '\n';
    }
    return 0;
}