/**
*n：数组长度
m：操作次数
a[100010]：存储输入数组
f[555][22][2]：用于分块处理的DP数组，存储每个块内选择j个区间且最后一个元素是否被选择的最大值
g[555][22][2]：另一个DP数组，可能存储从块开头开始的子问题解
h[22][2]：临时数组，用于DP过程中的状态转移
e[2][22][2]：查询过程中的临时DP数组
block：分块大小
u[100010]：记录每个位置属于哪个块
 *f[t][i][0/1]表示在第t个块中选择i个区间，[0]表示最后元素未选，[1]表示最后元素已选
*遍历块内的每个元素，更新f数组
h数组保存上一次的状态
f[t][u][0]：选择u个区间，当前位置i被选择，值为之前状态的最大值加上a[i]
f[t][u][1]：选择u个区间，当前位置i不被选择，取决于前一个位置的状态
 *将f[t][0][1]设置为极小值，表示0个区间且最后元素被选择是无效状态
 *
 *初始化和更新g数组，可能表示从块开始到当前位置的子问题解
 *设置无效状态
 *
 */
#include <cstdio>
#include <cstring>
#include <cmath>
#define Min(_A, _B) (_A < _B ? _A : _B)
#define Max(_A, _B) (_A > _B ? _A : _B)
#define R register
int n, m, a[100010], f[555][22][2], g[555][22][2], h[22][2], e[2][22][2];
int block, u[100010];
void Build(R int t)
{
    R int l = Max(t * block, 1), r = Min((t + 1) * block - 1, n);
    for(R int i = 0; i <= 20; ++i) f[t][i][0] = f[t][i][1] = 0;
    for(R int i = l; i <= r; ++i)
    {
        for(R int j = 0; j <= 20; ++j) h[j][0] = f[t][j][0], h[j][1] = f[t][j][1];
        for(R int u = 0; u <= 20; ++u)
        {
            f[t][u][0] = Max(h[u][0], h[u][1]) + a[i];
            if(u) f[t][u][1] = Max(h[u - 1][0], h[u][1]);
            else f[t][u][1] = h[u][1];
        }
    }
    f[t][0][1] = -1e9;
    for(R int j = 0; j <= 20; ++j) g[t][j][0] = g[t][j][1] = a[l];
    for(R int i = l + 1; i <= r; ++i)
    {
        for(R int j = 0; j <= 20; ++j) h[j][0] = g[t][j][0], h[j][1] = g[t][j][1];
        for(R int u = 0; u <= 20; ++u)
        {
            if(u) g[t][u][0] = Max(h[u][0], h[u][1]) + a[i];
            else g[t][u][0] = h[u][0] + a[i];
            if(u) g[t][u][1] = Max(h[u - 1][0], h[u][1]);
            else g[t][u][1] = Max(h[u][1], h[u][0]);
        }
    }
    g[t][0][1] = -1e9;
}
int main()
{
    scanf("%d", &n);
    for(R int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    block = sqrt(n);
    for(R int i = 1; i <= n; ++i) u[i] = i / block;
    for(R int i = 0; i <= u[n]; ++i) Build(i);
    scanf("%d", &m);
    while(m--)
    {
        R bool opt; scanf("%d", &opt);
        if(opt == 0)
        {
            R int pos, val; scanf("%d %d", &pos, &val);
            a[pos] = val;//更新位置pos的值为val，并重新构建该位置所属的块
            Build(u[pos]);
        }
        else
        {//在区间[l,r]中选择最多k个不相交子区间使和最大
            R int l, r, k; scanf("%d %d %d", &l, &r, &k);
            R int d = 0;//滚动数组的索引
            for(R int i = 0; i <= k; ++i) e[d][i][0] = e[d][i][1] = 0;
            for(R int i = l; u[l] == u[i] && i <= r; ++i)
            {//处理左端不完整的块
                d ^= 1;
                for(R int u = 0; u <= k; ++u)
                {
                    e[d][u][0] = Max(e[d ^ 1][u][0], e[d ^ 1][u][1]) + a[i];
                    if(u) e[d][u][1] = Max(e[d ^ 1][u - 1][0], e[d ^ 1][u][1]);
                    else e[d][u][1] = e[d ^ 1][u][1];
                }
            }
            for(R int i = u[l] + 1; i < u[r]; ++i)
            {//处理中间完整的块
                d ^= 1;
                //当前块选择的区间数j
                for(R int j = 0; j <= k; ++j) e[d][j][0] = e[d][j][1] = 0;
                for(R int j = 0; j <= k; ++j)
                {
                    for(R int l = 0; l + j <= k; ++l)//之前已选择的区间数l
                    {
                        e[d][l + j][0] = Max(e[d][l + j][0], e[d ^ 1][l][1] + f[i][j][0]);
                        e[d][l + j][1] = Max(e[d][l + j][1], e[d ^ 1][l][1] + f[i][j][1]);
                        e[d][l + j + 1][0] = Max(e[d][l + j + 1][0], e[d ^ 1][l][0] + f[i][j][0]);
                        e[d][l + j + 1][1] = Max(e[d][l + j + 1][1], e[d ^ 1][l][0] + f[i][j][1]);
                        e[d][l + j][0] = Max(e[d][l + j][0], e[d ^ 1][l][0] + g[i][j][0]);
                        e[d][l + j][1] = Max(e[d][l + j][1], e[d ^ 1][l][0] + g[i][j][1]);
                    }
                    e[d][j][1] = Max(e[d][j][1], e[d ^ 1][j][1]);
                    if(j) e[d][j][1] = Max(e[d][j][1], e[d ^ 1][j - 1][0]);
                }
            }
            if(u[l] != u[r])
            {//处理右端不完整的块（如果存在）
                for(R int i = u[r] * block; i <= r; ++i)
                {
                    d ^= 1;
                    for(R int u = 0; u <= k; ++u)
                    {
                        e[d][u][0] = Max(e[d ^ 1][u][0], e[d ^ 1][u][1]) + a[i];
                        if(u) e[d][u][1] = Max(e[d ^ 1][u - 1][0], e[d ^ 1][u][1]);
                        else e[d][u][1] = e[d ^ 1][u][1];
                    }
                }
            }
            R int Ans = 0;
            for(R int i = 0; i < k; ++i) Ans = Max(Ans, Max(e[d][i][0], e[d][i][1]));
            Ans = Max(e[d][k][1], Ans);
            printf("%d\n", Ans);
        }
    }
    return 0;
}