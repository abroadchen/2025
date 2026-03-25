//
// Created by Psy.C on 2026/3/25.
//
/**
线段树数组：sx, sy存储笛卡尔坐标，sa存储角度
单次修改：O(log n)
总体：O(m log n)
 */
#include <bits/stdc++.h>
#define pi (2*acos(0.))
using namespace std;
constexpr int N = 3e5+5;

double sx[N<<2], sy[N<<2], sa[N<<2];
void modify(int v, int l, int r, int pos, int dx, double da) {
    if (l + 1 == r) {
        //获取当前点的极坐标
        double R = sqrt(sx[v] * sx[v] + sy[v] * sy[v]);//当前半径
        double A = atan2(sy[v], sx[v]);//当前角度
        R += dx;//修改半径
        A += da;//修改角度
        //转换回笛卡尔坐标
        sx[v] = R * cos(A);
        sy[v] = R * sin(A);
        sa[v] = A;//更新角度
        return;
    }
    //递归修改子节点
    int mid = (l + r + 1) / 2;
    if (pos < mid) modify(2 * v + 1, l, mid, pos, dx, da);
    else modify(2 * v + 2, mid, r, pos, dx, da);

    double R = sqrt(sx[2 * v + 2] * sx[2 * v + 2] + sy[2 * v + 2] * sy[2 * v + 2]);
    double A = atan2(sy[2 * v + 2], sx[2 * v + 2]);
    //父节点坐标 = 左子节点坐标 + 右子节点坐标经过旋转
    sx[v] = sx[2 * v + 1] + R * cos(A + sa[2 * v + 1]);
    sy[v] = sy[2 * v + 1] + R * sin(A + sa[2 * v + 1]);
    sa[v] = sa[2 * v + 1] + sa[2 * v + 2];//左子节点角度 + 右子节点角度
}

int n, m;
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) {//初始化：每个点半径为1，角度为0
        modify(0, 0, n, i, 1, 0);
    }
    while(m--) {
        int tp, num, add;
        scanf("%d%d%d", &tp, &num, &add);
        if (tp == 1) {//在位置num-1处增加长度add
            modify(0, 0, n, num - 1, add, 0);
        } else {//将角度从度数转换为弧度，并进行相应调整
            modify(0, 0, n, num - 1, 0, 2 * pi - add / 360. * 2. * pi);
        }
        printf("%0.9lf %0.9lf\n", sx[0], sy[0]);//整个系统的终点坐标
    }
    return 0;
}