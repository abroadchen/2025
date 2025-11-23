//
// Created by Psy.C on 2025/11/21.
//
/*
 *v: 公主的速度
 *vd: 龙的速度
 * t: 龙延迟出发的时间
 *f: 公主被抓后森林停留时间
 *c: 公主城堡距离起点的距离
 *p: 龙开始追赶时公主的位置
 *d: 龙的位置（始终为0，因为以龙的起点为参考点）
 *cnt: 被抓次数计数器
 *
 *相对速度是(vd - v)，需要追赶的距离是p
 *追赶时间 = p / (vd - v)
 *追上时公主又前进的距离 = (p / (vd - v)) * v
 *所以追上时公主的总位置 = p + (p / (vd - v)) * v
 *
 *公主被抓后：
 *回到起点（位置变为0）
 *在森林停留f时间
 *再次出发时，公主已经走了 (p/vd + f) * v 的距离
 */
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    double v, vd, t, f, c; cin >> v >> vd >> t >> f >> c;
    if (v >= vd) { cout << 0 << '\n'; return 0; }//如果公主速度大于等于龙的速度，龙永远追不上公主
    double p = t * v, d = 0, cnt = 0;
    while (p < c) {//当公主还没到达城堡时继续循环
        p += p / (vd - v) * v;
        if (p >= c) break;//如果此时公主已经到达或超过城堡，逃脱成功
        p += (p / vd + f) * v;
        cnt++;
    }
    cout << cnt << '\n';
    return 0;
}