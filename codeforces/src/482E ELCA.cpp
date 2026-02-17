//
// Created by Psy.C on 2026/2/17.
//
/**
son[2]: 左右儿子
fa: 父节点
sz01: 0类型大小1
sz11: 1类型大小1
sz02: 0类型大小2
sum: 子树和
ans0: 答案0
ans: 总答案
fa[N+3]: 父节点数组
a[N+3]: 节点权值数组
n,q: 节点数，询问数

时间复杂度为均摊O(log n)
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

void read(int &x) {
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}

const int N = 1e5;
struct SplayNode {
    int son[2],fa; ll sz01,sz11,sz02,sum,ans0,ans;
} spl[N+3];
int fa[N+3];
ll a[N+3];
int n,q;
///节点u是否为其父亲的子节点
bool isroot(int u) {//如果不是，则u是当前Splay的根
    //u的父亲的左儿子
    return spl[spl[u].fa].son[0]!=u && spl[spl[u].fa].son[1]!=u;
}

///当前节点的sz11 = 左子树的sz11 + 当前节点的sz01 + 右子树的sz11
void pushup(int u) {
    int ls = spl[u].son[0],rs = spl[u].son[1];
    spl[u].sz11 = spl[ls].sz11+spl[u].sz01+spl[rs].sz11;
    spl[u].sum = spl[ls].sum+spl[rs].sum+spl[u].sz01*a[u];
    spl[u].ans = spl[ls].ans+spl[u].ans0+spl[rs].ans;
    spl[u].ans += (spl[u].sz01*spl[u].sz01-spl[u].sz02)*a[u];
    spl[u].ans += 2ll*spl[u].sz01*spl[rs].sz11*a[u];
    spl[u].ans += 2ll*spl[ls].sum*(spl[u].sz11-spl[ls].sz11);
}

///u旋转到其父亲x的位置
void rotate(int u) {
    int x = spl[u].fa,y = spl[x].fa;
    spl[u].fa = y;//u的新父节点为y
    if(!isroot(x)) spl[y].son[x==spl[y].son[1]] = u;//x不是根节点，则让y的儿子指向u
    int dir = u==spl[x].son[0];//u是x的左儿子还是右儿子（左为1，右为0）
    spl[x].son[dir^1] = spl[u].son[dir];
    if(spl[u].son[dir]) spl[spl[u].son[dir]].fa = x;
    spl[u].son[dir] = x; spl[x].fa = u;
    pushup(x); pushup(u);//更新x和u的信息
}

///不断旋转直到u成为当前Splay的根
void splaynode(int u) {
    while(!isroot(u)) {
        int x = spl[u].fa,y = spl[x].fa;
        if(!isroot(x)) {x==spl[y].son[1] ^ u==spl[x].son[1] ? rotate(u) : rotate(x);}
        rotate(u);
    }
    pushup(u);
}

///访问从u到根的路径
void access(int u) {
    for(int i=0; u; i=u,u=spl[u].fa) {//i=u：保存原来的右子树
        splaynode(u);//把u旋转到根
        //更新u的信息（加上原来右子树的信息）
        int ls = spl[u].son[0],rs = spl[u].son[1];
        spl[u].sz01 += spl[rs].sz11;
        spl[u].sz02 += spl[rs].sz11*spl[rs].sz11;
        spl[u].ans0 += spl[rs].ans;
        rs = spl[u].son[1] = i;//把原来的右子树重新设为当前右子树
        //减去刚才加上的信息（因为换了右子树）
        spl[u].sz01 -= spl[rs].sz11;
        spl[u].sz02 -= spl[rs].sz11*spl[rs].sz11;
        spl[u].ans0 -= spl[rs].ans;
        pushup(u);
    }
}

void link(int u,int v) {//将v连接到u的子树
    access(v); splaynode(v);//访问v到根的路径并把v转到根
    access(u); splaynode(u);
    //更新u的信息，加上v的贡献
    spl[u].sz01 += spl[v].sz11;
    spl[u].sz02 += spl[v].sz11*spl[v].sz11;
    spl[u].ans0 += spl[v].ans;
    spl[v].fa = u;
    pushup(u);
}

void cut(int u,int v) {//移除v作为u的子节点
    access(u); splaynode(u);
    splaynode(v);
    spl[u].sz01 -= spl[v].sz11;
    spl[u].sz02 -= spl[v].sz11*spl[v].sz11;
    spl[u].ans0 -= spl[v].ans;
    spl[v].fa = 0;//断开v的父节点连接
    pushup(u);
}

///u是否是v的祖先
bool isanc(int u,int v) {
    access(v); splaynode(v);
    splaynode(u);
    if(!isroot(v)) return true;//v不是根，说明v在u的子树中，即u是v的祖先
    return false;
}

void printans(ll x) {
    double ans = (double)x/(double)n/(double)n;
    printf("%.12lf\n",ans);
}

int main() {
    scanf("%d",&n);
    for(int i=2; i<=n; i++) scanf("%d",&fa[i]);
    for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
    for(int i=1; i<=n; i++) spl[i].sz11 = spl[i].sz01 = 1ll,spl[i].ans = spl[i].sum = a[i];
    for(int i=2; i<=n; i++) link(fa[i],i);
    access(1); splaynode(1);
    printans(spl[1].ans);
    scanf("%d",&q);
    for(int i=1; i<=q; i++) {
        char opt[5]; scanf("%s",opt+1);
        if(opt[1]=='P') {
            int x,y; scanf("%d%d",&x,&y);
            if(isanc(x,y)) swap(x,y);//确保y不是x的祖先
            cut(fa[x],x);
            fa[x] = y;
            link(fa[x],x);
            access(1); splaynode(1);
            printans(spl[1].ans);
        }
        else if(opt[1]=='V') {
            int x; ll y; scanf("%d%lld",&x,&y);
            access(x); splaynode(x);
            a[x] = y;
            pushup(x);
            printans(spl[x].ans);
        }
    }
    return 0;
}