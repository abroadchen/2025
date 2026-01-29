//
// Created by Psy.C on 2026/1/29.
//
/**
* h[N]：邻接表头指针数组
cnt：边的计数器
sz[N]：子树大小
pos：位置标记
son[N]：重儿子
top[N]：链顶节点
f[N]：父节点
mx：最大值
tot[N]：总和数组
sum[N]：子树和
dd：累计值
d[N]：深度数组
n：节点总数
 *
*计算子树大小、父节点、深度
找到每个节点的重儿子
计算子树信息
 *
*构建轻重链剖分
设置每个节点所在的重链顶端
 *
*计算每个节点到其他节点的距离和
更新最大值和位置
 *
*使用轻重链剖分求 LCA
沿着重链向上跳跃

s：计算基本组合值
第一项：三棵树的 dd 值之和
第二项：A和B树的相关组合
第三项：C和B树的相关组合
第四项：A和C树的相关组合
ysn=0：初始化额外值为 0
fp(i,1,T[B].n)：循环遍历 B 树的所有节点
计算每个节点的贡献并取最大值
T[B].Dis(T[B].pos,i)+2：B树特殊节点到当前节点的距离+2

 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define fp(i,a,b) for(int i=a;i<=b;i++)
using namespace std;


const int N=2e5+100;

ll ans;
struct Tree
{
    int h[N],cnt,sz[N],pos,son[N],top[N],f[N];
    ll mx,tot[N],sum[N],dd,d[N],n;
    Tree(){memset(h,-1,sizeof(h));cnt=0;pos=1;}
    struct Edge{int to,nxt;}e[N<<1];
    void add(int u, int v){e[++cnt]=(Edge){v,h[u]};h[u]=cnt;e[++cnt]=(Edge){u,h[v]};h[v]=cnt;}
    void dfs1(int u,int fa)
        {
            sz[u]=1;f[u]=fa;d[u]=d[fa]+1;
            for(int i=h[u];i+1;i=e[i].nxt)//当 i 为 -1 时结束（因为初始化为 -1）
            {
                int v=e[i].to;
                if(v==fa) continue;
                dfs1(v,u);//递归处理子节点 v，当前节点 u 成为新的父节点
                sz[u]+=sz[v];
                if(sz[v]>sz[son[u]]) son[u]=v;//v 的子树比当前重儿子更大 更新重儿子
                sum[u]+=sz[v]+sum[v];//更新当前节点的子树和信息
            }
        }
    void dfs2(int u,int up)
        {
            top[u]=up;//设置当前节点 u 所在重链的顶端为 up
            if(son[u]) dfs2(son[u],up);//如果有重儿子，继续在同一链上处理
            for(int i=h[u];i+1;i=e[i].nxt)
            {
                int v=e[i].to;
                if(v==f[u]||v==son[u]) continue;//跳过父节点和重儿子
                dfs2(v,v);//对轻儿子建立新链，链顶为 v 自己
            }
        }
    void dfs3(int u,int fa,ll las)//当前节点 u、父节点 fa、累积值 las
        {
            tot[u]=sum[u]+las;dd+=tot[u];//当前节点的总和 累加到总值
            if(tot[u]>mx) mx=tot[u],pos=u;//当前值更大，更新最大值和位置
            for(int i=h[u];i+1;i=e[i].nxt)
            {
                int v=e[i].to;
                if(v==fa) continue;
                //递归处理子节点，传递更新后的累积值
                dfs3(v,u,las+n-sz[v]+sum[u]-sum[v]-sz[v]);
            }
        }
    int LCA(int u,int v)
    {
        while(top[u]^top[v])// u 和 v 不在同一链上时
        {
            if(d[top[u]]<d[top[v]]) swap(u,v);//深度浅的节点换到 u
            u=f[top[u]];//u 跳到当前链顶的父节点
        }
        return d[u]<d[v]?u:v;//返回深度较小的节点
    }
    //节点 u 和 v 之间的距离
    ll Dis(int u,int v){return d[u]+d[v]-2*d[LCA(u,v)];}//两点深度之和 - 2倍 LCA 深度
}T[4];//实际使用 1,2,3
void calc(int A,int B,int C)//三棵树的索引 A、B、C
{
    ll s=(T[A].dd+T[B].dd+T[C].dd)+(T[A].mx*T[B].n+T[A].n*T[B].n+T[B].mx*T[A].n)+
        (T[C].mx*T[B].n+T[B].n*T[C].n+0)+(T[A].mx*T[C].n+0+T[C].mx*T[A].n),ysn=0;
    fp(i,1,T[B].n) ysn=max(ysn,T[B].tot[i]*T[C].n+(T[B].Dis(T[B].pos,i)+2)*T[A].n*T[C].n);
    ans=max(ans,s+ysn);
}
ll gi()//快速读入 long long 类型的整数
{
  ll x=0,t=1;
  char ch=getchar();
  while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
  if(ch=='-') t=-1,ch=getchar();
  while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
  return x*t;
}


int main() {
    fast;
    T[1].n=gi();T[2].n=gi();T[3].n=gi();
    fp(i,1,T[1].n-1) T[1].add(gi(),gi());
    fp(i,1,T[2].n-1) T[2].add(gi(),gi());
    fp(i,1,T[3].n-1) T[3].add(gi(),gi());
    fp(i,1,3) T[i].dfs1(1,0),T[i].dfs2(1,1),T[i].dfs3(1,0,0),T[i].dd/=2;//边被重复计算了
    fp(i,1,3)//遍历所有不同的树对组合
        fp(j,1,3)
    {
        if(i==j) continue;
        calc(i,j,6-i-j);
    }
    printf("%lld\n",ans);
    return 0;
}