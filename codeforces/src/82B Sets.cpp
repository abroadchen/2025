//
// Created by Psy.C on 2025/11/6.
//
/*
*n 存储节点数
a[N] 一维数组用于临时存储输入数据
b[N][N] 二维数组用于记录节点之间的连接关系（边的数量）
f[N] 布尔数组标记哪些节点存在
v[N] 布尔数组用于标记节点是否已被访问过
 *
 *n*(n-1)/2次，这个数值代表完全图中边的数量
 *读取当前边关联的节点数m，然后读取这m个节点编号存入数组a
 *
 *
特殊情况处理：当只有两个节点时，直接输出结果并格式化打印
 *标记节点a[j]存在
 *更新节点间的连接计数，在矩阵b中增加对应位置的值
 *
 */
#include <cstdio>
using namespace std;

const int N = 202;
int n, i, m, j, a[N], k, b[N][N];
bool f[N], v[N];


int main() {
    scanf("%d", &n);
    for (i = 0; i < n*(n-1)/2; ++i) {
        scanf("%d", &m);
        for (j = 0; j < m; ++j) {
            scanf("%d", &a[j]);
            if (n == 2) {
                if (j == 0) printf("1 %d\n", a[j]);
                else if (j == 1) printf("%d %d", m - 1, a[j]);
                else printf(" %d", a[j]);
            }
            f[a[j]] = true;
            for (k = 0; k < j; ++k) {
                b[a[k]][a[j]]++;
                b[a[j]][a[k]]++;
            }
        }
    }
    if (n == 2) return 0;
    for (i = 1; i <= N - 2; ++i) {
        if (f[i] && !v[i]) {
            for (m = j = 1; j <= N - 2; ++j) if (b[i][j] == n - 1) m++;
            printf("%d %d", m, i); v[i] = 1;
            for (j = 1; j <= N - 2; ++j) if (b[i][j] == n - 1) {
                printf(" %d", j);
                v[j] = 1;
            }
            puts("");
        }
    }
    return 0;
}