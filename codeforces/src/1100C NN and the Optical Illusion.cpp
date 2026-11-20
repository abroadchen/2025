//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
a = pi*2/n;      // a = 2π/n   （正是正n边形的中心角）
a /= 2;          // a = π/n    （中心角的一半）
a = sinf(a);     // a = sin(π/n)
a = 1/a;         // a = 1/sin(π/n)
a = a - 1;       // a = 1/sin(π/n) - 1
a = r / a;       // a = r / (1/sin(π/n) - 1)
正 n 边形邻接两顶点对圆心的夹角为 2π/n，半角为 π/n。
由三角函数关系可得内切圆半径与外接圆半径满足 r_out / r_in = 1/sin(π/n)。
若要求的是"某个内外中间圆"的半径，等价于解 r = a·(1/sin(π/n) − 1)，从而 a = r/(1/sin(π/n)−1)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define pi 3.14159265358979
using namespace std;

ld n, r, a;
int main() {
    fast;
    cin >> n >> r; a = pi*2/n; a/=2; a = sinf(a); a = 1/a; a = a-1; a = r/a;
    cout << fixed << setprecision(8) << a;
    return 0;
}