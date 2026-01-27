//
// Created by Psy.C on 2026/1/27.
//
/**
* [0]: 到达(x,y,z)的步数
[1]: 移动类型（1,2,3分别对应x,y,z坐标变化）
[2]: 前驱坐标
 *maz[M][M]: 2维数组，存储地图信息
 *
*坐标(x,y,z)和步数(stp)
now: 当前节点
to: 目标节点
*qu: BFS使用的队列
n: 地图大小
 *
 *递归路径重建函数
 *如果到达起点(步数为0)，返回
*如果移动类型是1（x坐标变化）
递归访问前驱状态 (station[x][y][z][2], y, z)
输出移动信息：从 station[x][y][z][2] 移动到 x
 *类似的逻辑处理y坐标变化和z坐标变化的情况
 *
*外层循环：i从1到n，处理每一行
getchar(): 消耗换行符
内层循环：j从1到n，处理每一列
scanf("%c",&op): 读入字符
if(op=='*') maz[i][j]=0: 障碍物设为0
else maz[i][j]=op-'a'+1: 字符转为数字(1-26)
 *
 *
*条件：maz[now.x][i] == maz[now.y][now.z] 且目标状态未访问
创建新节点，将x坐标改为i
更新步数、移动类型(1)和前驱坐标
将新节点加入队列
 *类似逻辑，改变y坐标，移动类型为2
 *类似逻辑，改变z坐标，移动类型为3
 *
*寻找目标状态(1,2,3)的排列的最小步数
如果没有找到解，设为-1
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
#define M 71

int station[M][M][M][3],maz[M][M];
struct node
{
	int x,y,z,stp;
}now,to;
queue<node> qu;
int n;

void dfs(int x,int y,int z)
{
	//printf("%d %d %d %d %d %d\n",x,y,z,station[x][y][z][0],station[x][y][z][1],station[x][y][z][2]);
	if(station[x][y][z][0]==0) return ;
	if(station[x][y][z][1]==1)
	{
		dfs(station[x][y][z][2],y,z);
		printf("%d %d\n",station[x][y][z][2],x);
	}
	else if(station[x][y][z][1]==2)
	{
		dfs(x,station[x][y][z][2],z);
		printf("%d %d\n",station[x][y][z][2],y);
	}
	else if(station[x][y][z][1]==3)
	{
		dfs(x,y,station[x][y][z][2]);
		printf("%d %d\n",station[x][y][z][2],z);
	}
}

int main()
{
	int i,j,x,y,z;
	char op;
	scanf("%d",&n);
	scanf("%d%d%d",&now.x,&now.y,&now.z);
	now.stp=0;
	memset(station,-1,sizeof(station));
	station[now.x][now.y][now.z][0]=0;//起始点的步数为0
	for(i=1;i<=n;i++)
	{
		getchar();
		for(j=1;j<=n;j++)
		{
			scanf("%c",&op);
			if(op=='*') maz[i][j]=0;
			else maz[i][j]=op-'a'+1;
		}
	}
	while(!qu.empty()) qu.pop();//清空队列
	qu.push(now);//将起始节点加入队列
	while(!qu.empty())
	{
		now=qu.front();
		//printf("from %d %d %d\n",now.x,now.y,now.z);
		qu.pop();
		for(i=1;i<=n;i++)
		{
			if(i==now.x||i==now.y||i==now.z) continue;
			if(maz[now.x][i]==maz[now.y][now.z]&&station[i][now.y][now.z][0]==-1)
			{
				to=now;
				to.x=i;
				to.stp++;
				station[to.x][to.y][to.z][0]=to.stp;
				station[to.x][to.y][to.z][1]=1;
				station[to.x][to.y][to.z][2]=now.x;
				//printf("to %d %d %d\n",to.x,to.y,to.z);
				qu.push(to);
			}
			if(maz[now.y][i]==maz[now.x][now.z]&&station[now.x][i][now.z][0]==-1)
			{
				to=now;
				to.y=i;
				to.stp++;
				station[to.x][to.y][to.z][0]=to.stp;
				station[to.x][to.y][to.z][1]=2;
				station[to.x][to.y][to.z][2]=now.y;
				//printf("to %d %d %d\n",to.x,to.y,to.z);
				qu.push(to);
			}
			if(maz[now.z][i]==maz[now.x][now.y]&&station[now.x][now.y][i][0]==-1)
			{
				to=now;
				to.z=i;
				to.stp++;
				station[to.x][to.y][to.z][0]=to.stp;
				station[to.x][to.y][to.z][1]=3;
				station[to.x][to.y][to.z][2]=now.z;
				//printf("to %d %d %d\n",to.x,to.y,to.z);
				qu.push(to);
			}
		}
	}
	i=M*M*M;
	if(station[1][2][3][0]!=-1&&station[1][2][3][0]<i) i=station[1][2][3][0],x=1,y=2,z=3;
	if(station[1][3][2][0]!=-1&&station[1][3][2][0]<i) i=station[1][3][2][0],x=1,y=3,z=2;
	if(station[2][1][3][0]!=-1&&station[2][1][3][0]<i) i=station[2][1][3][0],x=2,y=1,z=3;
	if(station[2][3][1][0]!=-1&&station[2][3][1][0]<i) i=station[2][3][1][0],x=2,y=3,z=1;
	if(station[3][1][2][0]!=-1&&station[3][1][2][0]<i) i=station[3][1][2][0],x=3,y=1,z=2;
	if(station[3][2][1][0]!=-1&&station[3][2][1][0]<i) i=station[3][2][1][0],x=3,y=2,z=1;
	if(i==M*M*M) i=-1;
	printf("%d\n",i);
	if(i!=-1) dfs(x,y,z); //存在解，用DFS重建并输出路径
	return 0;
}