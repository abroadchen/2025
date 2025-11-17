//
// Created by Psy.C on 2025/11/17.
//
/*
*N = 160：常量，最大节点数
n：输入的边数
x(1)：变量x，初始值为1（表示需要的节点数）
a[N][N]：邻接矩阵，存储图的边
c[N]：每个节点的度数计数器
s(0)：边的编号计数器
 *
*构造图的边：
对于前n条边的需求
在节点i和节点j之间添加边（i < j ≤ x）
++c[i]和++c[j]：增加节点i和j的度数计数
++s：边的编号递增
在邻接矩阵中记录这条边


c[j]：节点j的度数计数器（已连接的边数）
++c[j]：先将c[j]自增1，然后返回新值
a[j][++c[j]]：访问二维数组a的第j行，第(c[j]+1)列
s：当前边的编号
整体含义：将边s记录到节点j的邻接表中

a[i][k] = e 表示节点i的第k条边是编号为e的边
在添加一条边时，只在一端使用++s，而在另一端使用s
c[i] 记录了已有的边数，c[i]+1就是新边的位置
 *
*输出邻接矩阵：
对每个节点i，输出其连接的边的编号
每行输出x-1个数字
 */
#include <cstdio>
using namespace std;

const int N = 160;
int n, x(1),
a[N][N], c[N], s(0);

int main() {
    for (scanf("%d", &n); x * (x + 1) / 2 <= n; ++x);
    printf("%d\n", x);
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= x; ++j) {
            a[i][++c[i]] = ++s;
            a[j][++c[j]] = s;
        }
    }
    for (int i = 1; i <= x; ++i) {
        for (int j = 1; j <= x - 1; ++j) printf("%d ", a[i][j]);
        printf("\n");
    }
    return 0;
}