//
// Created by Psy.C on 2026/4/12.
//
/**
s: 存储第一个字符串
ss: 存储后续输入的字符串
n: 字符串长度
m: 第二批字符串的数量
pos: 记录第一个字符串中每个位置对应的自动机节点
k: 查询数量
par: 存储区间查询结果，ma为最大值，from为来源
l,r: 区间左右端点
ma: 区间最大值
from: 最大值的来源位置
zuo,you: 左右子节点指针

在位置x建立单点线段树
将该点的值设为1，其他为0
递归创建子节点直到叶子节点
更新当前节点的值
如果只有一个子节点，直接继承子节点信息
如果两子节点来源相同，合并计数
否则选择最大值较大的节点信息
查询区间[x,y]的最大值及来源
完全匹配直接返回
部分匹配递归查询并合并结果

link: 后缀链接
len: 节点对应字符串长度
next[26]: 转移数组，对应26个字母
root: 对应的线段树根节点
构造函数初始化线段树根为空
id: 当前节点编号
last: 上一个节点
now,p,q: 临时变量
size: 存储各节点大小
添加字符x到自动机
创建新节点，长度为上一节点长度+1
如果belong>1，为该节点建立线段树，标记其属于第belong-1个字符串
沿着后缀链接向上，为所有没有字符x转移的节点添加转移
如果存在字符x的转移
如果p到q的距离刚好是1，直接连接
否则克隆节点q，调整链接关系

kk: 计算节点x对应的字符串长度
f[i][j]: 节点i的第2^j个祖先
g[i]: 从根到节点i的路径长度
构建倍增表用于快速跳跃
合并两个线段树
递归合并左右子树
如果是叶子节点，直接合并值；否则更新节点

que: 查询结构，范围[x,y]，位置pos
ask: 每个节点存储的查询
ans: 存储答案
lo: 存储默认答案
递归处理每个节点
合并子节点的线段树
处理该节点上的查询

读入第一个字符串
初始化自动机根节点
将第一个字符串加入自动机，记录每个位置对应的节点ID
读入m个字符串
将每个字符串加入自动机，标记属于第i个字符串
建立后缀链接构成的树
DFS预处理倍增表
构建完整的倍增祖先表
读入k个查询
对于每个查询，找到对应的自动机节点
使用倍增跳转找到合适的节点
将查询挂载到相应节点
从根开始DFS处理所有查询
输出结果：如果没找到匹配，输出默认值；否则输出匹配位置和出现次数

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int maxn = 1e6+5;

char s[maxn],ss[maxn];
int n,m,pos[maxn],k;
struct par{int ma,from;};
struct node{
	int l,r,ma,from;
	node *zuo,*you;
	node(int x,int y):l(x),r(y),ma(0),from(0),zuo(NULL),you(NULL){}
	#define mid (l+r>>1)
	void build(int x) {
		ma=1;if(l==r){from=l;return;}
		if(x<=mid)zuo=new node(l,mid),zuo->build(x),from=zuo->from;
		else you=new node(mid+1,r),you->build(x),from=you->from;
	}
	void update() {
		if(zuo==NULL)ma=you->ma,from=you->from;
		else if(you==NULL)ma=zuo->ma,from=zuo->from;
		else if(zuo->from==you->from)from=zuo->from,ma=zuo->ma+you->ma;
		else if(zuo->ma==you->ma)from=min(zuo->from,you->from),ma=zuo->ma;
		else if(zuo->ma>you->ma)ma=zuo->ma,from=zuo->from;
		else ma=you->ma,from=you->from;
	}
	par ask(int x,int y) {
		if(l==x&&r==y)return (par){ma,from};
		if(y<=mid){if(zuo!=NULL)return zuo->ask(x,y);}
		else if(x>=mid+1){if(you!=NULL)return you->ask(x,y);}
		else {
			par re,p;re.ma=re.from=0;
			if(zuo!=NULL){p=zuo->ask(x,mid);if(p.ma>re.ma)re=p;}
			if(you!=NULL){p=you->ask(mid+1,y);if(p.ma>re.ma)re=p;}
			return re;
		}
		return (par){0,0};
	}
};
struct state{
	int link,len,next[26];
	node *root;
	state():root(NULL){}
}st[maxn<<1];
int id=0,last=0,now,p,q,size[maxn<<1];
void extend(int x,int belong) {
	now=++id;st[now].len=st[last].len+1;
	if(belong>1)st[now].root=new node(1,m),st[now].root->build(belong-1);
	for(p=last;p!=-1&&!st[p].next[x];p=st[p].link)st[p].next[x]=now;
	if(p!=-1) {
		q=st[p].next[x];
		if(st[p].len+1==st[q].len)st[now].link=q;
		else {
			int clone=++id;
			st[clone]=st[q];st[clone].len=st[p].len+1;st[clone].root=NULL;
			for(;p!=-1&&st[p].next[x]==q;p=st[p].link)st[p].next[x]=clone;
			st[q].link=st[now].link=clone;
		}
	}
	last=now;
}
struct edge{int y,next;};
edge e[maxn<<1];
int first[maxn<<1],len=0;
void add(int x,int y){e[++len]=(edge){y,first[x]};first[x]=len;}
int f[maxn<<1][20],g[maxn<<1];
int kk(int x){return st[x].len-st[st[x].link].len;}
void dfs_prepare(int x) {
	for(int i=first[x];i;i=e[i].next)
	f[e[i].y][0]=x,g[e[i].y]=kk(e[i].y)+g[x],dfs_prepare(e[i].y);
}
node *merge(node *x,node *y) {
	if(x==NULL)return y;
	if(y==NULL)return x;
	node *now=new node(x->l,x->r);
	now->zuo=merge(x->zuo,y->zuo);
	now->you=merge(x->you,y->you);
	if(now->l==now->r)now->from=now->l,now->ma=x->ma+y->ma;
	else now->update();
	return now;
}
struct que{int x,y,pos;};
vector<que>ask[maxn<<1];
par ans[maxn];
int lo[maxn];
void dfs(int x) {
	if(st[x].root==NULL)st[x].root=new node(1,m);
	for(int i=first[x];i;i=e[i].next) {
		int y=e[i].y;dfs(y);
		if(st[y].root->ma)st[x].root=merge(st[x].root,st[y].root);
	}
	for(int i=0;i<ask[x].size();i++)
	ans[ask[x][i].pos]=st[x].root->ask(ask[x][i].x,ask[x][i].y);
}

int main() {
	scanf("%s",s+1);n=strlen(s+1);
	st[0].link=-1;
	for(int i=1;i<=n;i++)pos[i]=id+1,extend(s[i]-'a',1);
	scanf("%d",&m);
	for(int i=1;i<=m;i++) {
		scanf("%s",ss+1);n=strlen(ss+1);last=0;
		for(int j=1;j<=n;j++)extend(ss[j]-'a',i+1);
	}
	for(int i=1;i<=id;i++)add(st[i].link,i);
	dfs_prepare(0);
	for(int j=1;j<20;j++)
	for(int i=1;i<=id;i++)
	f[i][j]=f[f[i][j-1]][j-1];
	scanf("%d",&k);
	for(int i=1,x,y,xx,yy;i<=k;i++) {
		scanf("%d %d %d %d",&x,&y,&xx,&yy);
		int now=pos[yy];
		for(int j=19;j>=0;j--)
		if(f[now][j]&&g[f[now][j]]>=yy-xx+1)now=f[now][j];
		ask[now].push_back((que){x,y,i});
		lo[i]=x;
	}
	dfs(0);
	for(int i=1;i<=k;i++)printf("%d %d\n",!ans[i].from?lo[i]:ans[i].from,ans[i].ma);
}