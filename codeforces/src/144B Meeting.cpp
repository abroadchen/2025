//
// Created by Psy.C on 2025/11/21.
//

#include <cstdio>
#include <set>
#include <vector>
using namespace std;

typedef pair<int, int> ii;//示坐标点
//判断点(x1,y1)是否在以(x2,y2)为圆心、r为半径的圆内或圆上
bool ok(int x1, int y1, int x2, int y2, int r) {
    if ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) <= r*r) return 1;
    return 0;
}

int main() {
    int xa, ya, xb, yb; scanf("%d %d %d %d", &xa, &ya, &xb, &yb);//矩形两个对角顶点的坐标
    int xl, xr, yl, yr;//矩形的边界坐标
    if (xa < xb) { xl = xa; xr = xb; } else { xl = xb; xr = xa; }
    if (ya < yb) { yl = ya; yr = yb; } else { yl = yb; yr = ya; }
    set<ii> c; set<ii>::iterator it;//存储矩形边界上的所有格点
    for (int i = yl; i <= yr; ++i) { c.insert({xl, i}); }//左边
    for (int i = yl; i <= yr; ++i) { c.insert({xr, i}); }//右边
    for (int i = xl; i <= xr; ++i) { c.insert({i, yl}); }//下边
    for (int i = xl; i <= xr; ++i) { c.insert({i, yr}); }//上边
    vector<ii> r; vector<int> rr;//圆心坐标 圆的半径
    int x; scanf("%d", &x);//圆的个数
    for (int i = 0; i < x; ++i) {
        int xt, yt, t; scanf("%d %d %d", &xt, &yt, &t);
        r.emplace_back(xt, yt);//存储圆心
        rr.push_back(t);//存储半径
    }
    for (int i = 0; i < x; ++i) {//对于每个圆，移除被它覆盖的边界点
        it = c.begin();
        while (it != c.end()) {
            if (ok(it->first,it->second,r[i].first, r[i].second, rr[i])) {
                c.erase(it);//从集合中删除该点
                it = c.begin();//重新从集合开头开始遍历
            } else ++it;//继续下一个点
        }
    }
    printf("%d\n", (int)c.size());//未被任何圆覆盖的边界点数量
    return 0;
}