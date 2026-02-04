//
// Created by Psy.C on 2026/2/4.
//
/**
 * 存储圆形障碍物的坐标 (x,y) 和半径 r
*d：扫描圆的半径
l[], r[]：存储每个圆形在角度轴上产生的区间
*距离计算：dis = √(x² + y²) - 障碍物中心到原点距离
距离范围：[st, ed] - 哪些整数倍距离的圆可能与障碍物相交
角度计算：
theta = atan2(y, x) - 障碍物中心的角度
t = acos(...) - 通过余弦定理计算相交角度范围
t1 = theta - t, t2 = theta + t - 相交区间的角度范围
 *
*排序：将所有区间端点按角度排序
事件处理：
遇到左端点：覆盖数+1
遇到右端点：覆盖数-1
最值更新：记录最大覆盖数
 *
*cos(θ) = (dis² + x² - r²) / (2×dis×x)
dis：障碍物中心距离
x：扫描圆距离（d的倍数）
r：障碍物半径
计算相交角度范围
 *
*扫描线技术
将区间问题转化为事件序列
按时间（角度）顺序处理进入/离开事件
维护当前覆盖层数的最大值
 *
*预处理：O(n × (ed-st+1))，其中区间数量与距离有关
排序：O(M log M)，M为区间总数
扫描线：O(M)，M为区间总数
总体：O(M log M)
 */
#include <algorithm>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define db double
#define N 20005
#define pi acos(-1)
#define eps 1e-8
using namespace std;

struct node { db x, y, r; } a[N];

int main() {
    fast;
    int n, d; cin >> n >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y >> a[i].r;
    db l[N*20]{}, r[N*20]{};
    int res = 0, num = 0;//当前覆盖层数 已处理的角度区间数量
    for (int i = 1; i <= n; ++i) {
        //第i个圆形障碍物中心到原点的距离
        const db dis = sqrt(a[i].x * a[i].x + a[i].y * a[i].y);
        //st：起始距离（向上取整） ed：结束距离（向下取整）
        const int st = ceil((dis-a[i].r)/d), ed = floor((dis+a[i].r)/d);
        //第i个圆形中心相对于原点的角度
        db theta = atan2(a[i].y, a[i].x);//返回值在[-π, π]范围内
        if (theta < 0) theta += 2*pi;//角度为负，转换到[0, 2π]范围内
        for (int j = st; j <= ed; ++j) {//遍历可能相交的距离范围
            const int x = d*j;//当前扫描圆的半径：d的j倍
            //相交角度t  t1：相交区间的左边界角度 t2：相交区间的右边界角度
            const db t = acos((dis*dis+x*x-a[i].r*a[i].r)/(2*dis*x)),
            t1 = theta - t; db t2 = theta + t;
            if (t2 >= 2*pi) t2 -= 2*pi, res++;//右边界超过2π，将其调整到[0, 2π]范围内 增加跨越边界计数res
            l[++num] = t1; r[num] = t2;//将角度区间[t1, t2]存入数组 num自增，记录区间数量
        }
    }
    sort(l + 1, l + num + 1); sort(r + 1, r + num + 1);
    int ans = res;//初始化答案为跨越边界的区间数
    for (int i = 1, j = 1; i <= num;) {//遍历所有端点事件
        const db now = l[i];//获取当前处理的事件时间（角度）
        for (; i <= num && abs(l[i] - now) < eps; ++i) ++res;
        for (; j <= num && r[j] < now; ++j) --res;
        if (res > ans) ans = res;
    }
    cout << ans << '\n';
    return 0;
}