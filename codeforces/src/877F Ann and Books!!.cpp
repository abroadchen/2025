//
// Created by Psy.C on 2026/10/6.
//
/**
ss 是前缀和（long long）。
下标范围是 0..n（ss[0]=0 未显式赋值但全局为 0）
把前缀和值离散化到 1..cnt。
注意 d[0] 未赋值（全局 0），排序从 d[1] 开始，但 mp 遍历从 i=0 到 n——d[0]=0，会把 d[0]=0（ss[0] 的值）也纳入 mp。实际上就是要包含 ss[0]=0
对每个下标 i，把位置 ss[i]（离散化编号 tmp）的：
pre[tmp] = 值 ss[i]-k 对应的编号（若存在），否则 -1。
nxt[tmp] = 值 ss[i]+k 对应的编号（若存在），否则 -1。
mp 默认 map 查找不存在返回 0，0 被用作"不存在"标记，再映射为 -1。
ss[i]=tmp 就地替换为离散化编号，此后 ss 存的是编号而非原始值。
这样建立了一个"值"级别的链表：从某个值的编号 p 出发，pre[p] 指向"比它小 k 的那个值的编号"，nxt[p] 指向"比它大 k 的那个值的编号"
查询区间是 [l, r]（1-based），--a[i].l 使得 l 变成 l-1，即区间 (l-1, r] 对应前缀和下标范围 正对应子区间 [l,r] 的和 = ss[r]-ss[l-1]。这是为了能用"差为 k"来判定区间内是否有满足条件的子段。
莫队标准排序
当前莫队维护的区间用下标区间表示，g[p] 表示"值编号 p 在当前区间内出现的次数"。s = 当前区间内满足"两数差 = k"的对数。
这段的对称逻辑（fst/lst、nxt/pre）是莫队维护有序对/边界的写法，用于在端点移动时正确增删，避免重复计数。这是差为 k 问题的标准双端莫队维护
遍历排好序的查询，用四个 while 扩展/收缩左右端点，分别调用 addlst/addfst/dellst/delfst 维护 s。
每个查询答案存入 ans[id]
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

struct node { int l, r, id; } a[N];
int b[N];
ll ss[N], s;
int g[N], nxt[N], pre[N];
int cmp(node x,node y){return b[x.l]!=b[y.l]?b[x.l]<b[y.l]:x.r<y.r;}//按 l 所在块、再按 r 排序
void delfst(int x){int p=ss[x],tmp;--g[p];tmp=nxt[p];if (tmp!=-1) s=s-g[tmp];}
void dellst(int x){int p=ss[x],tmp;--g[p];tmp=pre[p];if (tmp!=-1) s=s-g[tmp];}
void addfst(int x){int p=ss[x],tmp;tmp=nxt[p];if (tmp!=-1) s=s+g[tmp];++g[p];}
void addlst(int x){int p=ss[x],tmp;tmp=pre[p];if (tmp!=-1) s=s+g[tmp];++g[p];}

int n, t[N], cnt, q;
ll k, f[N], d[N], ans[N];
map<ll, int> mp;
signed main() {
    scanf("%d%lld",&n,&k);
    for (int i=1;i<=n;i++) scanf("%d",&t[i]);//符号：1 为加，其余(2)为减
    for (int i=1;i<=n;i++) scanf("%lld",&f[i]);//权值
    for (int i=1;i<=n;i++) if (t[i]==1) ss[i]=ss[i-1]+f[i];else ss[i]=ss[i-1]-f[i];
    for (int i=1;i<=n;i++) d[i]=ss[i];
    stable_sort(d+1,d+n+1);
    ll lst=-1;int cnt=0;
    for (int i=0;i<=n;i++) if (d[i]!=lst) mp[d[i]]=++cnt,lst=d[i];
    for (int i=0;i<=n;i++)
    {
        ll x=ss[i];
        int tmp=mp[x];
        pre[tmp]=(mp[x-k]?mp[x-k]:-1);
        nxt[tmp]=(mp[x+k]?mp[x+k]:-1);
        ss[i]=tmp;//把 ss 从原始值替换成离散化后的编号
    }
    for (int i=0;i<=n;i++) b[i]=i/100;
    scanf("%d",&q);
    for (int i=1;i<=q;i++) scanf("%d%d",&a[i].l,&a[i].r),a[i].id=i,--a[i].l;
    stable_sort(a+1,a+q+1,cmp);
    int l=0,r=-1;
    for (int i=1;i<=q;i++) {
        int L=a[i].l,R=a[i].r,id=a[i].id;
        while (r<R) addlst(++r);
        while (L<l) addfst(--l);
        while (l<L) delfst(l++);
        while (R<r) dellst(r--);
        ans[id]=s;
    }
    for (int i=1;i<=q;i++) printf("%lld\n",ans[i]);
    return 0;
}