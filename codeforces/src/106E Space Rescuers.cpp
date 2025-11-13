//
// Created by Psy.C on 2025/11/13.
//
/*
*offset：步长，初始为1
迭代M次：
找到离当前点s最远的点
计算从s到最远点的方向向量
沿该方向移动offset距离
衰减步长：offset *= K
 */
#include <cstdio>
using namespace std;

const int N = 105, M = 20000;
const double K = 0.997;
int n;
struct Node { double x, y, z; } p[N];


double dist(Node a, Node b) {
    double x = a.x - b.x,
    y = a.y - b.y,
    z = a.z - b.z;
    return x * x + y * y + z * z;
}


int find(Node x) {//找到离点x最远的点的索引
    double res(-1); int id = -1;
    for (int i = 0; i < n; ++i) {
        double d = dist(x, p[i]);
        if (d > res) { res = d; id = i; }
    }
    return id;
}

void solve() {
    Node s;
    s.x = s.y = s.z = 1.;//初始化起始点s为(1, 1, 1)
    double offset = 1;
    for (int i = 0; i < M; ++i) {
        int id = find(s);
        double dx = p[id].x - s.x,
        dy = p[id].y - s.y,
        dz = p[id].z - s.z;
        s.x += dx * offset;
        s.y += dy * offset;
        s.z += dz * offset;
        offset *= K;
    }
    printf("%.12lf %.12lf %.12lf\n", s.x, s.y, s.z);
}


int main() {
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) scanf("%lf%lf%lf",&p[i].x, &p[i].y, &p[i].z);
    solve();
    return 0;
}