//
// Created by Psy.C on 2026/3/24.
//
/**
构建虚树：将关键点及其LCA加入，形成最小连通子图
按DFS序排序，添加相邻节点的LCA
使用单调栈构建虚树结构
检查虚树中是否有相邻的关键点
在虚树上进行动态规划
计算最少操作次数
O(|S|)，其中|S|是关键点数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
bool vis[N];
int num[N];
bool cmp(int x, int y);
struct virtual_tree {
	struct {
		int to,next;
	}edge[N<<1]{};
	int head[N]{},cnt{},deep[N]{},dp[N][20]{},limit{};
	int L[N]{},R[N]{},dfn{};
	void add(int u,int v) {
		edge[cnt].to=v;
		edge[cnt].next=head[u];
		head[u]=cnt++;
	}
	void dfs(int u,int fa,int dep) {
		L[u]=++dfn;
		deep[u]=dep;
		dp[u][0]=fa;
		for(int i=1;i<=limit;i++)
			dp[u][i]=dp[dp[u][i-1]][i-1];
		for(int i=head[u];i!=-1;i=edge[i].next) {
			int v=edge[i].to;
			if(v!=fa)
				dfs(v,u,dep+1);
		}
		R[u]=dfn;
	}
	int LCA(int x,int y) {//最近公共祖先
		if(deep[x]<deep[y])
			swap(x,y);
		for(int i=limit;i>=0;i--)
			if(deep[x]-deep[y]>=(1<<i))
				x=dp[x][i];
		if(x==y)
			return x;
		for(int i=limit;i>=0;i--)
			if(dp[x][i]!=dp[y][i]) {
				x=dp[x][i];
				y=dp[y][i];
			}
		return dp[x][0];
	}
	void init(int n) {
		memset(head,-1,sizeof(head));
		cnt=dfn=0;
		limit=log2(n)+1;
		for(int i=1;i<n;i++)
		{
			int u,v; scanf("%d%d",&u,&v);
			add(u,v); add(v,u);
		}
	}

	vector<int>node[N];
	vector<int>ver;
	int Stack[N]{};
	void build()
	{
		ranges::sort(ver,cmp);
		int sz=ver.size()-1;
		for(int i=0;i<sz;i++)
			ver.push_back(LCA(ver[i],ver[i+1]));
		ranges::sort(ver,cmp);
		ver.erase(ranges::unique(ver).begin(),ver.end());
		int top=0;
		Stack[++top]=ver[0];
		for(int i=1;i<ver.size();i++) {
			while(top&&R[Stack[top]]<L[ver[i]])
				top--;
			if(top)
				node[Stack[top]].push_back(ver[i]);
			Stack[++top]=ver[i];
		}
	}

	bool check() {
		return ranges::all_of(ver, [&](int i) {
			return !vis[dp[i][0]];
		});
	}
	int dfs2(int u) {
		int ans=0;
		for(auto v:node[u]) {
			ans+=dfs2(v);
			num[u]+=num[v];
		}
		if(vis[u]) {
			ans+=num[u];
			num[u]=1;
		}
		else if(num[u]>1) {
			ans++;
			num[u]=0;
		}
		return ans;
	}
	void clear() {
		for(int i : ver) {
			vis[i]=num[i]=0;
			node[i].clear();
		}
		ver.clear();
	}
}tr;

bool cmp(int x, int y) { return tr.L[x] < tr.L[y]; }

int main() {
	int n; scanf("%d",&n);
	tr.init(n); tr.dfs(1,0,0);
	int m; scanf("%d",&m);
	while(m--) {
		tr.clear();
		int k; scanf("%d",&k);
		while(k--) {
			int pos; scanf("%d",&pos);
			tr.ver.push_back(pos);
			vis[pos]=true;
		}
		if(!tr.check()) {
			puts("-1");
			continue;
		}
		tr.build();
		printf("%d\n",tr.dfs2(tr.ver[0]));
		tr.clear();
	}
    return 0;
}