//
// Created by Psy.C on 2025/11/12.
//
/*
 *函数ok判断向量(tx,ty)是否可以由向量(cx,cy)通过某种变换得到
 *定义垂直向量(dx,dy) = (cy, -cx)（向量(cx,cy)逆时针旋转90度）
 *特殊情况：如果(cx,cy)是零向量，只有当(tx,ty)也是零向量时才返回true
*解二元一次方程组求系数a和b：
a * (cx,cy) + b * (dx,dy) = (tx,ty)
这表示(tx,ty)是否可以由(cx,cy)和其垂直向量的线性组合表示
 *
 *点A(ax,ay)、点B(bx,by)、向量C(cx,cy)
*循环4次，每次将点A绕原点逆时针旋转90度：
计算向量AB：(bx-ax, by-ay)
调用ok函数判断向量AB是否可以由向量C变换得到
旋转变换：(x,y) → (-y,x)
如果任何一次旋转后满足条件，设置flag为true
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;
bool ok(ll tx, ll ty, ll cx, ll cy) {
    ll dx = cy, dy = -cx;
    if (cx == 0 && cy == 0) return tx == 0 && ty == 0;
    ll b = (tx * cy - cx * ty) / (dx * cy - cx * dy),
    a = (tx * dy - dx * ty) / (cx * dy - dx * cy);
    if (a * cx + b * dx != tx) return false;
    if (a * cy + b * dy != ty) return false;
    return true;
}

int main() {
    int ax, ay, bx, by, cx, cy;
    scanf("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &cx, &cy);
    bool flag = false;
    for (int i = 0; i < 4; ++i) {
        if (ok(bx - ax, by - ay, cx, cy)) flag = true;
        int tmp = ax; ax = -ay; ay = tmp;
    }
    printf("%s\n", flag ? "YES" : "NO");
    return 0;
}