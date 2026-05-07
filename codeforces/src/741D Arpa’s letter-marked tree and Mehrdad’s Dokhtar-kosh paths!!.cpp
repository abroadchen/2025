//
// Created by Psy.C on 2026/5/3.
//
/**
dfn[u]：节点u的发现时间
id[tim]：时间tim对应的节点编号
siz[u]：以u为根的子树大小
dep[u]：节点u的深度
tim：DFS时间戳
son[u]：节点u的重儿子
dis[u]：从根到u路径上边权的异或和
low[u]：节点u子树的结束时间戳

设置当前节点的发现时间、ID映射
初始化子树大小和深度
遍历所有子节点：
计算到达子节点路径的异或和
递归DFS
更新当前节点子树大小
更新重儿子（子树最大的儿子）
设置low[u]为当前时间戳（子树结束时间）

ans[u]：以u为根的子树中答案
f[mask]：存储特定异或值mask对应的最大深度
先处理所有轻儿子子树，不保留其信息(kp=0)
更新当前节点的答案
处理重儿子子树，保留其信息(kp=1)
检查是否存在与当前路径异或值相同的路径，更新答案
检查是否存在与当前路径异或值相差一位的路径，更新答案（寻找异或值恰好差一位的路径）
更新当前异或值对应的最大深度
对每个轻儿子子树进行暴力处理：
遍历子树中所有节点
检查与已有路径的匹配情况更新答案
将轻儿子子树的信息合并到当前节点的f数组中
如果不是保留信息的调用(kp=0)，清空f数组（启发式合并的关键步骤）

读入节点数n
构建树：对每个节点i(2~n)，从父节点F连边，边权为1<<(ch-'a')（字母对应的位掩码）
第一次DFS：求重链剖分信息
第二次DFS：树上启发式合并求解
输出每个节点的答案
正确处理输出格式（最后一个数字后换行，其他后空格）

将 dis[u] 的第i位翻转 dis[u]^(1<<i)
减去 2*dep[u] 是因为两个节点都要向上追溯到u的子树，所以u的贡献被重复计算了两次
f[dis[id[i]]] 是某个与节点id[i]有相同异或值的节点的最大深度
f[dis[id[i]]] + dep[id[i]] 代表某种组合距离
 */
#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


constexpr int N = 5e5+7;

struct node { int to, nxt, w; } e[N];

int cnt, head[N];
void add(int u, int v, int w) {
    e[++cnt] = {v, head[u], w}; head[u] = cnt;
}

int dfn[N], id[N], siz[N], dep[N], tim, son[N], dis[N], low[N];
void dfs(int u,int ff){
    id[dfn[u]=++tim]=u;
    siz[u]=1;dep[u]=dep[ff]+1;
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;dis[v]=dis[u]^e[i].w;
        dfs(v,u);siz[u]+=siz[v];
        if(siz[v]>siz[son[u]])son[u]=v;
    }
    low[u]=tim;
}

int ans[N], f[1<<22];
void dfs(int u,int ff,int kp){
    for(int i=head[u];i;i=e[i].nxt){
        int v=e[i].to;if(v==son[u])continue;
        dfs(v,u,0);ans[u]=max(ans[u],ans[v]);
    }
    if(son[u])dfs(son[u],u,1),ans[u]=max(ans[u],ans[son[u]]);
    if(f[dis[u]])ans[u]=max(ans[u],f[dis[u]]-dep[u]);
    for(int i=0;i<22;i++)
        if(f[dis[u]^(1<<i)])ans[u]=max(ans[u],f[dis[u]^(1<<i)]-dep[u]);
    f[dis[u]]=max(f[dis[u]],dep[u]);
    for(int E=head[u];E;E=e[E].nxt){
        int v=e[E].to;if(v==son[u])continue;
        for(int i=dfn[v];i<=low[v];i++){
            if(f[dis[id[i]]])ans[u]=max(ans[u],f[dis[id[i]]]+dep[id[i]]-(dep[u]<<1));
            for(int j=0;j<22;j++)
                if(f[dis[id[i]]^(1<<j)])
                    ans[u]=max(ans[u],f[dis[id[i]]^(1<<j)]+dep[id[i]]-(dep[u]<<1));
        }
        for(int i=dfn[v];i<=low[v];i++)
            f[dis[id[i]]]=max(f[dis[id[i]]],dep[id[i]]);
    }
    if(!kp)for(int i=dfn[u];i<=low[u];i++)f[dis[id[i]]]=0;
}

int n;
int main() {
    n=rd();
    for(int i=2;i<=n;i++){
        int F=rd();char ch=getchar();while(ch<'a' || ch>'v')ch=getchar();
        add(F,i,1<<(ch-'a'));
    }
    dfs(1,1);dfs(1,1,1);
    for(int i=1;i<=n;i++)printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}