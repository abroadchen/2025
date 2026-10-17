//
// Created by Psy.C on 2026/10/17.
//
/**
N：节点数上限，约 2e5。
struct hh：一条边，f=起点，t=终点，w=边权，带默认构造函数。
edge[N<<1]：存储所有边的数组（N<<1 大概给动态新增的边留空间）
struct HH：线性基（XOR 线性基），用于维护所有环的 xor 异或张成空间。w[34] 存 0..30 位基向量。
全局对象 _：初始状态（空线性基），作为回溯的基准
从高位 30 到低位 0 遍历。
若 x 的第 i 位为 1：
若 w[i] 为空，则把它填成 x 并直接返回（插入完成）。
否则 x ^= w[i]，消去这一位，继续向下处理。
这就是线性基的标准插入：把 x 消成"不可约"形式再入基
从高位到低位，若异或 w[i] 能让 x 变小（即该位为 1 且 w[i] 有值），就异或。
这是在线性基张成空间里求 x 能异或得到的最小值（贪心消元）
v[N<<2]：线段树数组，每个节点挂一个 vector<hh>，存"存活时间段完全覆盖该区间"的边。
ls/rs：左右儿子下标；lson/rson 是递归下传用的简写
把边 e 挂到所有"完全包含 [x,y] 的区间"的节点上（标准线段树区间分解）。
若当前区间完全在 [x,y] 内，直接 push_back，返回。
否则向下递归左右孩子分解

fa[N]：并查集父亲。
getfa(x)：找根（路径压缩未做，因为要支持撤销，不能压缩——不然无法回溯）。
f[N]：节点 x 相对其父亲 fa[x] 的 xor 权值（带权并查集）。
getdis(x)：递归求出 x 到根的 xor 累计值：x==fa[x] 时为 0，否则 f[x] ^ getdis(fa[x])。
这是带异或权的并查集：getdis(x) 表示 x 到根节点的"异或距离"，用于合并时维护边权

记录一次并查集合并操作，用于回退：x=被挂到 y 下的那个节点、y=父亲节点、s=是否因深度相同导致 dep 增加了 1（方便撤销深度）
void solve(k,l,r,HH G)：G 是当前收集到的线性基副本（值传递，注意是传值！所以每层有自己的拷贝，回溯不会互相污染）。
stack<hhh> S：本次处理中用到的并查集合并操作栈，用于撤销。
遍历当前节点挂载的所有边：
取出边 x,y,w。
fx=getfa(x), fy=getfa(y)：两端根。
w ^= getdis(x) ^ getdis(y)：把边权折算成两端相对根的 xor 距离，即两端各自到根的 xor，再异或边权，得到"加入这条边后形成的环的 xor 值"。
若 fx==fy（成环）‍：G.ins(w)，把环的 xor 值插入线性基。
否则（不在同一集合）‍：合并两棵树。
按 dep（树高）保证小树挂到大树下（按秩合并，未压缩，保证复杂度）。
cur=(hhh){fx,fy,0}：记录这次合并的 (被挂节点, 父节点)。
fa[fx]=fy; f[fx]=w：把 fx 挂到 fy 下，并把相对 xor 距离记为 w。
若等高，++dep[fy]，cur.s=1 记下标。
压入栈 S。
到达叶子（l==r，即某个询问时间点）：回答该时间点的询问：G.query(getdis(qx[l])^getdis(qy[l])) —— 两点各自的根 xor 距离相异或，得到 dist(x) xor dist(y)，再拿到线性基里取最小，即两点间所有路径上异或和的最小值。
否则：递归左右子树，继续下放 DFS（把当前已插入的边/线性基 G 传给子节点）。
回溯撤销：处理完本层后，把并查集恢复：
对栈中每个操作：f[fa[top.x]=top.x]=0——把被挂节点 x 的父亲重置为自身，且 f[x]=0（解除挂靠）。
dep[top.y] -= top.s——若当时加了高度，现在减回去。
弹出。
注意：这里的 G 是按值传递的，所以本层插入的线性基在返回时自然丢弃，不需要手动撤销。
这就是"线段树分治 + 可撤销并查集 + 线性基"的经典写法：边在时间上增删 → 线段树分治把每条边挂到其存活时间区间 → DFS 线段树，进入时合并边、回答叶子询问、退出时用栈撤销并查集，线性基用值传递天然备份

声明：n=点数、m=初始边数、bg/ed=每条边存活的时间区间、Q=操作数、mp=把边 (x,y) 映射到边编号。
read(n,m) 读入。
并查集初始化 fa[i]=i。
c=m：当前边总数计数器；tim=1：时间点（询问计数）。
读入 m 条初始边：mp[(x,y)]=i 映射，bg[i]=1（第 1 个时间点开始存活），ed[i]=-1（默认一直存活，末尾修正），edge[i]=hh(x,y,z) 存边
读 Q 个操作：
z==1：加边 (x,y) 权 z（注意这里 read(z,x,y) 后 z==1，真正的权值再 read(z) 读一次）。新建边编号 ++c，bg[c]=tim 从当前时间开始存活，ed[c]=-1，存入 edge。
z==2：删边 (x,y)：找到它的编号 mp[(x,y)]，ed=tim-1（存活到上一个时间点为止）。
z==3（else）：询问：记录询问两端 qx[tim]=x, qy[tim]=y，tim++ 推进时间轴。
循环结束后 --tim：因为询问会 ++tim，这里把 tim 调整回真实的询问总数（线段树的时间范围 1..tim
把所有 ed[i]==-1（直到最后都存活）的边，把结束时间修正为 tim。
对每条存活区间非空的边（bg<=ed），用线段树插入挂到对应时间区间节点上。
以空线性基 _（全局 HH 对象）从线段树根开始 solve(1,1,tim,_)，叶子处输出每个询问的答案

 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; i++)
#define per(i,j,k) for(int i=(j), i##_end_=(k); i>=i##_end_; i--)
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+10;
struct hh{int f,t,w;hh(int ff=0,int tt=0,int ww=0){f=ff,t=tt,w=ww;}}edge[N<<1];

struct HH {
    int w[34];
    void ins(int x) {
        per(i,30,0) if (x&(1<<i))
        {
            if (!w[i]) return (void)(w[i]=x);
            x^=w[i];
        }
    }
    int query(int x){ per(i,30,0) if ((x^w[i])<x) x^=w[i]; return x; }
}_;
vector<hh> v[N<<2];
#define ls (k<<1)
#define rs (k<<1|1)
#define lson ls,l,mid
#define rson rs,mid+1,r

void insert(int k, int l, int r, int x, int y, hh e) {
    if (x<=l&&r<=y) return v[k].push_back(e);
    int mid=(l+r)>>1;
    if (x<=mid) insert(lson,x,y,e);
    if (y>mid) insert(rson,x,y,e);
}

int fa[N];
int getfa(int x){return x==fa[x]?x:getfa(fa[x]);}
int f[N];
int getdis(int x){return x==fa[x]?0:f[x]^getdis(fa[x]);}

struct hhh{int x,y;bool s;};

int dep[N], qx[N], qy[N];
void solve(int k, int l, int r, HH G) {
    stack<hhh>S;
    rep(i,0,(int)v[k].size()-1)
    {
        int x=v[k][i].f,y=v[k][i].t,w=v[k][i].w;
        int fx=getfa(x),fy=getfa(y);
        w^=getdis(x)^getdis(y);
        if (fx==fy) G.ins(w);
        else
        {
            if (dep[fx]>dep[fy]) swap(fx,fy),swap(x,y);
            hhh cur=(hhh){fx,fy,0};
            fa[fx]=fy;f[fx]=w;
            if (dep[fx]==dep[fy]) ++dep[fy],cur.s=1;
            S.push(cur);
        }
    }
    if (l==r) printf("%d\n",G.query(getdis(qx[l])^getdis(qy[l])));
    else
    {
        int mid=(l+r)>>1;
        solve(lson,G);solve(rson,G);
    }
    while (!S.empty()) f[fa[S.top().x]=S.top().x]=0,dep[S.top().y]-=S.top().s,S.pop();
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

int n, m, bg[N<<1], ed[N<<1],Q;
map<ii, int> mp;
int main() {
    int x,y,z;
    read(n,m);
    rep(i,1,n) fa[i]=i;
    int c=m,tim=1;
    rep(i,1,m) read(x,y,z),mp[make_pair(x,y)]=i,bg[i]=1,ed[i]=-1,edge[i]=hh(x,y,z);
    read(Q);
    rep(i,1,Q) {
        read(z,x,y);
        if (z==1)
        {
            read(z);
            mp[make_pair(x,y)]=++c;bg[c]=tim;ed[c]=-1;
            edge[c]=hh(x,y,z);
        }
        else if (z==2) ed[mp[make_pair(x,y)]]=tim-1;
        else qx[tim]=x,qy[tim]=y,++tim;
    }
    --tim;
    rep(i,1,c) if (ed[i]==-1) ed[i]=tim;
    rep(i,1,c) if (bg[i]<=ed[i]) insert(1,1,tim,bg[i],ed[i],edge[i]);
    solve(1,1,tim,_);
    return 0;
}