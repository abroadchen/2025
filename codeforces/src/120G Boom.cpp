//
// Created by Psy.C on 2025/11/16.
//
/*
*N = 104：最大容量
n：服务窗口数量
t：每个窗口的服务时间
i, j：循环变量
a[N][4]：每个窗口的参数数组
m：任务数量
c[N]：每个任务的需求量
k：当前窗口剩余服务能力
l：临时变量
d[N][N]：每个任务在各窗口的已服务量
b[N][32]：任务名称
q：任务队列
z[N]：记录每个窗口处理的任务
 *
*读取窗口数n和服务时间t
读取每个窗口的4个参数存储在a[i][0..3]中
*读取任务数m
读取m个任务的名称和需求量，同时将任务编号加入队列
 *
*外层循环：
i=0：当前窗口索引（0到2n-1，因为每个窗口有两个阶段）
!q.empty()：队列非空时继续
i=(i+1)%(n<<1)：循环遍历所有窗口阶段
内层循环：
k=t：当前窗口阶段的剩余服务能力初始化为t
k&&!q.empty()：还有服务能力且队列非空时继续
处理逻辑：
j=q.front(), q.pop()：取出队首任务
计算该任务还需要的服务量：
*c[j]：任务j的总需求
d[i%n][j]：任务j在窗口i%n已获得的服务
后面两项是窗口参数调整
判断服务能力：
如果k < l：服务能力不足
重新将任务放回队列：q.push(j)
更新已服务量：d[i%n][j]+=k
清空服务能力：k=0
如果k >= l：服务能力足够
记录该窗口处理了此任务：z[i%n].push_back(j)
扣除使用的服务能力：k-=l
 *
*对每个窗口i：
输出该窗口处理的任务数
输出该窗口处理的所有任务名称
 *
 *O(总服务时间 × 队列长度)
 *
 *scanf("%d", a[i]+0) → scanf("%d", &a[i][0])
 *z[i][j]：第i个窗口处理的第j个任务的编号
 *
 */
#include <cstdio>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 104;
int n, t, i, j, a[N][4],
m, c[N], k, l, d[N][N];
char b[N][32];//每个任务名最多31个字符
queue<int> q;
vector<int> z[N];

int main() {
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    for (scanf("%d%d",&n,&t);i!=n;++i) for (j=0;j!=4;scanf("%d", a[i]+j++));
    for (scanf("%d",&m),i=0; i!=m; scanf("%s%d", b[i], c + i), q.push(i++));
    for (i=0;!q.empty();i=(i+1)%(n<<1)) for (k=t;k&&!q.empty(); j=q.front(),
        q.pop(), l = max(1, c[j] - d[i%n][j] - a[i%n][i<n?0:1] - a[i%n][i<n?3:2]),
        k<l ? (q.push(j), d[i%n][j]+=k, k=0) : (z[i%n].push_back(j), k-=l));
    for (i = 0; i != n; puts(""), ++i) for (printf("%d", z[i].size()), j=0;
        j != z[i].size(); printf(" %s", b[z[i][j++]]));
    return 0;
}