//
// Created by Psy.C on 2026/2/9.
//
/**
n,m,K 分别表示节点数、边数、步数
dg[N] 存储每个节点的度数
a[N][N] 存储邻接矩阵（边的权重）
cg[N] 标记节点是否为目标节点
rbt 目标节点总数，rb[N] 映射原节点到目标节点编号
gs[N][N+105] 高斯消元用的增广矩阵
 */
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=605;typedef long double ld;
int n,m,K,dg[N],a[N][N],cg[N],rbt,rb[N];ld gs[N][N+105];
struct mat
{
	ld a[105][105];
	inline ld* operator[](int x) {return a[x];}//返回第x行的指针
	//矩阵清零
	inline void operator!() {for(int i=0;i<=rbt;i++) for(int j=0;j<=rbt;j++) a[i][j]=0;}
	//先清零，然后对角线元素设为1
	inline void operator~() {!*this;for(int i=0;i<=rbt;i++) a[i][i]=1;}
	inline mat operator*(mat b)//矩阵乘法
	{
		mat r;!r;for(int k=0;k<=rbt;k++)
			for(int i=0;i<=rbt;i++) for(int j=0;j<=rbt;j++) r[i][j]+=a[i][k]*b[k][j];
		return r;
	}
	//矩阵快速幂
	inline mat operator^(int q) {mat r,x=*this;~r;for(;q;q>>=1,x=x*x) if(q&1) r=r*x;return r;}
}mt;
int main()
{
	read(n,m,K);
	for(int i=1;i<=n;i++) read(cg[i]);//标记每个节点是否为目标节点
	for(int i=1,x,y;i<=m;i++) read(x,y),a[x][y]++,a[y][x]++,dg[x]++,dg[y]++;
	for(int i=1;i<=n;i++) if(cg[i]) rb[i]=++rbt;//重新编号
	for(int i=1;i<=n;i++)//构建线性方程组的系数矩阵
	{//a[i][j]*1.0/dg[i] 计算从节点i转移到节点j的概率
		gs[i][i]=-1;for(int j=1;j<=n;j++)
			(cg[j]?gs[i][n+rb[j]]:gs[i][j])+=a[i][j]*1.0/dg[i];
	}
	//设置增广矩阵的约束行
	for(int i=1;i<=rbt;i++) gs[i+n][i+n+rbt]=1,gs[i+n][i+n]=1;
	for(int i=1;i<=n+rbt;i++)
	{
		int ps=i;//初始化主元行为当前行
		//寻找绝对值最大的元素作为主元
		for(int j=i+1;j<=n+rbt;j++) if(abs(gs[j][i])>abs(gs[ps][i])) ps=j;
		//主元接近0（小于1e-9），说明这一列已经处理完毕，继续下一列
		if(abs(gs[ps][i])<1e-9) continue;
		//交换第i行和第ps行的所有元素
		for(int j=1;j<=n+rbt+rbt;j++) swap(gs[i][j],gs[ps][j]);
		//将主元标准化为1，除以主元的值
		ld qw=gs[i][i];for(int j=i;j<=n+rbt+rbt;j++) gs[i][j]/=qw;
		///消元过程：将第i列下方的所有元素变为0
		///用第i行消去第j行的第i列元素
		for(int j=i+1;j<=n+rbt;j++) {ld qw=gs[j][i];for(int k=1;k<=n+rbt+rbt;k++) gs[j][k]-=gs[i][k]*qw;}
	}
	///后向消元
	///将上三角矩阵化为对角矩阵
	for(int i=n+rbt;i>=1;i--) for(int j=1;j<i;j++)
		{ld qw=gs[j][i];for(int k=1;k<=n+rbt+rbt;k++) gs[j][k]-=gs[i][k]*qw;}
	///构建转移矩阵
	//将第一行的结果复制到转移矩阵的第一行（初始状态）
	for(int i=1;i<=rbt;i++) mt[0][i]=gs[1][n+rbt+i];
	//如果节点i是目标节点，将对应的解复制到转移矩阵中
	for(int i=1;i<=n;i++) if(cg[i]) for(int j=1;j<=rbt;j++) mt[rb[i]][j]=gs[i][n+rbt+j];
	return mt=mt^(K-1),printf("%.10Lf\n",mt[0][rb[n]]),0;//从起始状态到目标节点n的概率
}