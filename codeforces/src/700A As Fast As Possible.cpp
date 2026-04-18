//
// Created by Psy.C on 2026/4/17.
//
/**
l: 总路程长度
v1: 步行速度
v2: 车辆速度
n: 需要运输的人数
k: 车辆容量（一次最多载k人）
t2 = (l - v1*t)/(v2-v1): 这里计算的是车辆去接下一组人的时间
t3 = (v2-v1)*t2/(v1+v2): 车辆返回接下一组人的时间
计算需要的运输趟数：(n+k-1)/k 是向上取整的写法，确保所有人都被运送
计算总的运输时间：t2*p是车辆前进的总时间，t3*(p-1)是车辆返回的总时间（最后一趟不需要返回）

x = l/v2：理想情况下的最小时间（全部坐车）
y = l/v1：最坏情况下的最大时间（全部步行）
如果在mid时间内能完成任务，说明答案可能是更小的值，所以y = mid
否则答案应该更大，所以x = mid
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

double l, v1, v2;
int n, k;
bool check(double t) {//在时间t内是否能完成所有人的运输任务
    double t2 = (l - v1*t)/(v2-v1), t3 = (v2-v1)*t2/(v1+v2);
    int p = (n+k-1)/k;
    double ans = t2*p + t3*(p-1);
    if (ans <= t) return true;
    return false;
}


int main() {
    fast;
    cin >> n >> l >> v1 >> v2 >> k;
    double x = l/v2, y = l/v1;
    for (int i = 1; i <= 10000; ++i) {
        double mid = (x + y) / 2;
        if (check(mid)) y = mid; else x = mid;
    }
    printf("%.10f\n", y);
    return 0;
}