//
// Created by Psy.C on 2026/1/12.
//
/**
* n：路径长度
m：障碍物数量
s：起始位置
f：目标位置
d：移动方向（1表示向右/向前，-1表示向左/向后）
*t：障碍物出现的时间
l, r：障碍物覆盖的区间 [l, r]
x：当前时间（从1开始）
 *
*在障碍物到达前的时间内
沿着目标方向移动
输出相应的移动指令（'R'向右，'L'向左）
 *如果已到达目标，程序结束
*s >= l && s <= r：当前位置在障碍物区间内
s + d >= l && s + d <= r：下一步位置在障碍物区间内
如果任一条件满足，输出 'X'（等待） 否则，继续移动并输出相应方向
*时间前进1单位
如果还有障碍物，读入下一个障碍物信息
否则设置 t = INT_MAX（不再有障碍物）
 *
 *O(|f-s| + 障碍物数量)，算法在移动过程中处理时间窗口内的障碍物
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, s, f; cin >> n >> m >> s >> f;
    const int d =  s < f ? 1 : -1;
    int t, l, r, x = 1; cin >> t >> l >> r;
    while (true) {
        while (x < t && s != f) {
            ++x;
            s += d;
            cout << (d == 1 ? 'R' : 'L');
        }
        if (s == f) return 0;
        if (s >= l && s <= r || s + d >= l && s + d <= r) cout << 'X'; else {
            s += d; cout << (d == 1 ? 'R' : 'L');
        }
        ++x;
        if (--m) cin >> t >> l >> r; else t = INT_MAX;
    }
}
