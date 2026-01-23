//
// Created by Psy.C on 2026/1/22.
//
/**
* n, m: 网格的行数和列数
dp[N][N]: 记忆化搜索数组，dp[x][y]表示从(x,y)开始能搜索到的最大"DIMA"序列长度
*s[N][N]: 存储输入网格的字符数组
dir: 方向字符串"DMIA"，用于循环查找
 *vis[N][N]: 访问标记数组，用于检测循环
*xx[4]: 四个方向的x偏移量（上、下、左、右）
yy[4]: 四个方向的y偏移量（上、下、左、右）
 *
 *x,y是当前位置，idx是期望的字符索引
 *如果已经计算过，直接返回结果
 *将当前点的dp值暂时设为0，防止无限递归
 *ans存储从当前点能到达的最大长度
*循环遍历四个方向
dx, dy: 计算相邻位置坐标
*边界和条件检查:
坐标在网格范围内
相邻字符是期望的字符（dir[idx%4]）
 *如果相邻点已被访问，说明存在循环，返回无穷大
 *标记相邻点为已访问
 *搜索相邻点，期望字符索引+1，更新最大值
 *回溯时取消相邻点的访问标记
 * 当前点的结果是ans+1（包含当前点）
 *
 *
 *ans: 存储全局最大值
*双重循环: 遍历整个网格
条件: 只对字符为'D'且未计算过的点进行DFS
*标记起始点为已访问
从(i,j)开始搜索，期望字符索引为1（对应'I'）
更新全局最大值
取消起始点访问标记
 *
 *如果最大长度除以4为0，说明没有完整的"DIMA"序列
 *如果结果为无穷大，说明存在循环
 *输出完整"DIMA"序列的数量
 *
 *
 */
#include <iostream>
#include <cstring>
using namespace std;
const int N = 1010,INF = 0x3f3f3f3f;
int n,m,dp[N][N];//以x,y为起点能搜到的最大dima序列长度
char s[N][N],dir[N/10] = "DIMA";
bool vis[N][N];
int xx[4] = {-1,1,0,0},yy[4] = {0,0,-1,1};
int dfs(int x,int y,int idx)
{
    if(dp[x][y]!=-1) return dp[x][y];
    dp[x][y] = 0;
    int ans = 0;
    for(int i=0;i<4;i++)
    {
        int dx = x+xx[i],dy = y+yy[i];
        if(dx>0&&dx<=n&&dy>0&&dy<=m&&s[dx][dy]==dir[idx%4])
        {
            if(vis[dx][dy]) return INF;
            vis[dx][dy] = 1;
            ans = max(dfs(dx,dy,idx+1),ans);
            vis[dx][dy] = 0;
        }
    }
    return dp[x][y] = ans+1;
}
void solve()
{
    int ans = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(s[i][j]=='D'&&dp[i][j]==-1)
            {
                vis[i][j] = 1;
                ans = max(dfs(i,j,1),ans);
                vis[i][j] = 0;
            }
    if(ans/4==0) puts("Poor Dima!");
    else if(ans>=INF) puts("Poor Inna!");
    else printf("%d\n",ans/4);
}
int main()
{
    scanf("%d%d",&n,&m);
    memset(dp,-1,sizeof dp);
    for(int i=1;i<=n;i++) scanf("%s",s[i]+1);
    solve();
    return 0;
}