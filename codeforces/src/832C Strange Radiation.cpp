//
// Created by Psy.C on 2026/9/24.
//
/**
坐标范围 [0, Y]，Y = 1e6。
down(x,y) / up(x,y)：分别把 x 取为 min(x,y) / max(x,y)
n：点的个数。
v[0]：区间的固定长度（公路/目标区间长度）。
每个点 i：初始位置 x[i]，速度 v[i]，方向标志 t。
t==1 表示向负方向运动（v[i] 取负）
判断在时间 t 内，是否存在一个长度为 v[0] 的区间能"同时覆盖"所有点可达位置的交集
注意区分变量名冲突：外层 int v[N] 是速度数组，循环里的局部 t 只控制方向
方向归一化：把每个点变换到"向正方向运动 v0>0"的坐标系：
若原速度为正（v[i]>0），rev=0，坐标 x0=x[i]。
若原速度为负，rev=1，做对称变换 x0 = Y - x[i]（把整个坐标轴翻转，负方向变正方向）。
这样所有点都统一成向右（正方向）运动，便于统一计算
计算每个点的可达区间 [l, r]
目标位置范围是 [0, Y]，区间长度固定为 v[0]：
时间 t 内点从 x0 以速度 v0 向右最多到 x0 + v0*t，而目标区间须满足……这段的几何推导是把"长度为 v0 的区间右端"约束到点能到达的范围内。
l, r 给出了该点可达的那个长度固定区间的右端点允许范围（右端落在 [l, r]）。
维护所有点可达区间右端点的共同交集：
正向点：右边界约束 li（左界上界 max）、ls（右界下界 min）。
反向点：坐标已翻转，右端对应 Y - r、Y - l 调整。
最终判定所有区间是否有公共交集：
若所有可达区间存在共同的右端点重叠，则返回 true（可行）
对时间 t ∈ [0, Y] 做实数二分。
get(mid) 为 true（可行）→ 缩小上界 r=mid；否则增大下界 l=mid。
最终输出最小的可行时间 (l+r)/2。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define db long double
using namespace std;
constexpr int N = 1e5+15;
constexpr db Y = 1e6, eps = 1e-9;

void down(db& x, db y) { x > y ? x = y : 0; }
void up(db& x, db y) { x < y ? x = y : 0; }

int n, v[N], x[N];
bool get(db t) {
    db v0, x0, l, r, li = Y, ls = 0, ri = Y, rs = 0;
    bool rev = 0;
    for (int i = 1; i <= n; ++i) {
        v0 = (db)(((rev = (v[i]>0))) ? v[i] : -v[i]);
        x0 = (db)(rev ? Y-x[i] : x[i]);
        if (x0 <= v0*t) { l = 0; r = Y; }//时间足够到左端，可达全区间
        else {
            l = x0;
            down(r=Y, x0/v0*v[0]);
            down(r, (x0*v0+((db)v[0]*v[0]-v0*v0)*t)/v[0]);//可达性约束
        }
        if (l > r + eps) continue;
        rev ? down(ri, Y-r) : down(li, l);
        rev ? up(rs, Y-l) : up(ls, r);
    }
    return ceil(max(li, ri)) <= floor(min(ls, rs)) + eps;
}


signed main() {
    fast;
    cout << fixed << setprecision(9);
    cin >> n >> v[0];
    for (int i = 1, t; i <= n; ++i) {
        cin >> x[i] >> v[i] >> t;
        if (t == 1) v[i] = -v[i];
    }
    db l = 0, r = Y;
    while (r - l > eps) {
        db mid = (l+r)*0.5;
        get(mid) ? r = mid : l = mid;
    }
    cout << (l+r)*0.5 << '\n';
    return 0;
}