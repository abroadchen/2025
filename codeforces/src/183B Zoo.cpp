//
// Created by Psy.C on 2025/12/1.
//
/*
 *x和y，用于存储线段端点的坐标
 *ans，用于记录每个x坐标上经过的线段最大数量
 *
 *如果两条线段的y坐标不完全相同（斜率可能存在）
 *检查交点x坐标的分子是否能被分母整除（确保交点是整数坐标）
 *计算两条线段延长线在x轴上的交点横坐标
 *
*检查其他线段是否也经过这个交点
使用向量叉积判断三点共线的公式
如果共线则cur计数增加
 *更新位置t处的最大线段数
 *
*当y[i] == y[j]时，两条线段平行于x轴
交点就是它们的x坐标（这里简化处理）
 *统计经过同一x坐标的平行线段数量
 *
 *时间复杂度为O(m³)，空间复杂度为O(n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 255
#define M 1000005
using namespace std;

ll x[N], y[N];
int ans[M];

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> x[i] >> y[i];
    for (int i = 1; i <= n; ++i) ans[i] = 1;//至少有1条线段

    for (int i = 0; i < m; ++i) for (int j = i + 1; j < m; ++j) {
        ll t = 0;
        if (y[i] != y[j]) {
            if (((x[i]-x[j])*y[i])%(y[i]-y[j]) == 0) {
                t = x[i] - (((x[i]-x[j])*y[i])/(y[i]-y[j]));
                if (t >= 1 && t <= n) {//检查交点是否在有效范围内[1,n]
                    int cur = 2;//初始化当前交点处的线段数为2（线段i和j）
                    for (int k = j + 1; k < m; ++k) {
                        if (((y[i]-y[j])*(x[i]-x[k])) ==
                            ((y[i]-y[k])*(x[i]-x[j]))) cur++;
                    }
                    ans[t] = max(ans[t], cur);
                }
            }
        } else {
            t = x[i];
            if (t >= 1 && t <= n) {
                int cur = 1;
                for (int k = i + 1; k < m; ++k) {
                    if (x[k] == t) cur++;
                }
                ans[t] = max(ans[t], cur);
            }
        }
    }
    ll sum = 0;
    for (int i = 1; i <= n; ++i) sum += ans[i];
    cout << sum << '\n';
    return 0;
}