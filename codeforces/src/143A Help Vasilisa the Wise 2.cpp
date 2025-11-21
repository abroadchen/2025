//
// Created by Psy.C on 2025/11/21.
//
/*
 *r1,r2代表两行的和，c1,c2代表两列的和，d1,d2代表两个对角线的和
* // 假设格子布局为：
    // x y
    // z w
    //
    // 根据约束条件建立方程组并求解：
    // x + y = r1  (第一行和)
    // z + w = r2  (第二行和)
    // x + z = c1  (第一列和)
    // y + w = c2  (第二列和)
    // x + w = d1  (主对角线和)
    // y + z = d2  (副对角线和)
 *
 *每个数字必须在1-9范围内且互不相同
 */
#include <cstdio>
using namespace std;

int main() {
    int r1, r2, c1, c2, d1, d2;
    scanf("%d %d\n%d %d\n%d %d\n", &r1, &r2, &c1, &c2, &d1, &d2);
    int x = (r1+c1-d2) % 2 == 0 ? (r1+c1-d2)/2 : -1,
    y = (r1+c2-d1) % 2 == 0 ? (r1+c2-d1)/2 : -1,
    z = (r2+c1-d1) % 2 ==0 ? (r2+c1-d1)/2 : -1,
    w = (r2+c2-d2) % 2 ==0 ? (r2+c2-d2)/2 : -1;
    if (x < 1 || y < 1 || z < 1 || w < 1 || x > 9 || y > 9 || z > 9 || w > 9 ||
        x == y || x == z || x == w || y == z || y == w || z == w) puts("-1");
    else printf("%d %d\n%d %d\n", x, y, z, w);
    return 0;
}