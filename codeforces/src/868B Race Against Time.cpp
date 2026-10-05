//
// Created by Psy.C on 2026/10/5.
//
/**
h, m, s：当前时刻的小时、分钟、秒。
x, y：表示某个角度区间 [x, y]
角度计算（从 12 点方向顺时针）：

秒针 ns：每秒走
360
/
60
=
6
360/60=6 度，所以 s*6。✓
分针 nm：m 分钟本身走 m*6 度；加上秒针带动分针的增量。分针受秒针影响：ns 占
360
360 度的比例（ns/360）再乘以分针每分钟的 6 度。所以 nm = m*6 + (ns/360)*6。✓
时针 nh：h 小时走 h*30 度；加上分针带动时针的增量 (nm/360)*30。✓
目标指针：nx = x*30, ny = y*30，即输入的 x, y 各自乘 30 得到实际角度。l, r 是这两个角度的 min/max，构成区间 [l, r]
统计三根指针（时针、分针、秒针）中有几根落在区间 [l, r] 内：

cnt：落在区间内的指针数量。
若 cnt == 0 或 cnt == 3（全部不在 或 全部在）→ 输出 YES；否则（恰有 1 或 2 根在区间内）→ 输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int h, m, s, x, y, cnt = 0; cin >> h >> m >> s >> x >> y;
    double ns = s*1.0*6, nm = m*1.0*6+ns/360*6, nh = h*30+nm/360*30,
    nx = x*30, ny = y*30, l = min(nx, ny), r = max(nx, ny);
    if (ns >= l && ns <= r) cnt++;
    if (nm >= l && nm <= r) cnt++;
    if (nh >= l && nh <= r) cnt++;
    if (cnt == 0 || cnt == 3) cout << "YES"; else cout << "NO";
    return 0;
}