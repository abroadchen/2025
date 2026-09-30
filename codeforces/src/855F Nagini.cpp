//
// Created by Psy.C on 2026/9/30.
//
/**
int mx;    // 区间最大值
    int tag;   // chmin 懒惰标记（-1 表示无标记）
    int cnt;   // 区间等于最大值 mx 的个数
    int sec;   // 区间严格次大值
    ll sum;    // 区间和

剪枝一：出界，或 v >= mx（chmin 无效），直接返回。
剪枝二（Beats 的灵魂）‍：若区间被完全覆盖且 v > sec（v 大于次大值，即除最大值外所有点都 < v），则这次 chmin 只会影响"等于最大值的那一批点"，可以在节点层面 O(1) 用 update 完成，不必下钻。
否则下传标记并递归左右儿子，再 push_up 合并。
复杂度均摊 O(n log n)：每个点被"降到次大值"的次数有限

对全量树 all 和答案树 ans 同时 chmin。
用 set<int> pos 维护"还没处理完的位置"，遍历 [L,R] 内未处理的位置，累加其被覆盖次数 cnt；当某位置第 2 次被全覆盖时，把 all 树对应值写入 ans 树该位置（固定最终答案）
正负数分开处理：负数取绝对值存到 neg 树，正数存到 pos 树。询问时输出两棵树区间和之和

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e6+10, inf = 1e9+10;

struct node {
    int mx, tag, cnt, sec;
    ll sum;
};

int L, R, n = 1e5;
struct sgt {
#define ls (rt<<1)
#define rs (rt<<1|1)
#define middef int mid=(l+r)>>1
    node t[N];

    void push_up(int rt){
        t[rt].sum=t[ls].sum+t[rs].sum;
        int u=ls,v=rs;
        if(t[u].mx==t[v].mx){
            t[rt].mx=t[v].mx;
            t[rt].cnt=t[u].cnt+t[v].cnt;//最大值个数相加
            t[rt].sec=max(t[u].sec,t[v].sec);//次大值 = 两子树次大值较大者
        }else{
            if(t[u].mx>t[v].mx)swap(u,v);//让 v 是较大者（max）
            t[rt].sec=max(t[u].mx,t[v].sec);//次大 = max(较小的mx, 较大者的sec)
            //最大值取较大的一方
            t[rt].mx=t[v].mx,t[rt].cnt=t[v].cnt;
        }
    }

    void update(int rt,int v){
        if(v<t[rt].mx){//只有 v 严格小于当前最大值才有效
            t[rt].sum+=1ll*(v-t[rt].mx)*t[rt].cnt;//把"等于最大值"的 cnt 个点降到 v，更新总和
            t[rt].mx=t[rt].tag=v;//最大值变为 v，打上 chmin 标记
        }
    }

    void push_down(int rt){
        if(~t[rt].tag){//有 chmin 标记
            update(ls,t[rt].tag);//下传给左右孩子
            update(rs,t[rt].tag);
            t[rt].tag=-1;
        }
    }

    void build(int l=1,int r=n,int rt=1){
        t[rt].tag=-1;
        if(l==r){
            t[rt].sum=t[rt].mx=inf;
            t[rt].cnt=1;
            return;
        }
        middef;
        build(l,mid,ls),build(mid+1,r,rs);
        push_up(rt);
    }

    void minimize(int v,int l=1,int r=n,int rt=1){
        if(l>R||r<L||v>=t[rt].mx)return;//出界 或 v 不小于区间最大值 → 直接返回
        //完全覆盖 且 v 大于次大值
        if((L<=l&&r<=R)&&(t[rt].sec<v))return update(rt,v);//只需改最大值那批，整节点 O(1) 处理
        push_down(rt);
        middef;
        minimize(v,l,mid,ls);
        minimize(v,mid+1,r,rs);
        push_up(rt);
    }
    //把某个位置的值直接设为 v（用于"某个位置达到两次条件后把对应答案固定下来"）
    void modify(int pos,int v,int l=1,int r=n,int rt=1){
        if(l==r){
            t[rt].mx=t[rt].sum=v;
            t[rt].cnt=1;
            return;
        }
        middef;
        push_down(rt);
        if(pos<=mid)modify(pos,v,l,mid,ls);
        else modify(pos,v,mid+1,r,rs);
        push_up(rt);
    }
    //单点查询：走到叶子返回 t[rt].sum
    int get_val(int pos,int l=1,int r=n,int rt=1){
        if(l==r)return t[rt].sum;
        middef;
        push_down(rt);
        if(pos<=mid)return get_val(pos,l,mid,ls);
        return get_val(pos,mid+1,r,rs);
    }
    //区间求和：标准线段树区间和（带 push_down/push_up）
    ll get_sum(int l=1,int r=n,int rt=1){
        if(l>R||r<L)return 0;
        if(L<=l&&r<=R)return t[rt].sum;
        push_down(rt);
        middef;
        long long ret=get_sum(l,mid,ls)+get_sum(mid+1,r,rs);
        push_up(rt);
        return ret;
    }
} pos_ans,neg_ans,pos_all,neg_all;

int cnt[N];
inline void modify(sgt &all,sgt &ans,set<int> &pos,int v){
    all.minimize(v);
    ans.minimize(v);
    for(auto it=pos.lower_bound(L);*it<=R;it=pos.erase(it)){
        cnt[*it]++;
        if(cnt[*it]==2){
            pos_ans.modify(*it,pos_all.get_val(*it));
            neg_ans.modify(*it,neg_all.get_val(*it));
        }
    }
}

set<int> pos_p,neg_p;
int q;
int main() {
    fast;
    cin>>q;
    for(int i=1;i<=n;++i)pos_p.insert(i),neg_p.insert(i);
    pos_all.build();
    neg_all.build();
    for(int i=1;i<=q;++i){
        int op,v;
        cin>>op>>L>>R;
        R--;
        if(op==1){
            cin>>v;
            if(v<0) modify(neg_all,neg_ans,neg_p,-v);
            else modify(pos_all,pos_ans,pos_p,v);
        }else cout<<pos_ans.get_sum()+neg_ans.get_sum()<<endl;
    }
    return 0;
}