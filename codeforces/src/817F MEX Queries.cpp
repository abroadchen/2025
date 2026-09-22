//
// Created by Psy.C on 2026/9/22.
//
/**
l, r：该区间覆盖 [l, r]；val 是区间值。
mutable int val：mutable 允许在 set 迭代器上直接修改 val（set 元素默认 const，但 val 不在排序键里，故标记 mutable 以便 rever 中 it->val=!it->val 能改值而无需重插）。
operator<：只按 l 排序 → set 里的区间按左端点递增排列，且保证互不重叠（通过 split/assign 维护）。
set<node> s + 两个迭代器 il, ir 用于区间擦除
先 lower_bound 找到左端点 ≥ pos 的第一个区间。
若它的左端点恰好等于 pos → 不用切，直接返回。
否则 --it 得到真正包含 pos 的区间，记录 l,r,v，删除原区间，再按 [l,pos-1] 和 [pos,r] 两段插回，返回右半段迭代器
先 split(r+1)（保证右边界的右边正确），再 split(l)（保证左边界的左边正确），顺序很重要——先切右再切左，避免迭代器失效。
s.erase(il, ir) 一次性删掉从 il 到 ir 之前的所有区间（即 [l, r] 整段）。
插入单一的 [l, r, val]，完成"推平赋值"
同样先 split 边界。
遍历 [il, ir) 覆盖的每个小区间，把它们的 val 取反——因为 mutable，可以直接 it->val = !it->val，不需要重新插回 set
初始把整条[1, 1e18+1] 全部置 0（该数据结构假设区间长度巨大、值较少变化）。
每次读入一条操作，执行对应的 assign / rever。
每轮末尾：从头遍历 set，找到第一个值为 0 的区间，输出它的左端点并跳出——这就是"当前最靠左的 0 的位置"
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int inf = 1e18;

struct node {
    int l, r;
    mutable int val;
    bool operator<(const node& o) const {
        return l < o.l;
    }
};
set<node> s;
set<node>::iterator it, il, ir;
inline auto split(int pos) {
    it=s.lower_bound(node({pos}));
    if(it!=s.end()&&it->l==pos)//已存在以 pos 为左端点的区间，直接返回
        return it;
    --it;//否则 pos 落在 it 前一个区间里
    int l=it->l,r=it->r,v=it->val;
    s.erase(it);//删除原区间
    s.insert(node({l,pos-1,v}));
    return s.insert(node({pos,r,v})).first;//右半 [pos, r]，返回它的迭代器
}
inline void assign(int l, int r, int val) {
    ir=split(r+1),il=split(l);
    s.erase(il,ir);//删除 [l, r] 覆盖的所有旧区间
    s.insert(node({l,r,val}));//整段合并为一个新区间
}
inline void rever(int l, int r) {
    ir=split(r+1),il=split(l);
    for(it=il;it!=ir;++it) it->val=!it->val;
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

signed main() {
    int n=read();
    s.insert(node({1,(int)1e18+1,0}));
    while(n--){
        int flag=read(),l=read(),r=read();
        if(flag==1)
            assign(l,r,1);
        else if(flag==2)
            assign(l,r,0);
        else if(flag==3)
            rever(l,r);
        for(it=s.begin();it!=s.end();++it)
            if(!it->val){
                printf("%lld\n",it->l);
                break;
            }
    }
    return 0;
}