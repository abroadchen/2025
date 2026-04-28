//
// Created by Psy.C on 2026/4/28.
//
/**
n,a,b: 问题参数（n个物品，a,b为限制条件）
g[2],G[2]: 两个滚动数组，记录某种状态
Ans: 最终答案
A[2005],B[2005]: 存储输入的两组数据
f[2]: 滚动数组，记录dp状态
重置f,g,G数组为0
Dec1,Dec2: 两个决策变量（可能是惩罚项）
循环处理n个物品
使用滚动数组优化空间（l^=1,r^=1实现0和1之间的切换）
复制上一状态的值
三种转移状态：
选择A[i]，减少Dec1惩罚，G增加1
选择B[i]，减少Dec2惩罚，g增加1
同时选择A[i]和B[i]，减去Dec1和Dec2惩罚，还要减去A[i]*B[i]的交叉项，g和G都增加1
返回G数组的最终值是否小于等于a（奇偶性取决于n的奇偶性）
在Dec固定的情况下，二分查找第一个参数的最优值
通过Solve函数验证条件
调整第二个参数Dec，并检查g[n&1]是否小于等于b

循环读取输入直到EOF
读取n,a,b三个参数
读取A数组和B数组的值
对第二个参数进行二分查找
找到满足条件的最优值
用找到的最优解再次计算
 */
#include <bits/stdc++.h>
#define EXP 1e-6
using namespace std;
int n,a,b,g[2],G[2];double Ans,A[2005],B[2005],f[2];
bool Solve(double Dec1,double Dec2){
    memset(f,0,sizeof(f));memset(g,0,sizeof(g));memset(G,0,sizeof(G));
    for(int i=1,l=0,r=1;i<=n;i++,l^=1,r^=1){
        f[r]=f[l],g[r]=g[l],G[r]=G[l];
        if(f[r]<f[l]+A[i]-Dec1) f[r]=f[l]+A[i]-Dec1,g[r]=g[l],G[r]=G[l]+1;
        if(f[r]<f[l]+B[i]-Dec2) f[r]=f[l]+B[i]-Dec2,g[r]=g[l]+1,G[r]=G[l];
        if(f[r]<f[l]+A[i]+B[i]-Dec1-Dec2-A[i]*B[i]) f[r]=f[l]+A[i]+B[i]-Dec1-Dec2-A[i]*B[i],g[r]=g[l]+1,G[r]=G[l]+1;
    }
    return G[n&1]<=a;
}
bool check(double Dec){
    double Now=0;
    for(double L=-1,R=3,mid=(R+L)/2;R-L>=EXP;mid=(R+L)/2) if(Solve(mid,Dec)) Now=R=mid;else L=mid;
    Solve(Now,Dec);f[n&1]+=Now*a;
    return g[n&1]<=b;
}
int main(){
    while(~scanf("%d%d%d",&n,&a,&b)){
        for(int i=1;i<=n;i++) scanf("%lf",A+i);
        for(int i=1;i<=n;i++) scanf("%lf",B+i);
        for(double L=-1,R=3,mid=(R+L)/2;R-L>=EXP;mid=(R+L)/2) if(check(mid)) Ans=R=mid;else L=mid;
        check(Ans);f[n&1]+=Ans*b;
        printf("%.6lf\n",f[n&1]);
    }
    return 0;
}