//
// Created by Psy.C on 2026/9/22.
//
/**
w 是阈值，只有 ≥ 某界限的父节点才继续扩张；x 从 n 开始不断 x/=2，等价地一层层把"向下可生成的节点集合"拆小。
s1、s2 分别代表两条扩展链（对应 2x 与 2x+1 的方向）各自还能扩出的规模；每多展开一层就把 s1+s2 累进 tt。
复杂度 O(log n)
取中位数 md 作为二叉树的分割点。
用 solve 算出左右两半各贡献多少个数（v1、v2），中位本身算 1 个。
若第 k 个比 v1+v2+1 还大 → 结果在右半，跳到 [md+1, r] 并把 k 减去左半与中位个数；否则落在左半。
这正是 Common Number 里"按 fun 排序后取第 k 个"的分治实现，复杂度 O((log n)²)
前两个位置（1 和 n）被单独处理。
二分确定一个"最合适的阈值 rs"，保证 solve(n-2, rs) ≥ K 且 rs 尽量大——对应 Common Number 中用于筛出第 K 个的临界参数。
最后 work(2, n-1, rs, K) 在去掉两端的区间内精确定位第 K 个并输出
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;

inline int solve(int n,int w) {
    int x=n,y=n-1,s1=1,s2=0,tt=0;
    if(x<=w*2) return 0;//规模太小，直接贡献 0
    for(;y>=w*2;x/=2,y=x-1) {//按 x/=2 逐层拆解
        if(y==w*2) return tt+s1;//y 触到阈值，提前收口
        tt+=s1+s2;//累加已展开层贡献
        if(x&1) s1=2*s1+s2;//奇节点：两分支 + 收敛
        else s2=2*s2+s1;
    }
    return tt;
}
inline int work(int l,int r,int p,int k) {
    int md=(l+r)>>1;
    if(k==1) return md;//本区间的第 1 个就是中位
    //左半数量 右半数量(阈值+1)
    int v1=solve(md-l,p),v2=solve(r-md,p+1);
    if(k>v1+v2+1) return work(md+1,r,p,k-v1-1);//落在右半
    return work(l,md-1,p,k-v2-1);
}

template<class T>
void read(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

template<typename T,typename... Args>
void read(T& t,Args&... args) {
    read(t); read(args...);
}

signed main() {
    int n,K;read(n,K);if(K==1) return puts("1"),0;
    if(K==2) return printf("%lld\n",n),0;
    K-=2;//之后从第 3 个算起
    int l=1,r=n/2+1,rs=0;
    while(l<=r) {
        int md=(l+r)>>1;
        if(solve(n-2,md)>=K) rs=md,l=md+1;//足够则阈值可再大
        else r=md-1;
    }
    return printf("%lld\n",work(2,n-1,rs,K)),0;
}