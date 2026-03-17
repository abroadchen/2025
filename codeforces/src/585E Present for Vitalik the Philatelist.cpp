//
// Created by Psy.C on 2026/3/17.
//
/**
MAXN = 500000：输入元素最大个数
MAXM = 10000000：值域最大范围
n：输入元素个数
pw[MAXN+5]：2的幂次数组
c[MAXM+5]：每个数出现的次数
f[MAXM+5], g[MAXM+5]：动态规划数组
pr[]：素数数组
pcnt：素数个数
mu[]：莫比乌斯函数值
vis：埃拉托斯特尼筛法标记

初始化：μ(1) = 1
素数判断：若i未被标记，则为素数，μ(i) = -1
合数处理：
当i%pr[j]==0时：pr[j]是i的最小质因子，break
否则：μ(i*pr[j]) = -μ(i)

读入n
初始化2的幂次数组：pw[i] = 2^i % MOD
统计每个数的出现次数
对每个素数pr[i]，从大到小枚举其倍数
c[j]：包含因子j的数的个数
这个操作计算了每个数作为因子在多少个输入数中出现
f[i] = 2^c[i] - 1：包含因子i的子集数量（非空）
g[i] = c[i] * μ[i]：莫比乌斯函数的加权版本
类似于狄利克雷卷积的计算
g[d]最终表示与d相关的莫比乌斯变换结果
反向计算，去除包含更大因子的情况
这是莫比乌斯反演的思想
从2开始累加g[i]*f[i]
这是在计算某种数论函数的卷积

时间复杂度：
筛法：O(MAXM)
倍数枚举：O(MAXM log log MAXM)
DP转移：O(MAXM log log MAXM)
总体：O(MAXM)
空间复杂度：
O(MAXM)，主要是存储数组的空间

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int MAXN = 5e5, MAXM = 1e7, MOD = 1e9+7;

int n,pw[MAXN+5],c[MAXM+5],f[MAXM+5],g[MAXM+5];
int pr[MAXM/10+5],pcnt=0,mu[MAXM+5];
bitset<MAXM+5> vis;
void sieve(int n){
    mu[1]=1;
    for(int i=2;i<=n;i++){
        if(!vis[i]){pr[++pcnt]=i;mu[i]=-1;}
        for(int j=1;j<=pcnt&&pr[j]*i<=n;j++){
            vis[pr[j]*i]=1;
            if(i%pr[j]==0) break;
            else mu[i*pr[j]]=-mu[i];
        }
    }
}
int main(){
    scanf("%d",&n);pw[0]=1;sieve(MAXM);
    for(int i=1;i<=n;i++) pw[i]=pw[i-1]*2%MOD;
    for(int i=1,x;i<=n;i++) scanf("%d",&x),c[x]++;
    for(int i=1;i<=pcnt;i++) for(int j=MAXM/pr[i];j;j--) c[j]+=c[j*pr[i]];
    for(int i=1;i<=MAXM;i++) f[i]=pw[c[i]]-1,g[i]=c[i]*mu[i];
    for(int i=1;i<=pcnt;i++) for(int j=1;j*pr[i]<=MAXM;j++) g[j*pr[i]]+=g[j];
    for(int i=1;i<=pcnt;i++) for(int j=1;j*pr[i]<=MAXM;j++) f[j]=(f[j]-f[j*pr[i]]+MOD)%MOD;
    int ans=0;for(int i=2;i<=MAXM;i++) ans=(ans+1ll*g[i]*f[i])%MOD;
    printf("%d\n",ans);
    return 0;
}
