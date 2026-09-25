//
// Created by Psy.C on 2026/9/25.
//
/**
cbrt 求实数立方根，round 四舍五入到最近的整数，得到候选的 z。
目的：若 x·y 是真立方数（perfect cube），则其整数立方根 z 应恰好等于该值
同时对 z 做三个条件校验：

z*z*z == x*y：z 的立方恰好等于 x·y —— 保证 ∛(x·y) 是整数 z（真立方数）。
x % z == 0：z 能整除 x。
y % z == 0：z 能整除 y。
只有三个条件同时成立才输出 "Yes"
由于浮点数 cbrt(x*y) 存在精度误差，直接比较浮点立方根与整数可能误判。用 round 先取最近整数 z，再用整数运算 z*z*z == x*y 做精确验证，规避浮点误差——这是本解的关键技巧
如果三个条件全满足，则 z 同时整除 x 和 y，且 z³ = x·y，意味着几何平均 ∛(x·y) = z 是整数，并且 x、y 都能被这个"平均"整除
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;


signed main() {
    fast;
    int a; cin >> a;
    while (a--) {
        int x, y; cin >> x >> y;
        int z = round(cbrt(x * y));
        if (z*z*z == x*y && x%z == 0 && y%z == 0) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}