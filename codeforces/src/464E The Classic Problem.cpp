//
// Created by Psy.C on 2026/2/12.
//

#include <bits/stdc++.h>
#define maxn 500000
#define mod 1000000007
#define maxlog 25
#define INF 0x3f3f3f3f
using namespace std;

int n,m,dg;
long long pow2[maxn+5];
struct segment_tree{
#define lson(x) tree[x].ls
#define rson(x) tree[x].rs
	struct node{
		int ls, rs;
		long long sum;
	}tree[maxn*maxlog+5];
	int ptr;
	void push_up(const int x, const int l, const int r){
		int mid=(l+r)>>1;
		tree[x].sum=tree[lson(x)].sum+tree[rson(x)].sum*pow2[mid-l+1]%mod;
		tree[x].sum%=mod;
	}
	int insert(int &x, const int last,int upos, const int l, const int r){
		x=++ptr;
		tree[x]=tree[last];
		if(l==r){
			tree[x].sum^=1;
			return tree[last].sum;
		}
		const int mid=(l+r)>>1;
		int res;
		if(upos<=mid){
			res=insert(tree[x].ls,tree[last].ls,upos,l,mid);
			if(res) res=insert(tree[x].rs,tree[last].rs,upos,mid+1,r);
		}else{
			res=insert(tree[x].rs,tree[last].rs,upos,mid+1,r);
		}
		push_up(x,l,r);
		return res;
	}
	bool cmp(const int x, const int y, const int l, const int r){
		if(l==r){
			return tree[x].sum<tree[y].sum;
		}
		const int mid=(l+r)>>1;
		if(tree[tree[x].rs].sum==tree[tree[y].rs].sum) return cmp(tree[x].ls,tree[y].ls,l,mid);//从高位到低位，高位相同就比低位
		return cmp(tree[x].rs,tree[y].rs,mid+1,r);
	}
#undef lson
#undef rson
}T;

struct edge{
	int from, to, nxt, len;
}E[maxn*2+5];
int head[maxn+5], ecnt=1;
void add_edge(const int u, const int v, const int w){
	ecnt++;
	E[ecnt].from=u; E[ecnt].to=v; E[ecnt].len=w; E[ecnt].nxt=head[u]; head[u]=ecnt;
}

struct heap_node{
	int id{}, rt{};
	heap_node()= default;
	heap_node(const int _id, const int _rt){ id=_id; rt=_rt; }
	friend bool operator < (const heap_node p, const heap_node q){
		return !T.cmp(p.rt,q.rt,0,dg);
	}
};
priority_queue<heap_node>q;
int vis[maxn+5], disrt[maxn+5], pre[maxn+5];
long long dijkstra(const int s, const int t){
	memset(disrt,0x3f,sizeof(disrt));
	disrt[s]=0;
	q.emplace(s,disrt[s]);
	while(!q.empty()){
		heap_node x=q.top();
		q.pop();
		if(vis[x.id]) continue;
		vis[x.id]=1;
		for(int i=head[x.id];i;i=E[i].nxt){
			const int y=E[i].to;
			int tmprt;
			T.insert(tmprt,disrt[x.id],E[i].len,0,dg);
			if(disrt[y]==INF||T.cmp(tmprt,disrt[y],0,dg)){
				disrt[y]=tmprt;
				pre[y]=i;
				q.emplace(y,disrt[y]);
			}
		}
	}
	if(disrt[t]==INF) return -1;
	return T.tree[disrt[t]].sum;
}

int cnt=0, res[maxn+5];
void get_ans(const int s, const int t){
	int x=t;
	while(x!=s){
		res[++cnt]=x;
		x=E[pre[x]].from;
	}
	res[++cnt]=x;
}

int main(){
	int u,v,w;
	int s,t;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
		dg=max(dg,w);
	}
	scanf("%d %d",&s,&t);

	dg+=log2(m)+1;
	pow2[0]=1;
	for(int i=1;i<=dg;i++) pow2[i]=pow2[i-1]*2%mod;

	const long long ans=dijkstra(s,t);
	printf("%lld\n",ans);
	if(ans==-1) return 0;

	cnt=0;
	get_ans(s,t);
	printf("%d\n",cnt);
	for(int i=cnt;i>=1;i--){
		printf("%d ",res[i]);
	}
}