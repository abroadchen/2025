//
// Created by Psy.C on 2026/3/29.
//
/**
g[now] 存储当前节点到其子树中所有节点的距离和
f[i] 表示以节点i为根时，根到所有其他节点的距离和
换根公式：f[to] = f[now] + (n - 2*siz[to])

O(n log n + m log n)
f[x]是x到所有节点的距离和
g[son]是x到son子树内部节点的距离和
siz[son]是son子树节点数（每个节点距离比x到son的距离多1）
f[x]-g[son]-siz[son]是x到非son子树节点的距离和
乘以siz[y]是因为y子树中的每个节点都要经过x到达这些节点

g[y]是y到其子树内所有节点的距离和
n-siz[son]是不在son子树中的节点数
这些节点到y子树的距离都要经过y节点

dis+1是x到y的距离+1（路径数）
n-siz[son]是起点数（不在son子树中的节点）
siz[y]是终点数（y子树中的节点）
这部分计算的是经过x-y路径的额外距离

dis+1是LCA(z)到x子树中任意节点再到y子树中任意节点的中间路径长度
siz[x]和siz[y]分别是起始点和终止点的选择数
每条路径都要经过LCA(z)，这部分长度为dis+1

g[x]是从x到x子树中所有节点的距离和
siz[y]表示y子树中的每个节点都会经历这些距离
即x子树内每个节点到x的距离，会被重复siz[y]次

g[y]是从y到y子树中所有节点的距离和
siz[x]表示x子树中的每个节点都会经历这些距离
即y子树内每个节点到y的距离，会被重复siz[x]次

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

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

#define int long long
constexpr int N = 1e5+5;

int dep[N],fa[N][21],siz[N];
int f[N],g[N],n,m,rt=1;
vector<int>G[N];
void dfs(int now,int from) {
    siz[now]=1;
    for(int i=1;(1<<i)<=dep[now];i++)
        fa[now][i]=fa[fa[now][i-1]][i-1];//倍增预处理
    g[now]=0;
    for(int to:G[now]) {
        if(to==from) continue;
        fa[to][0]=now;dep[to]=dep[now]+1;//设置父节点和深度
        dfs(to,now);
        g[now]+=g[to]+siz[to],siz[now]+=siz[to];//计算子树信息
    }
}
void redfs(int now,int from) {
    for(int to:G[now]) {
        if(to==from) continue;
        f[to]=f[now]+(n-2*siz[to]);
        redfs(to,now);
    }
}
int LCA(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;~i;i--)
        if((1<<i)<=dep[x]-dep[y]) x=fa[x][i];
    if(x==y) return x;
    for(int i=20;~i;i--)
        if((fa[x][i]^fa[y][i])) x=fa[x][i],y=fa[y][i];//同时向上跳跃直到相遇
    return fa[x][0];
}


signed main() {
    read(n,m);
    for(int i=1,x,y;i<n;i++) {
        read(x,y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(rt,0);for(int i=1;i<=n;i++) f[rt]+=dep[i];redfs(rt,0);
    for(int i=1,x,y,z;i<=m;i++) {
        read(x,y);
        if(dep[x]>dep[y]) swap(x,y);
        z=LCA(x,y);
        if(z==x){
            int dis=dep[x]+dep[y]-2*dep[z],son=y;
            for(int i=20;~i;i--)
                if(fa[son][i]&&dep[fa[son][i]]>dep[x]) son=fa[son][i];
            double Ans=siz[y]*(f[x]-g[son]-siz[son])+(n-siz[son])*g[y]+(dis+1)*(n-siz[son])*siz[y];
            printf("%.6lf\n",Ans/((n-siz[son])*siz[y]));
        } else{
            int dis=dep[x]+dep[y]-2*dep[z];
            double Ans=siz[x]*siz[y]*(dis+1)+siz[y]*g[x]+siz[x]*g[y];
            printf("%.6lf\n",Ans/(siz[x]*siz[y]));
        }
    }
    return 0;
}