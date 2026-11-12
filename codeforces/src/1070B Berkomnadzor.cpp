//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
operator< 按掩码长度 bit 升序排序，短的（前缀更长/更具体）排前面，read() 时也保证"先插具体后插宽泛"便于插入检查冲突。

read()—读取一行：

第一个字符 +/- 决定 color；
读 a.b.c.d；
若后面是 /数字 读入 bit（掩码）；
把 4 段拼接成 32 位 x，再逐位存入 val[1..32]。
printans()—把 val 每 8 位一组还原成 a.b.c.d/掩码 输出
因为先按 bit 排序（短的先插），先插入更具体的规则；
如果一条规则的前缀包含了另一条规则（走到已标记节点），而颜色不同 → 直接 -1（黑白相互包含无解）。
最终在叶节点打标记 color[now]=a.color
g[x]=1 表示节点 x 的子树内包含至少一个白名单地址；
递归后回溯，用子节点和自身累加出 g
条件 g[x]==0 && (g[fa[x]]==1 || x==0) 的含义：

g[x]==0：节点 x 的整棵子树不含任何白名单 → 它覆盖的这段 IP 区间可以整体作为一个黑名单块；
且父节点含白（g[fa[x]]==1）或已到根：说明父节点范围内混有白，不能再向上合并，只能在 x 这一层截断。
满足条件时：

记录这块 CIDR，前缀长度 = 节点深度 depth[x]；
从 x 一路向上沿 fa 回溯，用 now==rs(fa[now]) 判断每一层走的是右孩子（1）还是左孩子（0），还原出块的前缀二进制位，写入 ans[cnt].val[]。
if(ls(x)) dfs(ls(x)); if(rs(x)) dfs(rs(x)); —— 先深搜叶子，再判当前节点，保证从根向下的过程中每个"可截断的黑块"只被收一次

*/
#include <bits/stdc++.h>
#define B 35//二进制位数组长度（32位IP + 冗余）
#define N 200005//最多输入条数
#define M N<<5//字典树最大节点数 ≈ 200005*32 ≈ 6.4e6
using namespace std;

struct Net{
    bool color;//0=白(+), 1=黑(-)
    int bit=32;//掩码长度，默认为/32
    bool val[B]{};//二进制位，val[1..32]，高位在前
    Net():color(0),bit(32){}
    bool operator <(const Net &b) const { return bit<b.bit; }
    void read(){
        char ch;
        scanf(" %c",&ch);
        if(ch=='-') color=1; else color=0;
        int a,b,c,d,x=0;
        scanf("%d.%d.",&a,&b); scanf("%d.%d",&c,&d); ch=getchar();
        if(ch=='/') scanf("%d",&bit);
        x+=a*(1<<24)+c*(1<<8); x+=b*(1<<16)+d*(1<<0);
        for(int i=31;i>=0;--i) val[32-i]=(x>>i)&1;
    }
    void printans(){
        for(int i=1;i<=4;++i){
            int x=0;
            for(int j=1;j<=8;++j){
                int now=(i-1)*8+j;
                x=(x<<1)+val[now];
            } printf("%d",x);
            if(i!=4) putchar('.');
        } putchar('/');
        printf("%d\n",bit);
    }
}a[N],ans[N];
int n,cnt;
struct LibTree{
    int depth[M]{};//节点深度（根=0）
    int tree[M][2]{};//左右孩子，tree[x][0/1]
    int cntnode,g[M]{};//子树或自身是否含白名单
    int color[M]{},fa[M]{};//color: -1=无标记, 0=白, 1=黑；fa=父节点
    LibTree(){ cntnode=0;
        for(int & i : color) i=-1;
    }
    #define ls(x) tree[x][0]
    #define rs(x) tree[x][1]
    void Insert(Net a){
        int now=0;
        for(int i=1;i<=a.bit;++i){
            if(color[now]!=-1){
                if(a.color!=color[now])//走到已标记节点且颜色冲突
                    puts("-1"),exit(0);
            }
            int next=a.val[i];
            if(!tree[now][next])
                tree[now][next]=++cntnode;
            now=tree[now][next];
        }
        if(color[now]!=-1){//终点颜色冲突
            if(color[now]!=a.color)
                puts("-1"),exit(0);
        } color[now]=a.color;
    }
    void init(int x){
        if(ls(x)){
            depth[ls(x)]=depth[x]+1;
            init(ls(x));fa[ls(x)]=x;
            g[x]|=g[ls(x)];
        }
        if(rs(x)){
            depth[rs(x)]=depth[x]+1;
            init(rs(x));fa[rs(x)]=x;
            g[x]|=g[rs(x)];
        } g[x]|=color[x]==0;//自身是白则置1
    }
    void dfs(int x){
        if(ls(x)) dfs(ls(x));
        if(rs(x)) dfs(rs(x));
        if(g[x]==0&&(g[fa[x]]==1||x==0)){
            int now=x; ++cnt;
            ans[cnt].bit=depth[x];
            int i=depth[x];
            while(now){
                int v=(now==rs(fa[now]));
                ans[cnt].val[i]=v;
                now=fa[now]; --i;
            }
        }
    }
}tree;
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i) a[i].read();
    sort(a+1,a+n+1);//按 bit 升序，具体规则先插
    for(int i=1;i<=n;++i) tree.Insert(a[i]);//建树 + 冲突检测（冲突直接 -1 退出）
    tree.init(0);tree.dfs(0);//标记 g，并贪心选块
    printf("%d\n",cnt);
    for(int i=1;i<=cnt;++i) ans[i].printans();
}