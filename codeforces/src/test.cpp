//
// Created by Psy.C on 2025/9/18.
//


#include<cstdio>
#include<cstring>
#include<algorithm>
#define lowbit(x) (x&-x)
using namespace std;
const int N=2e5+5;
struct node{int l,r,id;}q[N];int Q,ans[N];
int n,m,c[N],h[N],sa[N],tsa[N],Rank[N],tRank[N];
int log2[N],f[N][20];
int s[N],a[N],BIT[N];
//==========快读=============================
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
//==========Suffix Array=====================
inline void DA(int maxx=256){
    int p;
    for(int i=0;i<=maxx;i++) c[i]=0;
    for(int i=1;i<=n;i++) c[Rank[i]=s[i]]++;
    for(int i=2;i<=maxx;i++) c[i]+=c[i-1];
    for(int i=n;i;i--) sa[c[Rank[i]]--]=i;
    tRank[sa[1]]=p=1;
    for(int i=2;i<=n;i++){
        if(Rank[sa[i]]!=Rank[sa[i-1]]) p++;
        tRank[sa[i]]=p;
    }
    for(int i=1;i<=n;i++) Rank[i]=tRank[i];
    for(int k=1;p<n;k<<=1,maxx=p){
        p=0;
        for(int i=n-k+1;i<=n;i++) tsa[++p]=i;
        for(int i=1;i<=n;i++) if(sa[i]>k) tsa[++p]=sa[i]-k;
        for(int i=0;i<=maxx;i++) c[i]=0;
        for(int i=1;i<=n;i++) tRank[i]=Rank[tsa[i]];
        for(int i=1;i<=n;i++) c[tRank[i]]++;
        for(int i=2;i<=maxx;i++) c[i]+=c[i-1];
        for(int i=n;i;i--) sa[c[tRank[i]]--]=tsa[i];
        tRank[sa[1]]=p=1;
        for(int i=2;i<=n;i++){
            if(Rank[sa[i]]!=Rank[sa[i-1]]||Rank[sa[i]+k]!=Rank[sa[i-1]+k]) p++;
            tRank[sa[i]]=p;
        }
        for(int i=1;i<=n;i++) Rank[i]=tRank[i];
    }
    for(int i=1,k=0;i<=n;i++){
        int j=sa[Rank[i]-1];
        while(s[i+k]==s[j+k]) k++;
        h[Rank[i]]=k;if(k>0) k--;
    }
}
//==========RMQ==============================
inline void RMQ(){
    for(int i=1;i<=n;i++) f[i][0]=h[i];
    for(int i=2;i<=n;i++) log2[i]=log2[i>>1]+1;
    for(int j=1;j<=log2[n];j++){
        for(int i=1;i+(1<<j)-1<=n;i++){
            f[i][j]=min(f[i][j-1],f[i+(1<<j-1)][j-1]);
        }
    }
}
inline int query(int l,int r){
    int k=log2[r-l+1];
    return min(f[l][k],f[r-(1<<k)+1][k]);
}
//==========排序==============================
inline bool cmp1(const node &a,const node &b){
    return a.l+a.r<b.l+b.r;
}
inline bool cmp2(const node &a,const node &b){
    return a.l-a.r<b.l-b.r;
}
//==========BIT统计答案=======================
inline void add(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)) BIT[i]+=v;
}
inline int get(int x){
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=BIT[i];
    return res;
}
//==========向上、向下二分====================
inline int solve(int pos,int k){
    int tl=pos+1,tr=pos-1;
    int l=pos+1,r=n,mid;
    while(l<=r){
        mid=l+r>>1;
        if(query(pos+1,mid)>=k) l=mid+1,tr=mid;
        else r=mid-1;
    }
    l=1;r=pos;
    while(l<=r){
        mid=l+r>>1;
        if(query(mid+1,pos)>=k) r=mid-1,tl=mid;
        else l=mid+1;
    }
    return get(tr)-get(tl-1);
}
int main(){
    m=read();
    for(int i=1;i<=m;i++) a[i]=read();
    /*转成差分序列*/
    for(int i=1;i<m;i++) s[i]=a[i+1]-a[i];s[m]=1e9;
    for(int i=1;i<m;i++) s[i+m]=-s[i];
    n=(m<<1)-1;
    /*离散化*/
    memcpy(a,s,n+1<<2);
    sort(a+1,a+n+1);
    int cnt=unique(a+1,a+n+1)-(a+1);
    for(int i=1;i<=n;i++) s[i]=lower_bound(a+1,a+cnt+1,s[i])-a;

    DA(cnt);RMQ();

    Q=read();
    for(int i=1;i<=Q;i++){
        q[i].l=read();q[i].r=read();q[i].r-=q[i].l;
        q[i].id=i;
    }
    /*离线统计答案：右边从后扫，左边从前扫*/
    sort(q+1,q+Q+1,cmp1);
    for(int j=m-1,i=Q;i;i--){
        for(;j>1&&j>q[i].l+q[i].r;j--) add(Rank[j+m],1);
        ans[q[i].id]+=solve(Rank[q[i].l],q[i].r);
    }
    sort(q+1,q+Q+1,cmp2);
    memset(BIT,0,n+1<<2);
    for(int j=1,i=1;i<=Q;i++){
        for(;j<m&&j+q[i].r<q[i].l;j++) add(Rank[j+m],1);
        ans[q[i].id]+=solve(Rank[q[i].l],q[i].r);
        if(!q[i].r) ans[q[i].id]=m-1;
    }
    for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
    return 0;
}