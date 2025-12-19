//
// Created by Psy.C on 2025/12/19.
//
/*
 *n为点数，a,b为坐标，ang存储角度
 *
 *将直角坐标转换为角度（度数制）
 *处理负角度情况
 *处理第三、四象限的情况（atan函数只能区分四个象限中的两个）
 *按降序排序角度
 *计算相邻角度之间的最大间隙
 *检查所有相邻角度之间的间隙
 *
 *输出最小夹角（360度减去最大间隙）
 *时间复杂度O(n log n)，主要是排序的开销
 */
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define pi acos(-1.)
#define N 100010
using namespace std;


int main() {
    fast;
    int n; cin>>n; db a, b, ang[N];
    for (int i = 0; i < n; ++i) {
        cin>>a>>b;
        ang[i] = atan(b / a) / pi * 180;
        if (ang[i] < 0) ang[i] += 180;
        if (b < 0 || a < 0 && b == 0) ang[i] += 180;
    }
    sort(ang, ang + n, [](const db x, const db y) {
        return x > y;
    });
    db ans = 360 - ang[0] + ang[n-1];
    for (int i = 0; i < n - 1; ++i)
        ans = max(ans, ang[i] - ang[i+1]);
    cout << fixed << setprecision(8) << 360 - ans << '\n';
    return 0;
}