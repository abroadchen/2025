//
// Created by Psy.C on 2026/9/15.
//
/**
有一个矩形，左下角 (x1,y1)、右上角 (x2,y2)。
有 n 个匀速运动的点，第 i 个初始位置 (x,y)，速度 (vx,vy)。
问是否存在一个正的时间 t，使得所有点同时都在矩形内；若存在输出最小的 t，否则 -1。
（坐标 pos + v*t 随时间线性移动。）
对一维（只看 x 或只看 y）：点位置 pos + v*t，要求它落在区间 [L, R] 内：

v == 0（静止）‍：
若 pos 已在 [L,R] 内部 → 任何 t 都可行，不影响区间，直接返回。
若 pos 不在内部 → 永远无法进入 → r = -1 标记无解。
v != 0：解不等式 L ≤ pos + v*t ≤ R：
t ∈ [(L-pos)/v, (R-pos)/v]，可能两端反序，用 swap 归一成 [t1, t2]。
把这个一维区间并入全局区间 [l, r]（l 取两者的较大下界、r 取两者的较小上界）——即区间求交。
对每个点，分别对 x 和 y 调用 update，把每个维度的时间区间都并进全局 [l,r]。
因为"某个时刻所有点都在矩形内"等价于：该时刻 t 同时落在所有点的 x 区间和所有点的 y 区间里。全部并到一起后，整个解集是所有区间（2n 个一维区间）的交集 [l,r]。
若交集非空（r - l >= eps）且为正（r > 0，要求 t>0），输出左端点 l（最小可行时间）；否则 -1。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-11
using namespace std;
constexpr double inf = 1e11;

double l = 0, r = inf;
void update(int pos, int L, int R, int v) {
    if (v == 0) {
        if (pos > L && pos < R) return;
        r = -1;
    }
    double t1 = (double)(L-pos)/v, t2 = (double)(R-pos)/v;
    if (t1 > t2) swap(t1, t2);
    l = max(l, t1), r = min(r, t2);
}

int main() {
    fast;
    int n; cin >> n;
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    for (int i = 1, x, y, vx, vy; i <= n; ++i) {
        cin >> x >> y >> vx >> vy;
        update(x, x1, x2, vx);
        update(y, y1, y2, vy);
    }
    if (r - l >= eps && r > 0) printf("%.10lf\n", l);
    else cout << "-1\n";
    return 0;
}