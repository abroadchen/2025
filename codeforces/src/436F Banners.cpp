//
// Created by Psy.C on 2026/2/7.
//
/**
n: 元素总数
w: 权重参数
limit: 分块大小
Max_p: 最大位置值
Max[M]: 每个块的最大值
pos[M]: 每个块产生最大值的位置
belong[N]: 每个位置属于哪个块
Ans: 当前答案
Pos: 当前答案对应的位置

f[i]: 位置i的附加值
p[i]: 第i个块的附加值
k[i]: 第i个块的更新阈值

Max[belong[x]]: 当前块内的最大得分值
pos[belong[x]]: 达到最大得分的位置
i: 当前考虑的位置（不同于最优位置）
f[i]: 位置i的个人附加值
p[belong[x]]: 当前块的公共附加值

Max[belong[x]] - i*(f[i]+p[belong[x]])
i*(f[i]+p[belong[x]]): 位置i当前的得分
Max[belong[x]]: 当前最优得分
这部分计算的是当前得分差距
i - pos[belong[x]]
位置差值，表示从最优位置到当前位置i的距离
这是每次操作对两个位置得分影响的差异系数

设需要d次操作后，位置i的得分超过当前位置最优位置
位置i的新得分：i*(f[i]+p[belong[x]]+d)
最优位置的新得分：pos[belong[x]]*(f[pos[belong[x]]]+p[belong[x]]+d)
当两者相等时：i*(f[i]+p[belong[x]]+d) = Max[belong[x]] + d*pos[belong[x]]
整理得：i*(f[i]+p[belong[x]]) + i*d = Max[belong[x]] + d*pos[belong[x]]
移项：i*(f[i]+p[belong[x]]) - Max[belong[x]] = d*(pos[belong[x]] - i)
解得：d = (Max[belong[x]] - i*(f[i]+p[belong[x]])) / (i - pos[belong[x]])
 */
#include <bits/stdc++.h>
#define gc getchar()
#define ll long long
#define N 100009
#define M 1009
using namespace std;
ll n,w,limit,Max_p,Max[M],pos[M],belong[N],Ans,Pos;
ll f[N],p[M],k[M];//f[i]:add of ansi p[i]:add of i-th block
struct node
{
    ll a,b;
    bool operator <(const node &rhs) const
    {
        return b<rhs.b;
    }
}P[N];
ll read()
{
    ll x=1;
    char ch;
    while (ch=gc,ch<'0'||ch>'9') if (ch=='-') x=-1;
    ll s=ch-'0';
    while (ch=gc,ch>='0'&&ch<='9') s=s*10+ch-'0';
    return s*x;
}
void ins(ll x)
{
    ///从位置x开始，向前遍历直到当前块的开头
    for (ll i=x;belong[i]==belong[x];i--)
    {
        f[i]++;//将位置i的附加值加1
        ll now_ans=i*(f[i]+p[belong[x]]);//位置i的新得分（位置 × (个人附加值 + 块附加值)）
        if (now_ans>Max[belong[x]])//更新当前块的最大值和对应位置
            Max[belong[x]]=now_ans,pos[belong[x]]=i;
    }
    k[belong[x]]=N*M;//更新阈值为极大值
    //从当前最大值位置的下一个位置开始遍历当前块
    for (ll i=pos[belong[x]]+1;belong[i]==belong[x];i++)
        //需要多少次操作才能让位置i超越当前最优位置
        k[belong[x]]=min(k[belong[x]],(Max[belong[x]]-i*(f[i]+p[belong[x]]))/(i-pos[belong[x]]));
    for (ll i=1;i<belong[x];i++)
    {
        ///将第i个块的附加值加1
        ///将块的最大值增加该块最优位置的值
        p[i]++,Max[i]+=pos[i];
        k[i]--;//将更新阈值减1（因为进行了一次操作）
        if (k[i]<=0)//需要重新计算块内最值
        {
            for (ll j=pos[i]+1;belong[j]==i;j++)
            {
                ll now_ans=j*(f[j]+p[i]);
                if (now_ans>Max[i])
                    Max[i]=now_ans,pos[i]=j;
            }
            k[i]=N*M;
            for (ll j=pos[i]+1;belong[j]==i;j++)
                k[i]=min(k[i],(Max[i]-j*(f[j]+p[i]))/(j-pos[i]));
        }
    }
}
int main()
{
    n=read(),w=read();
    for (ll i=1;i<=n;i++)
    {
        P[i].a=read(),P[i].b=read();
        Max_p=max(Max_p,P[i].a);
    }
    sort(P+1,P+n+1);
    limit=(int)sqrt(Max_p);
    for (ll i=1;i<=Max_p;i++)
        belong[i]=i/limit+1;
    for (ll i=1;i<=belong[Max_p];i++)
        pos[i]=(i-1)*limit;
    ll now=1;
    for (ll c=0;c<=P[n].b+1;c++)
    {
        while (P[now].b<c&&now<=n) ins(P[now].a),now++;
        Ans=0,Pos=1;
        for (ll i=1;i<=belong[Max_p];i++)
            if (Ans<Max[i]) Ans=Max[i],Pos=pos[i];
        printf("%lld %lld\n",Ans+(n-now+1)*w*c,Pos);
    }
    return 0;
}