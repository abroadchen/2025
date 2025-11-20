//
// Created by Psy.C on 2025/11/20.
//
/*
*a[i][j]表示第i个人的第j个偏好选择
b[N]: 一维数组，存储某种排序或匹配结果
 *
 *如果第i个人在第j个偏好位置上是自己，则跳过
*在数组b中查找a[i][j]的位置
在查找过程中，如果发现有比a[i][j]更小且不等于i的元素，则提前退出
*如果成功找到a[i][j]在b中的位置（没有被中断）
输出该值，并根据是否是最后一行决定输出空格还是换行
跳出内层循环
 */
#include <cstdio>
#define rep(i,n) for(i=1;i<=(n);++i)
using namespace std;

const int N = 400;
int n, a[N][N], b[N];

int main() {
    scanf("%d",&n);
    int i, j, k;
    rep(i,n) rep(j,n) scanf("%d",&a[i][j]);
    rep(i,n) scanf("%d",&b[i]);
    rep(i,n) rep(j,n) {
        if (i == a[i][j]) continue;
        for (k = 1; b[k] != a[i][j]; ++k) {
            if (b[k] < a[i][j] && b[k] != i) break;
        }
        if (b[k] == a[i][j]) {
            printf("%d", a[i][j]);
            putchar(i == n ? '\n' : ' ');
            break;
        }
    }
    return 0;
}