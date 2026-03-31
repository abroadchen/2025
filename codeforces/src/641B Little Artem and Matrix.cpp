//
// Created by Psy.C on 2026/3/31.
//
/**
type：操作类型（1, 2, 3）
r, c：行号、列号
x：值
n, m：矩阵的行数和列数
Q：操作数量
a[N][N]：存储矩阵数据
操作1：type=1，读入行号 r
操作2：type=2，读入列号 c
操作3：type=3，读入位置 (r,c) 和值 x

操作1（行循环左移）
将第 r 行的所有元素向左循环移动一位
a[r][1] 移到 a[r][m]
操作2（列循环上移)
将第 c 列的所有元素向上循环移动一位
a[1][c] 移到 a[n][c]
操作3（赋值）
将位置 (r,c) 设置为值 x
时间复杂度：O(Q×max(n,m))，空间复杂度：O(n×m)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105, M = 1e5+5;
struct node { int type, r, c, x; } q[M];
int n, m, Q, a[N][N];
int main() {
    while(~scanf("%d%d%d",&n,&m,&Q)) {
        for(int i=1;i<=Q;i++) {
            scanf("%d",&q[i].type);
            if(q[i].type==1)scanf("%d",&q[i].r);
            else if(q[i].type==2)scanf("%d",&q[i].c);
            else scanf("%d%d%d",&q[i].r,&q[i].c,&q[i].x);
        }
        memset(a,0,sizeof(a));
        for(int i=Q;i>=1;i--) {
            int type=q[i].type,r=q[i].r,c=q[i].c,x=q[i].x;
            if(type==1)
                for(int j=m;j>1;j--)swap(a[r][j],a[r][j-1]);
            else if(type==2)
                for(int i=n;i>1;i--)swap(a[i][c],a[i-1][c]);
            else a[r][c]=x;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                printf("%d%c",a[i][j],j==m?'\n':' ');
    }
    return 0;
}