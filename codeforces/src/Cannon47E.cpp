//
// Created by Psy.C on 2025/10/11.
//
/*
*N和M分别为角度和障碍物数组的最大大小
g为重力加速度(9.8 m/s²)
eps为浮点数比较的精度误差
 *
*a数组存储角度信息，first为角度值，second为原始索引
c数组存储障碍物坐标(first为X坐标，second为Y坐标)
res数组存储结果(first为最终X坐标，second为最终Y坐标)
 *
*读取炮弹数量n和初速度v
读取n个发射角度，并记录原始索引
按角度大小对发射角度进行排序

*读取障碍物数量m
读取m个障碍物的坐标(X,Y)
按X坐标对障碍物进行排序
*对每个发射角度进行计算：
使用物理抛物运动公式计算轨迹
t为到达障碍物X坐标所需时间
y为在该时刻的高度
公式基于经典物理：y = v₀sin(θ)t - ½gt²
 *
*判断是否撞击障碍物：
如果高度小于障碍物高度或几乎相等(考虑精度误差)，则发生撞击
如果撞击点在地面以下(y≤0)，则修正为地面撞击点
记录撞击点坐标到结果数组中对应位置
跳出循环处理下一个角度
 *
*如果没有撞击任何障碍物：
计算炮弹落地点：飞行时间为2vsin(θ)/g
落地点X坐标为v*cos(θ)*t
Y坐标为0(地面)
 *
*输出结果：
按原始顺序输出每个炮弹的落点坐标
使用fixed格式和6位小数精度
 *
 *
 */
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <ios>
#include <iostream>
using namespace std;

const int N = 1e4+5, M = 1e5+5;
const double g = 9.8, eps = 1e-9;
pair<double, int> a[N];
pair<double, double> c[M], res[N];

void solve() {
    int n, v; cin >> n >> v;
    for (int i = 1; i <= n; ++i) { cin >> a[i].first; a[i].second = i; }
    sort(a+1, a+n+1);
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) cin >> c[i].first >> c[i].second;
    sort(c+1, c+m+1);

    for (int i = 1, j = 1; i <= n; ++i) {
        for (; j <= m; ++j) {
            double X = c[j].first, Y = c[j].second;
            double t = X / (v * cos(a[i].first));
            double y = sin(a[i].first) * v * t - g * t * t / 2;
            if (y < Y || abs(y - Y) < eps) {
                int k = a[i].second;
                if (y <= 0) {
                    y = 0;
                    t = 2 * sin(a[i].first) * v / g;
                    X = cos(a[i].first) * v * t;
                }
                res[k].first = X; res[k].second = y;
                break;
            }
        }
        if (j > m) {
            double t = 2 * sin(a[i].first) * v / g;
            double x = cos(a[i].first) * v * t;
            res[a[i].second].first = x; res[a[i].second].second = 0;
        }
    }

    for (int i = 1; i <= n; ++i)
        cout << fixed << setprecision(6) << res[i].first << ' ' << res[i].second << '\n';
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    solve();
    return 0;
}