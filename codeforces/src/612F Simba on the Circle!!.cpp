//
// Created by Psy.C on 2026/3/24.
//
/**
n: 数组长度
p: 起始位置
f[N], g[N]: DP状态数组
a[N]: 原始数组
m: 离散化后不同值的数量
F[N], G[N]: 记录前驱节点
res: 最终结果，初始化为无穷大
u: 用于离散化的临时向量
v[N]: 每个值对应的索引列表
s: 栈，用于输出路径

读入n和p，p减1（转为0索引）
初始化f和g数组为无穷大
读入数组a，同时添加到u中用于离散化
对u排序并去重，获得m（不同值的数量）
对a[i]进行离散化（映射到1-m范围）
将每个值对应的所有索引存储到v数组中

初始化第一层（值为1的所有位置）的DP值
min((i+n-p)%n,(p+n-i)%n): 从起始位置p到位置i的最短距离（考虑环形）
设置前驱为-1（表示起点）
遍历每个不同的值（从1到m）
len: 当前值对应的索引数量
计算同一层内的转移：
A: 从J位置逆时针移动到K位置的代价
B: 从J位置顺时针移动到K位置的代价
更新g[K]和G[K]
如果当前层只有一个元素，直接转移
层间转移：从当前层i转移到下一层i+1
计算层间移动的最短距离
找到最后一层的最小值作为结果并输出
从满足最优解的终点开始重建路径
逆向追踪路径并压入栈中

len: 当前层的节点数量
J=G[K]: K的前驱节点（从G数组中获取）
j: J在当前层v[i]中的索引
k: K在当前层v[i]中的索引
A: 从J经过逆时针路径到K的代价
(v[i][(k+len-1)%len]+n-J)%n*2: 逆时针从J到K的前一个节点的代价×2
(J+n-K)%n: 从J直接到K的代价
B: 从J经过顺时针路径到K的代价
(J+n-v[i][(k+1)%len])%n*2: 顺时针从J到K的后一个节点的代价×2
(K+n-J)%n: 从K到J的代价
逆时针路径 (A<B)：
for(int l=k;(l+1)%len!=j;(++l)%=len): 从k开始逆时针移动，直到接近j
s.push(-(v[i][(l+1)%len]+n-v[i][l])%n): 压入负值（逆时针移动）
s.push(-(v[i][(k+len-1)%len]+n-v[i][(j+len-1)%len])%n): 连接关键节点
for(int l=(k+len-1)%len;l!=j;(l+=len-1)%=len): 继续逆时针到j
顺时针路径 (A>=B)：
for(int l=k;(l+len-1)%len!=j;(l+=len-1)%=len): 从k开始顺时针移动
s.push((v[i][l]+n-v[i][(l+len-1)%len])%n): 压入正值（顺时针移动）
s.push((v[i][(j+1)%len]+n-v[i][(k+1)%len])%n): 连接关键节点
for(int l=(k+1)%len;l!=j;(++l)%=len): 继续顺时针到j
A=J: 当前节点
B=F[J]: J的层间前驱节点
if(B==-1)B=p: 如果是起点（F[J]=-1），则B为起始位置p
计算从B到A的最短距离，正数表示顺时针，负数表示逆时针
K=B: 更新K为下一轮的处理节点

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e3+5, inf = 0x3f3f3f3f;
int n, p, f[N], g[N], a[N], m, F[N], G[N], res = inf;
vector<int> u, v[N];
stack<int> s;
int main() {
    scanf("%d%d",&n,&p),p--,memset(f,0x3f,sizeof(f)),memset(g,0x3f,sizeof(g));
	for(int i=0;i<n;i++)scanf("%d",&a[i]),u.push_back(a[i]);
	sort(u.begin(),u.end()),u.resize(m=unique(u.begin(),u.end())-u.begin());
	for(int i=0;i<n;i++)v[a[i]=lower_bound(u.begin(),u.end(),a[i])-u.begin()+1].push_back(i);
	for(auto i:v[1])f[i]=min((i+n-p)%n,(p+n-i)%n),F[i]=-1;
	for(int i=1;i<=m;i++){
		int len=v[i].size();
		for(int j=0;j<len;j++)for(int k=0;k<len;k++){
			if(j==k)continue;
			int J=v[i][j],K=v[i][k];
			int A=(v[i][(k+len-1)%len]+n-J)%n*2+(J+n-K)%n;
			int B=(J+n-v[i][(k+1)%len])%n*2+(K+n-J)%n;
			if(g[K]>f[J]+min(A,B))g[K]=f[J]+min(A,B),G[K]=J;
		}
		if(len==1)g[v[i][0]]=f[v[i][0]],G[v[i][0]]=v[i][0];
		if(i==m)continue;
		for(auto j:v[i])for(auto k:v[i+1])
			if(f[k]>g[j]+min((k+n-j)%n,(j+n-k)%n))f[k]=g[j]+min((k+n-j)%n,(j+n-k)%n),F[k]=j;
	}
	for(auto i:v[m])res=min(res,g[i]);
	printf("%d\n",res);
	for(auto K:v[m]){//遍历最后一层的所有节点
		if(g[K]!=res)continue;//只处理最优解的节点
		for(int i=m;i;i--){//从最后一层倒推到第一层
			int len=v[i].size();
			int J=G[K];
			int j=lower_bound(v[i].begin(),v[i].end(),J)-v[i].begin(),
			k=lower_bound(v[i].begin(),v[i].end(),K)-v[i].begin();
			int A=(v[i][(k+len-1)%len]+n-J)%n*2+(J+n-K)%n;
			int B=(J+n-v[i][(k+1)%len])%n*2+(K+n-J)%n;
			if(len>1){
				if(A<B){
					for(int l=k;(l+1)%len!=j;(++l)%=len)s.push(-(v[i][(l+1)%len]+n-v[i][l])%n);
					s.push(-(v[i][(k+len-1)%len]+n-v[i][(j+len-1)%len])%n);
					for(int l=(k+len-1)%len;l!=j;(l+=len-1)%=len)s.push((v[i][l]+n-v[i][(l+len-1)%len])%n);
				}else{
					for(int l=k;(l+len-1)%len!=j;(l+=len-1)%=len)s.push((v[i][l]+n-v[i][(l+len-1)%len])%n);
					s.push((v[i][(j+1)%len]+n-v[i][(k+1)%len])%n);
					for(int l=(k+1)%len;l!=j;(++l)%=len)s.push(-(v[i][(l+1)%len]+n-v[i][l])%n);
				}
			}
			A=J,B=F[J];
			if(B==-1)B=p;
			s.push((A+n-B)%n<(B+n-A)%n?(A+n-B)%n:-(B+n-A)%n);
			K=B;
		}
		break;//找到一个路径就退出
	}
	while(!s.empty())printf("%c%d\n",(s.top()>=0?'+':'-'),abs(s.top())),s.pop();
	return 0;
}