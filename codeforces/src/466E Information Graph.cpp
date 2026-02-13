//
// Created by Psy.C on 2026/2/13.
//
///时间复杂度：O(m log n)，其中m是操作次数，n是节点数
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define PII pair<int,int>
#define mp make_pair
const int N=1e5+10;

namespace IO{
    //快读
    inline int read(){
        int x=0,f=1;
        char ch=getchar();
        while(ch<'0'||ch>'9'){
            if(ch=='-'){
                f=-1;
            }
            ch=getchar();
        }
        while(ch>='0'&&ch<='9'){
            x=(x<<1)+(x<<3)+(ch^48);
            ch=getchar();
        }
        return x*f;
    }

    //快写
    inline void write(int x){
        if(x<0){
            putchar('-');
            x=-x;
        }
        if(x>9){
            write(x/10);
        }
        putchar(x%10+'0');
    }
}

using namespace IO;

namespace code{
    //链式前向星存图
    int head[N],tot;

    struct node{
        int ver,nxt;
    }t[N<<1];

    void add(int x,int y){
        t[++tot].ver=y,t[tot].nxt=head[x],head[x]=tot;
    }

    //并查集
    int fa[N];

    int getfa(int x){
        if(fa[x]==x){
            return x;
        }
        return fa[x]=getfa(fa[x]);
    }

    //树链剖分
    int fat[N],size[N],son[N],deep[N],top[N];

    void dfs1(int x){//计算子树大小、深度、重儿子
        size[x]=1;
        int maxson=-1;
        for(int i=head[x];i;i=t[i].nxt){
            int y=t[i].ver;
            if(y==fat[x]){
                continue;
            }
            fat[y]=x;
            deep[y]=deep[x]+1;
            dfs1(y);
            if(size[y]>maxson){
                maxson=size[y];
                son[x]=y;
            }
            size[x]+=size[y];
        }
    }

    void dfs2(int x,int from){//标记链的顶端
        top[x]=from;
        if(!son[x]){
            return;
        }
        dfs2(son[x],from);
        for(int i=head[x];i;i=t[i].nxt){
            int y=t[i].ver;
            if(y==son[x]||y==fat[x]){
                continue;
            }
            dfs2(y,y);
        }
    }

    //求LCA
    //将两点移到同一重链上，深度浅的那个就是LCA
    int lca(int x,int y){
        while(top[x]!=top[y]){
            if(deep[top[x]]<deep[top[y]]){
                swap(x,y);
            }
            x=fat[top[x]];
        }
        if(deep[x]<deep[y]){
            return x;
        }
        return y;
    }

    //主程序
    int n,m,f_tot,q_tot;
    PII file[N],query[N];

    void solve(){
        n=read(),m=read();
        for(int i=1;i<=n;i++){//并查集预处理
            fa[i]=i;
        }
        for(int i=1;i<=m;i++){//离线处理
            int op=read();
            if(op==1){
                int x=read(),y=read();
                add(y,x);//单向边
                fa[x]=getfa(y);//在线维护并查集
            }else if(op==2){
                int x=read();
                file[++f_tot]=mp(x,getfa(x));//记录节点和其根节点
            }else{
                int x=read(),y=read();
                query[++q_tot]=mp(x,y);
            }
        }
        for(int i=1;i<=n;i++){//枚举所有点
            if(getfa(i)==i){//判断是否为所在连通块的根
                deep[i]=1;//树剖预处理
                fat[i]=i;
                dfs1(i);
                dfs2(i,i);
            }
        }
        for(int i=1;i<=q_tot;i++){
            int x=query[i].first,y=query[i].second,st=file[y].first,ed=file[y].second;
            if(getfa(x)!=getfa(st)){//是否在同一个连通块
                printf("NO\n");
                continue;
            }
            if(lca(x,st)==x&&lca(x,ed)==ed){//判断
                printf("YES\n");
            }else{
                printf("NO\n");
            }
        }
    }
}

using namespace code;

signed main(){
    solve();
    return 0;
}