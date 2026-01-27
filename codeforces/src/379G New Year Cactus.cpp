//
// Created by Psy.C on 2026/1/25.
//
/**
*n,m: 节点数和边数
tt: 时间戳或新节点编号
f[N]: 父节点数组
dfn[N]: DFS序
low[N]: Tarjan算法low值
dt: 时间戳
dp[N][N][4]: DP数组
sz[N]: 子树大小
 *
 *初始化Ed为x的头边，v为第一条边的目标节点
 *当Ed非0时继续
 *更新v为下一条边的目标节点
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;//初始化目标变量 读取第一个字符
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;//直到读到数字字符
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);//读取连续的数字字符
	f?x=-x:x;//如果f为1，x取负；否则x不变
}
//可变参数包，接受0个或多个类型
///先读取x，再递归读取剩余参数
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
template<int N,int M>struct Edge
{
	//边结构
	struct edge{int to,nxt;}e[M<<1];int et,head[N];//边总数
	//添加从x到y的单向边 下一条边指向前一条 更新x的头指针
	inline void Adde(int x,int y) {e[++et]=(edge){y,head[x]},head[x]=et;}
	//同时添加x→y和y→x两条边
	inline void adde(int x,int y) {Adde(x,y),Adde(y,x);}
	inline void clear() {et=0,memset(head,0,sizeof(head));}
	//遍历节点x的所有邻接点v
#define Go(A,x,v) for(int Ed=A.head[x],v=A.e[Ed].to;Ed;v=A.e[Ed=A.e[Ed].nxt].to)
};
Edge<2505,5005>E;//原图
Edge<5005,5005>Tr;//缩点后的树
const int N=3755;int n,m,tt,f[N],dfn[N],low[N],dt,dp[N][N][4],sz[N];
inline void tarjan(int x,int fa)
{
	f[x]=fa,dfn[x]=low[x]=++dt;//值为当前时间戳
	Go(E,x,y)
	{
		//如果y未访问，递归访问y 更新low值
		if(!dfn[y]) tarjan(y,x),low[x]=min(low[x],low[y]);
		else if(y!=fa) low[x]=min(low[x],dfn[y]);//返祖边
		if(low[y]>dfn[x]) Tr.adde(x,y);//桥边，添加到缩点树
	}
	Go(E,x,y) if(f[y]!=x&&dfn[y]>dfn[x])
	{
		//找到环，创建新的虚拟节点tt
		tt++,Tr.adde(tt,x);//将虚拟节点连接到x
		//沿父节点路径收集环上所有节点 当u=x时为0
		for(int u=y;u^x;u=f[u]) Tr.adde(tt,u);//将虚拟节点连接到环上所有节点
	}
}
inline void chkmx(int &a,int b) {a=max(a,b);}
int debug[N][4],tmp[N][4];
inline void solve(int x,int fa)
{//dp k 个 1 点最多有几个 2 点
	Go(Tr,x,y) if(y!=fa) solve(y,x);//递归处理子节点
	if(x<=n)//原图节点（不是虚拟节点）
	{
		//dp[x][0][0]=0
		sz[x]=1,memset(dp[x],~0x3f,sizeof(dp[x])),memset(dp[x][0],0,sizeof(dp[x][0]));
		Go(Tr,x,y) if(y!=fa)
		{
			int od=sz[x];sz[x]+=sz[y];//更新子树大小
			for(int i=0;i<=od;i++) memcpy(debug[i],dp[x][i],sizeof(debug[i]));//备份当前状态
			for(int i=od;i>=0;i--) for(int a=3;~a;a--)//遍历当前节点状态
				for(int j=sz[y];j>=0;j--) for(int b=3;~b;b--)//遍历子节点状态
					chkmx(dp[x][i+j][a|b],debug[i][a]+dp[y][j][b]);
//printf("f**k %d : ",x);for(int i=0;i<=sz[x];i++) printf("<%d,%d,%d,%d>%c",dp[x][i][0],dp[x][i][1],dp[x][i][2],dp[x][i][3],i==sz[x]?'\n':' ');
		}
		for(int i=0;i<=sz[x];i++) memcpy(debug[i],dp[x][i],sizeof(debug[i])),memset(dp[x][i],~0x3f,sizeof(dp[x][i]));
		for(int i=0;i<=sz[x];i++)//内部状态转换操作
		{
			for(int a=0;a<4;a++) if(i+(a==1)<=sz[x]) chkmx(dp[x][i+(a==1)][a],debug[i][0]+(a==2));
			//i不等于sz[x]时
			chkmx(dp[x][i][0],debug[i][1]);if(i^sz[x]) chkmx(dp[x][i+1][1],debug[i][1]);
			chkmx(dp[x][i][0],debug[i][2]);chkmx(dp[x][i][2],debug[i][2]+1);
			chkmx(dp[x][i][0],debug[i][3]);
		}
	}else//处理虚拟节点（环缩点）
	{
		Go(Tr,x,y) if(y!=fa) sz[x]+=sz[y];// 累加子树大小
		memset(dp[x],~0x3f,sizeof(dp[x]));
		for(int bit=0;bit<3;bit++)//遍历三种状态
		{
			char fg=0;int Sz=1;memset(tmp,~0x3f,sizeof(tmp));
			Go(Tr,x,y) if(y!=fa)
			{
				if(!fg)//第一次处理，直接复制
				{
					for(int i=0;i<=sz[y];i++) tmp[i][bit]=dp[y][i][bit];
					Sz+=sz[y],fg=1;continue;
				}
				else
				{//合并状态
					for(int i=0;i<=Sz;i++) memcpy(debug[i],tmp[i],sizeof(debug[i]));
					for(int i=Sz;i>=0;i--) for(int j=sz[y];j>=0;j--)
					{
						for(int a=0;a<3;a++) chkmx(tmp[i+j][0],debug[i][a]+dp[y][j][0]);
						chkmx(tmp[i+j][1],max(debug[i][0],debug[i][1])+dp[y][j][1]);
						chkmx(tmp[i+j][2],max(debug[i][0],debug[i][2])+dp[y][j][2]);
					}
					Sz+=sz[y];
				}
			}
//printf("f**k %d : ",x);for(int i=0;i<=sz[x];i++) printf("<%d,%d,%d,%d>%c",tmp[i][0],tmp[i][1],tmp[i][2],tmp[i][3],i==sz[x]?'\n':' ');
			for(int i=0;i<=sz[x];i++)//将临时结果转移到最终DP数组
			{
				chkmx(dp[x][i][bit],tmp[i][0]);
				chkmx(dp[x][i][bit|1],tmp[i][1]);//状态合并
				chkmx(dp[x][i][bit|2],tmp[i][2]);
			}
		}
	}
//printf("res %d : ",x);for(int i=0;i<=sz[x];i++) printf("<%d,%d,%d,%d>%c",dp[x][i][0],dp[x][i][1],dp[x][i][2],dp[x][i][3],i==sz[x]?'\n':' ');
}
int main()
{
	read(n,m);for(int i=1,x,y;i<=m;i++) read(x,y),E.adde(x,y);
	tt=n,tarjan(1,0),solve(1,0);//虚拟节点起始编号
	//取四个状态的最大值
	for(int i=0;i<=n;i++) printf("%d%c",max(max(dp[1][i][0],dp[1][i][1]),max(dp[1][i][2],dp[1][i][3])),i==n?'\n':' ');
	return 0;
}