//
// Created by Psy.C on 2026/4/22.
//
/**
将每个字符的所有位置按B大小分块
每块64位，使用unsigned long long存储
x&63：取低6位，相当于x%64
x>>6=6：右移6位，相当于x/64
i 和 i-1 之间双向边，权重1（相邻移动）
i 到 n+a[i] 权重1（进入字符桶）
n+a[i] 到 i 权重0（从字符桶出来，无代价）


T: 当前处理的块索引
L = T*B: 当前块的起始索引（在64位块级别）
R = min(..., (T+1)*B-1): 当前块的结束索引
c[x].size()>>6: 字符x的总位置数除以64（有多少个完整的64位块）
now: 当前块中处理的位置数量
f[i][j]: 二维位数组，f[i]表示位置i在当前块中的状态
up: 当前块的数量
L<<6: 左移6位 = L*64，实际起始位置
i-(L<<6): 在当前块中的相对位置
f[u][x>>6]|=1ull<<(x&63):
x>>6: 块索引（x/64）
x&63: 位索引（x%64）
1ull<<(x&63): 设置第(x&63)位为1
f[u][x>>6]|=: 将位置u在当前块的第x位标记为1
对于每条最短路径边u->v
f[v][k]|=f[u][k]：将u的位状态传播给v
这是并行操作，一次性传播64个位置的状态
__builtin_popcountll(f[i][k]): 计算f[i][k]中1的个数
对于距离为bs的每个位置i，统计它能到达多少个当前块中的目标位置
sum!=now: 如果不能到达当前块中所有的目标位置
优化：O(|positions|/64 × (V + E))


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ull unsigned long long
using namespace std;
const int N=1e5+500;
const int inf=1e18;
const int B=N/64/6;//分块大小
int n;
char a[N];
int dis[N];
vector<int> c[N];///每个字符对应的所有位置
int head[N],len;
struct E{ int to,next,w,u; }e[N*10];
void add(int u,int v,int w){e[++len]=E{v,head[u],w,u};head[u]=len;}
int vis[N];
int mx,ans;
int sk[N];//排序用数组
int bfs(char x){
	memset(vis,0,sizeof(vis));
	memset(dis,63,sizeof(dis));
	deque<int> q;
	for(int i=1;i<=n;i++){
		if(a[i]==x) dis[i]=1,q.push_front(i);//权重为0的边优先处理
	}
	if(!q.size()) return 0;
	while(q.size()){
		int u=q.front();q.pop_front();
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				if(w) q.push_back(v);//权重为1的边后处理
				else q.push_front(v);
			}
		}
	}return 1;
}
ull f[N][B];//位运算数组，用于优化
void cal(int now,int res){
	if(mx<now) mx=now,ans=res;
	else if(mx==now) ans+=res;
}

/**
 *
 * @param F 标记是否所有位置都被覆盖
 * @param res 结果计数
 * @param bs 目标距离
 * @param x 字符
 */
void get(int &F,int &res,int bs,int x){
	int top=n+150;
	for(int T=0;;T++){
		int L=T*B,R=min(((int)c[x].size()-1)>>6,(T+1)*B-1);
		if(L>R) break;
		int up=R-L+1;
		int now=0;
		for(int i=1;i<=n+150;i++){
			for(int j=0;j<up;j++) f[i][j]=0;
		}
		for(int i=L<<6;i<min((int)c[x].size(),(R+1)<<6);i++){
			now++;
			int u=c[x][i];
			int x=i-(L<<6);
			f[u][x>>6]|=1ull<<(x&63);
		}
		for(int i=1;i<=top;i++){
			int u=sk[i];
			if(dis[u]>inf) continue;
			for(int i=head[u];i;i=e[i].next){
				int v=e[i].to,w=e[i].w;
				if(dis[v]==dis[u]+w){
					for(int k=0;k<up;k++) f[v][k]|=f[u][k];
				}
			}
		}
		for(int i=1;i<=n;i++){
			if(dis[i]==bs){
				int sum=0;
				for(int k=0;k<up;k++){
					sum+=__builtin_popcountll(f[i][k]);
				}
				if(sum!=now) F=0,res+=now-sum;
			}
		}
	}
}
bool cmp(int x,int y){
	return dis[x]==dis[y]? x>y: dis[x]<dis[y];
}
void solve(char x){
	if(!bfs(x)) return;
	for(int i=1;i<=n+150;i++) sk[i]=i;
	sort(sk+1,sk+1+n+150,cmp);
	int mx=0;
	for(int i=1;i<=n;i++) mx=max(mx,dis[i]);

	int F=1,res=0,cnt=0;
	get(F,res,mx,x);
	for(int i=1;i<=n;i++){
		if(dis[i]==mx) cnt++;
	}
	if(!F) cal(mx,res);
	else{
		res+=cnt*(int)c[x].size();
		get(F,res,mx-1,x);
		cal(mx-1,res);
	}
}
signed main(){
	scanf("%lld%s",&n, a+1);
	for(int i=1;i<=n;i++) c[a[i]].push_back(i);//收集每个字符的位置
	for(int i=1;i<=n;i++){
		if(i!=1) add(i,i-1,1);add(i-1,i,1);//相邻位置连边
		add(i,n+a[i],1);//位置到字符桶连边
		add(n+a[i],i,0);
	}
	for(int i=0;i<18;i++) {//遍历所有可能的字符
		solve(i+'a');
	}
	cout<<mx<<' '<<ans/2;
	return 0;
}