//
// Created by Psy.C on 2026/2/12.
//
/**
l, r: 范围边界
k: 可使用的最大元素数
ans: 存储找到的最小XOR结果
vis: 跟踪选择的数字（位掩码）

x: 正在考虑的当前数字
tmp: 当前XOR值
lala: 指示选择哪些数字的位掩码
cnt: 选择的数字计数
尝试包含和排除每个数字x
当找到更好的解决方案时更新ans和vis


情况1：小范围（r-l <= 10）
使用DFS暴力尝试所有组合：

检查[l, r]中最多k个元素的所有可能子集
找到给出最小XOR值的组合
输出结果、位数和选择的数字
情况2：k = 1
简单输出l，因为使用一个数字得到最小XOR值。

情况3：k = 2
强制两个连续数字的XOR以获得1（最小化XOR的最佳选择）。

情况4：k >= 4
使用巧妙的构造方法，其中4个数字的XOR为0：

对于奇数l：使用l+1, l+2, l+3, l+4
对于偶数l：使用l, l+1, l+2, l+3
因为对于任何x，其中x%4=0，有x ⊕ (x+1) ⊕ (x+2) ⊕ (x+3) = 0
情况5：k=3的复杂情况
这是最有趣的部分：

找到最高位位置m，使得2^m > l
检查2^m + 2^(m-1) ≤ r
如果是，构造三个数字：(2^m)-1, 2^m + 2^(m-1), (2^m + 2^(m-1))-1
这三个数字的XOR = 0，这是最优的



对于小范围：O(2^(r-l+1)) - 指数级但小范围内可处理
对于大范围：O(log(max(l,r))) - 非常高效
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;

int l,r,k,ans,vis;

inline void dfs(int x,int tmp,int lala,int cnt){
    if(lala)//至少选择了一个数字
        if(ans>=tmp)//当前XOR值更优（更小或相等）
            ans=tmp,vis=lala;//更新最小XOR值和对应的位掩码
    if(x==r+1||cnt>k)//已考虑完所有范围内的数字 选择的数字已经超过限制k
        return;
    dfs(x+1,tmp,lala,cnt);dfs(x+1,tmp^x,lala|(1<<x-l),cnt+1);
    //对应范围中一个数字的选择状态
    //cnt+1：选择当前数字后总数+1
}

signed main(){
    scanf("%lld%lld%lld",&l,&r,&k);
    if(r-l<=10){
        ans=r;dfs(l,0,0,1);printf("%lld\n",ans);ans=vis;int cnt=0;
        while(ans)
            cnt+=ans&1,ans>>=1;
        printf("%lld\n",cnt);cnt=0;
        while(vis){
            if(vis&1)
                printf("%lld ",l+cnt);
            cnt++,vis>>=1;
        }
        puts("");
    }
    else if(k==1)
        printf("%lld\n1\n%lld\n",l,l);
    else if(k==2){//强制两个连续数字的XOR以获得1
        puts("1");puts("2");
        if(l&1)
            printf("%lld %lld",l+1,l+2);
        else
            printf("%lld %lld",l,l+1);
    }
    else if(k>=4){
        puts("0");puts("4");
        if(l&1){
            for(int i=l+1;i<=l+4;i++)
                printf("%lld ",i);
            puts("");
        }
        else{
            for(int i=l;i<=l+3;i++)
                printf("%lld ",i);
            puts("");
        }
    }
    else{
        int m,L=1,R=62;
        while(L<=R){
            int mid=(L+R)>>1;
            if((1LL<<mid)>l)
                m=mid,R=mid-1;
            else
                L=mid+1;
        }
        if(m==0){
            puts("1");puts("2");
                if(l&1)
                    printf("%lld %lld",l+1,l+2);
                else
                    printf("%lld %lld",l,l+1);
        }
        else{
            if((1LL<<m)+(1LL<<m-1)>r){
                puts("1");puts("2");
                if(l&1)
                    printf("%lld %lld",l+1,l+2);
                else
                    printf("%lld %lld",l,l+1);
            }
            else{
                puts("0");puts("3");int x=(1LL<<m)-1,y=(1LL<<m)+(1LL<<m-1),z=(1LL<<m)+(1LL<<m-1)-1;
                printf("%lld %lld %lld\n",x,y,z);
            }
        }
    }
    return 0;
}
