//
// Created by Psy.C on 2026/4/13.
//
/**
(ax,ay), (bx,by), (tx,ty): 三个关键点的坐标
n: 点的数量
ma: 到A点的最小额外成本
mb: 到B点的最小额外成本
mab: 同时服务A和B的最小额外成本
sum: 总的基础成本

计算距离：
dt: 从T到点(x,y)的距离
da: 从A到点(x,y)比从T到点(x,y)多出的距离
db: 从B到点(x,y)比从T到点(x,y)多出的距离
更新总成本：
sum += dt*2: 每个点都要访问两次（T→点→T），所以加2*dt
更新最小额外成本：
mab: 更新同时服务A和B的最小额外成本
ma, mb: 更新单独服务A或B的最小额外成本

基础成本 + 最优额外成本

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr double inf = 1e18;

double get(int x, int y, int a, int b) {
    return sqrt(1.*(x-a)*(x-a)+1.*(y-b)*(y-b));
}

int ax, ay, bx, by, tx, ty, n;
double ma = inf, mb = inf, mab = inf, sum;
int main() {
    fast;
    cin >> ax >> ay >> bx >> by >> tx >> ty;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        double dt = get(tx, ty, x, y),
        da = get(ax, ay, x, y) - dt,
        db = get(bx, by, x, y) - dt;
        sum += dt*2;
        mab = min(mab, min(ma + db, mb + da));
        ma = min(ma, da), mb = min(mb, db);
    }
    printf("%.12f", sum + min(mab, min(ma, mb)));
    return 0;
}