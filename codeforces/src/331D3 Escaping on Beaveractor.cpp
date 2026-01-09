/**
 * 存储线段的起点(u,v)和终点(x,y)，以及方向(dir)
 * 扫描线算法中的边，包含位置、左右边界、操作类型和索引
 * 存储查询结果的x和y坐标
 * 查询信息：坐标、时间、操作、索引、目标和方向
 *
* 按y坐标比较行节点
按x坐标比较列节点
按y坐标比较行查询
按x坐标比较列查询
 *
*n, m: 行、列数量
B: 边界值
q: 查询数
N: 总节点数
nq, mq, bn: 各类查询的数量
nxt[]: 下一个节点的索引数组
 *
*up[i][j]: 从节点i走2^j步后到达的节点
s[i][j]: 从节点i走2^j步的距离
 *
*在给定路径上移动z单位后的坐标计算
根据当前线段的方向决定移动方向
确保结果在边界范围内

*从边界离开时的坐标计算
处理四个边界方向（左、右、下、上）
 *
*对行和列线段分别排序
设置总节点数，额外添加4个边界节点
初始化边界节点的下一个节点为自己
 *
 *将行和列线段合并到A数组中
 */
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define int long long
#define ALL(x) (x).begin(),(x).end()
#define pb push_back
#define MP make_pair
using namespace std;
template <class t> bool ckmin(t&x,t y){if(x>y){x=y;return true;}return false;}
template <class t> bool ckmax(t&x,t y){if(x<y){x=y;return true;}return false;}
constexpr  int MaxN=1e5+50;
constexpr  int Lim=1e16;
struct Node{int u,v,x,y,dir;}R[MaxN],C[MaxN],A[MaxN];
struct Edge{int x,l,r,opt,idx;bool operator < (const Edge &nt) const{return x<nt.x;}};
int ansx[MaxN],ansy[MaxN];
struct Query{int x,y,tm,opt,idx,to,dir;}Rq[MaxN],Cq[MaxN],Bq[MaxN];
inline bool cmpR(const Node &a, const Node &b){return a.y<b.y;}
inline bool cmpC(const Node &a, const Node &b){return a.x<b.x;}
inline bool cmpRq(const Query &a, const Query &b){return a.y<b.y;}
inline bool cmpCq(const Query &a, const Query &b){return a.x<b.x;}
int n,m,B,q,N,nq,mq,bn;
int nxt[MaxN];
#define fi first
#define se second
#define IT set<pair<int,int> >::iterator
int up[MaxN][62],s[MaxN][62];
inline int Add(const int x,const int y){return (x+y)>=Lim?Lim:(x+y);}
inline int dis(const int x,const int y) {
	if(x>n+m&&y>n+m)return 0;
	if(x<=n+m&&y<=n+m)return abs(A[x].x-A[y].x)+abs(A[x].y-A[y].y);
	if(y==n+m+1)return A[x].x-1;
	if(y==n+m+2)return B-A[x].x;
	if(y==n+m+4)return A[x].y-1;
	return B-A[x].y;
}
inline void go(const int x,const int sx,const int sy,const int z,int &ex,int &ey) {
	if(x<=n) {
		if(A[x].u<A[x].x)ex=sx+z;
		else ex=sx-z;
		ey=sy;
	}
	else {
		if(A[x].v<A[x].y)ey=sy+z;
		else ey=sy-z;
		ex=sx;
	}
	ckmin(ex,B),ckmax(ex,1LL),ckmin(ey,B),ckmax(ey,1LL);
}
inline void goout(const int x,const int sx,const int sy,const int z,int &ex,int &ey) {
	if(x==n+m+1)ex=max(1LL,sx-z),ey=sy;
	else if(x==n+m+2)ex=min(B,sx+z),ey=sy;
	else if(x==n+m+4)ey=max(1LL,sy-z),ex=sx;
	else ey=min(B,sy+z),ex=sx;
}
signed main() {
	cin >> q >> B,++B;
	for(int i=1;i<=q;++i)
	{
		Node X{}; cin >> X.u >> X.v >> X.x >> X.y,++X.u,++X.v,++X.x,++X.y;
		if(X.v==X.y)R[++n]=X;else C[++m]=X;
	}
	sort(R+1,R+n+1,cmpR),sort(C+1,C+m+1,cmpC);
	N=n+m+4; // 1 left 2 right 3 up 4 down
	nxt[n+m+1]=n+m+1,nxt[n+m+2]=n+m+2,nxt[n+m+3]=n+m+3,nxt[n+m+4]=n+m+4;
	for(int i=1;i<=n;++i)R[i].dir=R[i].u<R[i].x?2:1;
	for(int i=1;i<=m;++i)C[i].dir=C[i].v<C[i].y?3:4;
	{int T=0;for(int i=1;i<=n;++i)A[++T]=R[i];
	for(int i=1;i<=m;++i)A[++T]=C[i];}
	int Q; cin >> Q;
	for(int i=1;i<=Q;++i) {
		char opt[5];
		Query cu{}; cin >> cu.x >> cu.y >> opt >> cu.tm,cu.idx=i;
		cu.to=-1,++cu.x,++cu.y;
		if(*opt=='L'||*opt=='R') {
			if(*opt=='L')cu.opt=-1;
			else cu.opt=+1;
			Rq[++nq]=cu;
		} else {
			if(*opt=='U')cu.opt=+1;
			else cu.opt=-1;
			Cq[++mq]=cu;
		}
	}
	sort(Rq+1,Rq+nq+1,cmpRq), sort(Cq+1,Cq+mq+1,cmpCq);
	for(int i=1;i<=nq;++i)Rq[i].dir=Rq[i].opt>0?2:1;
	for(int i=1;i<=mq;++i)Cq[i].dir=Cq[i].opt>0?3:4;
	{// Edged Row
		set<pair<int,int> > S;
		vector<Edge> dr;
		for(int i=1;i<=n;++i)
			dr.pb((Edge){R[i].y,R[i].u,R[i].x,+1,i}),
			dr.pb((Edge){R[i].y+1,R[i].u,R[i].x,-1,i});
		for(int i=1;i<=m;++i)
			dr.pb((Edge){min(C[i].v,C[i].y),C[i].u,C[i].x,+1,i+n}),
			dr.pb((Edge){max(C[i].v,C[i].y)+1,C[i].u,C[i].x,-1,i+n});
		for(auto &i:dr)if(i.l>i.r) swap(i.l,i.r);
		sort(ALL(dr));
		int pos=-1;
		for(int i=1;i<=n;++i) {
			while(pos+1<dr.size()&&dr[pos+1].x<=R[i].y) {
				++pos;
				if(dr[pos].opt>0) {
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				}
				else {
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(R[i].u<R[i].x) {
				if(auto it=S.upper_bound(MP(R[i].x,1e9)); it==S.end())nxt[i]=n+m+2;
				else nxt[i]=it->se;
			} else {
				if(auto it=S.lower_bound(MP(R[i].x,0)); it==S.begin())nxt[i]=n+m+1;
				else nxt[i]=(--it)->se;
			}
		}
		pos=-1,S.clear();
		for(int i=1;i<=nq;++i) {
			while(pos+1<dr.size()&&dr[pos+1].x<=Rq[i].y) {
				++pos;
				if(dr[pos].opt>0) {
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				} else {
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(Rq[i].opt>0) {
				if(auto it=S.lower_bound(MP(Rq[i].x,0)); it==S.end())Rq[i].to=n+m+2;
				else Rq[i].to=it->se;
			} else {
				if(auto it=S.upper_bound(MP(Rq[i].x,1e9)); it==S.begin())Rq[i].to=n+m+1;
				else Rq[i].to=(--it)->se;
			}
		}
	}
	{// Edged Col
		set<pair<int,int> > S;
		vector<Edge> dr;
		for(int i=1;i<=n;++i)
			dr.pb((Edge){std::min(R[i].u,R[i].x),R[i].v,R[i].y,+1,i}),
			dr.pb((Edge){std::max(R[i].u,R[i].x)+1,R[i].v,R[i].y,-1,i});
		for(int i=1;i<=m;++i)
			dr.pb((Edge){C[i].x,C[i].v,C[i].y,+1,i+n}),
			dr.pb((Edge){C[i].x+1,C[i].v,C[i].y,-1,i+n});
		for(auto &i:dr)if(i.l>i.r)swap(i.l,i.r);
		sort(ALL(dr));
		int pos=-1;
		for(int i=1;i<=m;++i) {
			while(pos+1<dr.size()&&dr[pos+1].x<=C[i].x) {
				++pos;
				if(dr[pos].opt>0) {
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				} else {
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(C[i].v<C[i].y) {
				if(auto it=S.upper_bound(MP(C[i].y,1e9)); it==S.end())nxt[i+n]=n+m+3;
				else nxt[i+n]=it->se;
			} else {
				if(auto it=S.lower_bound(MP(C[i].y,0)); it==S.begin())nxt[i+n]=n+m+4;
				else nxt[i+n]=(--it)->se;
			}
		}
		pos=-1,S.clear();
		for(int i=1;i<=mq;++i) {
			while(pos+1<dr.size()&&dr[pos+1].x<=Cq[i].x) {
				++pos;
				if(dr[pos].opt>0) {
					S.insert(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.insert(MP(dr[pos].r,dr[pos].idx));
				} else {
					S.erase(MP(dr[pos].l,dr[pos].idx));
					if(dr[pos].l^dr[pos].r)S.erase(MP(dr[pos].r,dr[pos].idx));
				}
			}
			if(Cq[i].opt>0) {
				if(auto it=S.lower_bound(MP(Cq[i].y,0)); it==S.end())Cq[i].to=n+m+3;
				else Cq[i].to=it->se;
			} else {
				if(auto it=S.upper_bound(MP(Cq[i].y,1e9)); it==S.begin())Cq[i].to=n+m+4;
				else Cq[i].to=(--it)->se;
			}
		}
	}
	for(int i=1;i<=nq;++i)Bq[++bn]=Rq[i];
	for(int i=1;i<=mq;++i)Bq[++bn]=Cq[i];
	for(int i=1;i<=N;++i)up[i][0]=nxt[i],s[i][0]=dis(i,nxt[i]);
	for(int k=1;k<62;++k)for(int i=1;i<=N;++i)
		up[i][k]=up[up[i][k-1]][k-1],s[i][k]=Add(s[i][k-1],s[up[i][k-1]][k-1]);
	for(int i=1;i<=bn;++i) {
		if(!Bq[i].tm) {
			ansx[Bq[i].idx]=Bq[i].x,ansy[Bq[i].idx]=Bq[i].y;
			continue;
		}
		int w=Bq[i].tm,to=Bq[i].to,x=Bq[i].x,y=Bq[i].y,I=Bq[i].idx;
		int dir=Bq[i].dir;
		if(to<=n+m&&w>abs(x-A[to].x)+abs(y-A[to].y)) {
			w-=abs(x-A[to].x)+abs(y-A[to].y);
			x=A[to].x,y=A[to].y,dir=A[to].dir;
			for(int k=61;to<=n+m&&~k;--k)
				if(up[to][k]<=n+m&&w>s[to][k])
					w-=s[to][k],to=up[to][k],
					x=A[to].x,y=A[to].y,dir=A[to].dir;
			to=nxt[to];
		}
		if(to>n+m) {
			goout(to,x,y,w,ansx[I],ansy[I]);
			continue;
		}
		if(dir==1) {
			int tp=max(A[to].u,A[to].x);ckmin(tp,x);
			if(w<=x-tp)ansx[I]=x-w,ansy[I]=y;
			else go(to,tp,y,w-(x-tp),ansx[I],ansy[I]);
		} else if(dir==2) {
			int tp=min(A[to].u,A[to].x);ckmax(tp,x);
			if(w<=tp-x)ansx[I]=x+w,ansy[I]=y;
			else go(to,tp,y,w-(tp-x),ansx[I],ansy[I]);
		} else if(dir==4) {
			int tp=max(A[to].v,A[to].y);ckmin(tp,y);
			if(w<=y-tp)ansy[I]=y-w,ansx[I]=x;
			else go(to,x,tp,w-(y-tp),ansx[I],ansy[I]);
		} else {
			int tp=min(A[to].v,A[to].y);ckmax(tp,y);
			if(w<=tp-y)ansy[I]=y+w,ansx[I]=x;
			else go(to,x,tp,w-(tp-y),ansx[I],ansy[I]);
		}
	}
	for(int i=1;i<=Q;++i) cout << ansx[i] - 1 << ' ' << ansy[i] - 1 << '\n';
	return 0;
}