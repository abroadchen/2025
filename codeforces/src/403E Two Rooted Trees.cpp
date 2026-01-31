//
// Created by Psy.C on 2026/1/31.
//
/**
 * tt: 时间戳，用于线段树节点编号
 *son[i]表示节点i的重儿子
 *top[i]表示节点i所在重链的顶端节点
 * fa[i]表示节点i的父节点
 *deep[i]表示节点i的深度
 *in[i]表示节点i的DFS序（进入时间戳）
 *gg[i]标记节点i是否已被处理
 * ls表示左子节点索引，rs表示右子节点索引
 *num存储该线段树节点包含的数字
 *to[i]存储节点i的所有子节点
 *
 *res=1表示当前节点本身的贡献，mx=0记录最大子树大小
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200100
using namespace std;

int n;
bool A,B;//控制轮流操作
vector<int>ans[2];//存储两方的结果
struct Tree {
    int tt,son[N],top[N],fa[N],deep[N],in[N];
    bool gg[N];
    struct Node	{
		int ls,rs;//左右子节点
		vector<int>num;
    }node[N<<1];
    vector<int>to[N];//邻接表存储树结构
    void add(int u,int v){to[u].push_back(v);}
    int dfs(int now) {//子树最大的儿子
		int i,t,tmp,res=1,mx=0;
		for(i=0;i<to[now].size();i++) {
	    	t=to[now][i];//获取第i个子节点
	    	fa[t]=now;//子节点t的父节点为now
	    	deep[t]=deep[now]+1;//子节点t的深度
	    	res+=tmp=dfs(t);// 递归计算子树大小并累加到res
	    	if(tmp>mx) {//当前子树比之前最大的还大
				mx=tmp;// 更新最大值和重儿子
				son[now]=t;
	    	}
		}
		return res;//返回以now为根的子树大小
    }
    void Dfs(int now) {//计算每个节点的链顶
		int i,t;
		in[now]=++tt;//为节点now分配DFS序号
		if(son[now]) {
	    	top[son[now]]=top[now];//重儿子的链顶与当前节点相同
	    	Dfs(son[now]);// 优先处理重儿子
		}
		for(i=0;i<to[now].size();i++) {//处理所有轻儿子
	    	t=to[now][i];
	    	if(t==son[now]) continue;
	   	    top[t]=t;//轻儿子的链顶是自己
	    	Dfs(t);//递归处理轻儿子
		}
    }
    void build(int now,int l,int r) {
		if(l==r) return;
		int mid=((l+r)>>1);
		node[now].ls=++tt; build(tt,l,mid);//创建左子节点并递归构建
		node[now].rs=++tt; build(tt,mid+1,r);
    }
    void add(int now,int l,int r,int u,int v,int w) {//在区间[u,v]添加元素w
		if(u<=l&&r<=v) {
	    	node[now].num.push_back(w);//在当前节点存储w
	    	return;
		}
		int mid=((l+r)>>1);
		if(u<=mid) add(node[now].ls,l,mid,u,v,w);//如果左半区间有交集，递归处理左子树
		if(mid<v) add(node[now].rs,mid+1,r,u,v,w);
    }
    void del(int now,int l,int r,int u) {//删除节点u相关的信息
		int i,t;
		for(i=0;i<node[now].num.size();i++) {//遍历当前节点存储的所有元素
	    	t=node[now].num[i];//获取当前元素
	    	if(!gg[t]) {//元素t还未被处理过
				gg[t]=1;
				ans[A].push_back(t);
	    	}
		}
		node[now].num.clear();//清空当前节点的存储
		if(l==r) return;
		int mid=((l+r)>>1);
    	//根据u的位置决定走哪边
		if(u<=mid) del(node[now].ls,l,mid,u);
		else del(node[now].rs,mid+1,r,u);
    }
    void pre() {
		int i,j;
		deep[1]=top[1]=1;//初始化根节点
		dfs(1); Dfs(1);
		build(tt=1,1,n);
    }
    void ad(int u,int v,int w) {//在树上路径u→v添加元素w
		for(;top[u]!=top[v];) {//u和v不在同一条重链上
	    	if(deep[top[u]]<deep[top[v]]) swap(u,v);//让u指向更深的链顶
	    	add(1,1,n,in[top[u]],in[u],w);//在u到其链顶的路径上添加w
	    	u=fa[top[u]];//u跳到当前重链顶部的父节点
		}
		if(deep[u]>deep[v]) swap(u,v);//确保u在v上方
		if(u!=v) add(1,1,n,in[u]+1,in[v],w);//在u+1到v的路径上添加w
    }
	//删除节点u对应的信息
    void del(int u){del(1,1,n,in[u]);}
}tree[2];

int main()
{
    int i,j,p;
    cin>>n;
	//构建两棵树
    for(i=2;i<=n;i++) scanf("%d",&p),tree[0].add(p,i);
    for(i=2;i<=n;i++) scanf("%d",&p),tree[1].add(p,i);
    tree[0].pre(),tree[1].pre();
    for(i=2;i<=n;i++) {//在两棵树之间建立关联 遍历所有非根节点
    	///在tree[0]中，从tree[1].fa[i]到i的路径上添加i
		tree[0].ad(tree[1].fa[i],i,i);
		tree[1].ad(tree[0].fa[i],i,i);
    }
	//读入初始节点，标记为已访问
    cin>>p,ans[A=1].push_back(p+1),tree[1].gg[p+1]=1;
    for(i=0;;i^=1) {//无限循环进行博弈
		swap(A,B);
		puts(i&1?"Red":"Blue");
		sort(ans[B].begin(),ans[B].end());
		for(j=0;j<ans[B].size();j++) printf("%d ",ans[B][j]-1);puts("");
		ans[A].clear();
		for(j=0;j<ans[B].size();j++) tree[i].del(ans[B][j]);
		if(!ans[A].size()) return 0;
    }
}