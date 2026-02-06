//
// Created by Psy.C on 2026/2/6.
//
/**
n: 节点总数
cnt: 边计数器
tot: 当前处理节点数
mn: 最小值记录
rt: 当前重心
X,Y,K: 题目参数
Ki: K的逆元
ans: 答案

pw[]: K的幂次数组
pi[]: K逆元的幂次数组
v[]: 节点权值
in1[],in0[]: 入边统计数组 1满足条件的 0不满足条件的
out1[],out0[]: 出边统计数组
to[],nxt[],head[]: 链式前向星建图
vis[]: 访问标记
siz[]: 子树大小

DFS找树的重心（平衡点）
siz[x]: 以x为根的子树大小
tmp: 最大连通块大小
重心定义：删除该点后最大连通块最小

收集从当前节点出发的路径信息
s1: 从根到当前节点的加权和（K进制表示）
s2: 从当前节点到叶子的加权和
将相关信息存储到p和q数组中

计算通过当前节点的满足条件的路径数量
使用双指针算法统计满足等式的路径
flag: 正负标记，用于容斥原理
对p和q数组排序后进行匹配统计

点分治核心函数
calc(x,1,0,0,0): 计算通过当前重心的所有路径
calc(to[i],-1,1,v[x],0): 减去重复计算的部分（容斥原理）
递归处理子树的重心

读入参数，计算K的逆元
读入节点权值
预处理K的幂次和逆元的幂次
构建无向图
找到树的重心并开始点分治
计算每个节点的相关统计值
最后输出结果：总路径数减去不符合条件的路径数

 */
#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
#define maxn 100010
using namespace std;

int n,cnt,tot,mn,rt;
ll X,Y,K,Ki,ans;
ll pw[maxn],pi[maxn],v[maxn],in1[maxn],in0[maxn],out1[maxn],out0[maxn];
int to[maxn<<1],nxt[maxn<<1],head[maxn],vis[maxn],siz[maxn];
struct node
{
	ll x;
	int y;
	node() {}
	node(ll a,int b) {x=a,y=b;}
	bool operator < (const node &a) const {return x<a.x;}
}p[maxn],q[maxn];
inline int rd()
{
	char gc=getchar();	int ret=0;
	while(gc<'0'||gc>'9')	gc=getchar();
	while(gc>='0'&&gc<='9')	ret=ret*10+gc-'0',gc=getchar();
	return ret;
}
inline void add(int a,int b) {
	to[cnt]=b,nxt[cnt]=head[a],head[a]=cnt++;
}
inline ll pm(ll x,ll y) {
	ll z=1;
	while(y) {
		if(y&1)	z=z*x%Y;
		x=x*x%Y,y>>=1;
	}
	return z;
}
void getrt(int x,int fa) {
	int i,tmp=0;
	siz[x]=1;
	for(i=head[x];i!=-1;i=nxt[i])	if(!vis[to[i]]&&to[i]!=fa)	getrt(to[i],x),siz[x]+=siz[to[i]],tmp=max(tmp,siz[to[i]]);
	tmp=max(tmp,n-siz[x]);
	if(tmp<mn)	mn=tmp,rt=x;
}
void getp(int x,int fa,int dep,ll s1,ll s2) {
	s1=(s1*K+v[x])%Y,s2=(s2+v[x]*((!dep)?0:pw[dep-1]))%Y,dep++;
	p[++tot]=node((X-s1+Y)*pi[dep]%Y,x),q[tot]=node(s2,x);
	for(int i=head[x];i!=-1;i=nxt[i])	if(!vis[to[i]]&&to[i]!=fa)
		getp(to[i],x,dep,s1,s2);
}
void calc(int x,int flag,int dep,ll s1,ll s2) {
	int i,j,cnt;
	tot=0;
	//根到x的加权和 x到叶子的加权和
	s1=(s1*K+v[x])%Y,s2=(s2+v[x]*((!dep)?0:pw[dep-1]))%Y,dep++;
	//计算目标值并存储
	p[++tot]=node((X-s1+Y)*pi[dep]%Y,x),q[tot]=node(s2,x);
	for(i=head[x];i!=-1;i=nxt[i])	if(!vis[to[i]])	getp(to[i],x,dep,s1,s2);
	sort(p+1,p+tot+1),sort(q+1,q+tot+1);
	for(cnt=0,i=j=1;i<=tot;i++) {
		for(;j<=tot&&q[j].x<=p[i].x;j++) {
			if(j==1||q[j].x!=q[j-1].x)	cnt=0;//新值，重置计数
			cnt++;
		}
		if(j!=1&&q[j-1].x==p[i].x)	out1[p[i].y]+=cnt*flag;
	}
	for(cnt=0,i=j=1;i<=tot;i++) {
		for(;j<=tot&&p[j].x<=q[i].x;j++) {
			if(j==1||p[j].x!=p[j-1].x)	cnt=0;
			cnt++;
		}
		if(j!=1&&p[j-1].x==q[i].x)	in1[q[i].y]+=cnt*flag;
	}
}
void dfs(int x) {
	vis[x]=1;
	int i;
	calc(x,1,0,0,0);//通过x的所有路径（+1标记）
	for(i=head[x];i!=-1;i=nxt[i])	if(!vis[to[i]]) {
		calc(to[i],-1,1,v[x],0);//减去重复计算的部分（-1标记）
		tot=siz[to[i]],mn=1<<30,getrt(to[i],x),dfs(rt);
	}
}
int main() {
	n=rd(),Y=rd(),K=rd(),X=rd(),Ki=pm(K,Y-2);
	int i,a,b;
	memset(head,-1,sizeof(head));
	for(i=1;i<=n;i++)	v[i]=rd();//读入每个节点的权值
	for(i=pw[0]=pi[0]=1;i<=n;i++)	pw[i]=pw[i-1]*K%Y,pi[i]=pi[i-1]*Ki%Y;
	for(i=1;i<n;i++)	a=rd(),b=rd(),add(a,b),add(b,a);
	tot=n,mn=1<<30,getrt(1,0),dfs(rt);//找重心并开始点分治
	for(i=1;i<=n;i++) {
		in0[i]=n-in1[i],out0[i]=n-out1[i];//计算不满足条件的数量
		//累加不符合条件的路径数
		ans+=2*in1[i]*in0[i]+2*out1[i]*out0[i]+in0[i]*out1[i]+in1[i]*out0[i];
	}
	printf("%lld",1ll*n*n*n-ans/2);//总路径数 - 不符合条件路径数/2
	return 0;
}
