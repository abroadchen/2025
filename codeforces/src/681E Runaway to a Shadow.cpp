//
// Created by Psy.C on 2026/4/15.
//
/**
N: 数组大小
a, b: 起始点坐标
v, t: 速度和时间
x, y, r: 圆心坐标和半径
dy, dx, d: 距离计算
tot, eg: 角度变量
lt, ans: 临时和结果变量
ve[N<<1]: 角度区间数组
圆的数量n

计算起始点到圆心的距离
如果起始点在圆内，输出1.0（全覆盖）
如果最大距离(v*t) + 半径 < 距离 - eps，说明不可达，跳过
atan2(dy, dx): 计算从起始点到圆心的角度
角度规范化到[0, 2π)

如果 v*t > sqrt(d²-r²)（可触及圆的最远点）：
eg = arcsin(r/d)（切线角度）
否则计算相交角度
计算圆在角度空间中形成的可见区间
处理跨0度或2π的特殊情况
将区间加入数组
按起始角度排序
合并重叠区间，计算总覆盖长度
将弧长转换为比例（除以2π）
输出覆盖比例
时间复杂度：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define eps 1e-9
#define pi acos(-1.)
#define dd pair<double,double>
using namespace std;
constexpr int N = 1e5+5;
double a, b, v, t, x, y, r, dy, dx, d, tot, eg, lt, ans;
int n, cnt;
dd ve[N<<1];
int main() {
    fast;
    cin >> a >> b >> v >> t >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y >> r;
        dy = y - b, dx = x - a, d = sqrt(dy*dy+dx*dx);
        if (d*d < r*r + eps) {
            cout << "1.0000000000\n";
            return 0;
        }
        if (v*t + r < d - eps) continue;
        tot = atan2(dy, dx);
        if (tot < 0) tot += 2.*pi;
        if (v*t + eps > sqrt(d*d-r*r)) eg = asin(r/d);
        else eg = acos(v*t/d/2.+(d*d-r*r)/v/t/d/2.);
        if (tot + eg > 2.*pi) {
            ve[cnt++] = {0, tot+eg-2.*pi};
            ve[cnt++] = {tot-eg, 2.*pi};
        } else if (tot - eg < 0.) {
            ve[cnt++] = {tot-eg+2.*pi, 2.*pi};
            ve[cnt++] = {0, tot+eg};
        } else ve[cnt++] = {tot-eg, tot+eg};
    }
    sort(ve, ve + cnt);
    for (int i = 0; i < cnt; ++i) {
        if (i == 0 || ve[i].first > lt) {
            ans += ve[i].second - ve[i].first;
            lt = ve[i].second;
        } else if (ve[i].second > lt) {
            ans += ve[i].second - lt;
            lt = ve[i].second;
        }
    }
    printf("%.10lf\n", ans/pi/2.);
    return 0;
}