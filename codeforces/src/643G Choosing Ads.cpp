//
// Created by Psy.C on 2026/4/1.
//
/**
cnt: 当前节点中不同值的数量（最多5个）
a[5]: 存储不同的数值
b[5]: 存储对应数值的出现次数
t[N<<2]: 线段树数组（开4倍空间）
tp: 临时节点，用于查询结果

定义节点合并操作
将节点x和y合并为新节点z
遍历y节点中的每个不同值
如果z中已有相同的值，将其计数相加
如果找到了相同值，继续下一个
如果z未满且当前值不存在，直接添加
如果z已满，找到出现次数最少的值
如果新值出现次数比最小值还少，整体减去新值次数
否则替换掉最小值，并将所有计数减去被替换值的原计数

将标记向下推送
左右儿子的值都设为标记值
重置左右儿子为单一值状态
平均分配区间长度给左右儿子
递归构建线段树
叶子节点：cnt=1, a[0]=值, b[0]=1
非叶子节点：合并左右子树的结果
区间覆盖操作
如果完全包含，设置懒惰标记
否则推送标记，递归修改，合并结果
区间查询操作
如果完全包含，将结果合并到tp
否则推送标记，递归查询

n(数组长度), m(操作次数), p(阈值百分比)


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1.5e5+5;

struct node { int cnt, a[5], b[5]; } t[N<<2], tp;

int p;
inline node operator+(const node &x,const node &y){
    node z=x;
    for(int i=0;i<y.cnt;++i){
        bool flag=0;
        for(int j=0;j<z.cnt;++j)
            if(z.a[j]==y.a[i]){z.b[j]+=y.b[i];flag=true;break;}
        if(flag)continue;
        if(z.cnt<p){
            z.a[z.cnt]=y.a[i];
            z.b[z.cnt++]=y.b[i];
            continue;
        }int k=0;
        for(int j=1;j<z.cnt;++j)if(z.b[j]<z.b[k])k=j;
        if(y.b[i]<z.b[k])for(int j=0;j<z.cnt;++j)z.b[j]-=y.b[i];
        else {
            int tp=z.b[k];
            z.a[k]=y.a[i];z.b[k]=y.b[i];
            for(int j=0;j<z.cnt;++j)z.b[j]-=tp;
        }
    }
    return z;
}

int tag[N<<2];
#define lc u<<1
#define rc (u<<1|1)
inline void pushdown(int u,int len){
    int &x=tag[u];
    if(x){
        tag[lc]=tag[rc]=t[lc].a[0]=t[rc].a[0]=x;
        t[lc].cnt=t[rc].cnt=1;x=0;
        t[lc].b[0]=len+1>>1,t[rc].b[0]=len>>1;
    }
}

int a[N];
inline void build(int u,int l,int r){
    if(l==r){t[u].cnt=1,t[u].a[0]=a[l],t[u].b[0]=1;return ;}
    int mid=l+r>>1;
    build(lc,l,mid);build(rc,mid+1,r);
    t[u]=t[lc]+t[rc];
}
inline void modify(int u,int l,int r,int ql,int qr,int v){
    if(ql<=l&&r<=qr){
        t[u].cnt=1,tag[u]=t[u].a[0]=v,t[u].b[0]=r-l+1;
        return ;
    }pushdown(u,r-l+1);
    int mid=l+r>>1;
    if(ql<=mid)modify(lc,l,mid,ql,qr,v);
    if(mid<qr)modify(rc,mid+1,r,ql,qr,v);
    t[u]=t[lc]+t[rc];
}
inline void query(int u,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){tp=tp+t[u];return;}
    int mid=l+r>>1;pushdown(u,r-l+1);
    if(ql<=mid)query(lc,l,mid,ql,qr);
    if(mid<qr)query(rc,mid+1,r,ql,qr);
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m;
int main() {
    fast;
    n = rd(), m = rd(), p = 100/rd();
    for (int i = 1; i <= n; ++i) a[i] = rd();
    build(1, 1, n);
    while (m--) {
        switch (rd()) {
            case 1: {
                int l = rd(), r = rd(), v = rd();
                modify(1, 1, n, l, r, v);
                break;
            }
            case 2: {
                tp.cnt = 0;
                int l = rd(), r = rd();
                query(1, 1, n, l, r);
                cout << tp.cnt;
                for (int i = 0; i < tp.cnt; ++i)
                    cout << ' ' << tp.a[i];
                cout << '\n';
                break;
            }
        }
    }
    return 0;
}