//
// Created by Psy.C on 2025/9/24.
//

#include <cstdio>
using namespace std;
//判断两个点是否至少在某一个坐标轴方向上对齐
int main() {
    int x1, y1, z1, x2, y2, z2;//两组三维坐标点
    scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);
    puts(((x1 ^ x2) && (y1 ^ y2) && (z1 ^ z2)) ? "NO" : "YES");
    return 0;
}