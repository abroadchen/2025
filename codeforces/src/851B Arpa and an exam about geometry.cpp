//
// Created by Psy.C on 2026/9/29.
//
/**
读入 A(ax,ay)、B(bx,by)、C(cx,cy) 三点坐标

第一条件：边长相等
|AB|² = |BC|²，即 B 到 A 和 B 到 C 距离相等。若不等 → 不可能是正方形，输出 No。

第二条件：垂直
(ax-bx)*(cy-by) == (cx-bx)*(ay-by) 判断向量 BA 与 BC 是否共线（即叉积为 0）。

若两者共线（BA ∥ BC）：说明 A、B、C 三点共线或退化成一条直线，无法构成正方形 → No。
若共线为假（且边长相等）：那么 BA 与 BC 等长且垂直，这恰好是正方形的两条邻边 → 构成正方形 → Yes
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

signed main() {
    fast;
    int ax = rd(), ay = rd(), bx = rd(), by = rd(), cx = rd(), cy = rd();
    if ((ax-bx)*(ax-bx)+(ay-by)*(ay-by) != (cx-bx)*(cx-bx)+(cy-by)*(cy-by)) cout << "No";
    else if ((ax-bx)*(cy-by) == (cx-bx)*(ay-by)) cout << "No";
    else cout << "Yes";
    return 0;
}