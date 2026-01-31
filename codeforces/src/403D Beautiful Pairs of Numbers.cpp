//
// Created by Psy.C on 2026/1/31.
//
/**
 *默认b=mod-2（用于计算模逆元）
*sum[2][N][N]：滚动数组，用于动态规划
sm[M][N]：前缀和数组
ans[N][M]：最终答案数组
f[N*2]：阶乘数组
fav[N*2]：阶乘的模逆元数组
 *
 *初始化第一行的前缀和
*p^=1：滚动数组切换（0和1之间切换）
z<=j：确保合法状态
sum[p^1][j-z][z-1]：从上一层状态转移
 *
 *sm[k][j] * C(n-j+k, n-j)
 *k*(k+1)/2 是k个不同正整数的最小和（1+2+...+k）
 *
 *
 */
#include<iostream>
using namespace std;
#define int long long
const int N=1005,M=45,mod=1e9+7;
int qpow(int a,int b=mod-2){a=(a%mod+mod)%mod;int res=1;while(b){if(b&1)res=res*a%mod;a=a*a%mod;b>>=1;}return res;}
int sum[2][N][N],sm[M][N];
int ans[N][M];
int f[N*2],fav[N*2];
void init(){
    sum[0][0][0]=f[0]=fav[0]=f[1]=fav[1]=1;

    for(int i=2;i<N*2;i++)f[i]=f[i-1]*i%mod,fav[i]=fav[i-1]*qpow(i)%mod;

    for(int j=1;j<N;j++)sum[0][0][j]+=sum[0][0][j-1];

    for(int i=1,p=1;i<M;i++,p^=1)
        for(int j=0;j<N;j++){
            sum[p][j][0]=0;
            for(int z=1;z<N;z++){
                sum[p][j][z]=sum[p][j][z-1];
                if(z<=j){
                    int x=sum[p^1][j-z][z-1];
                    sum[p][j][z]=(sum[p][j][z]+x)%mod;
                    sm[i][j]=(sm[i][j]+x)%mod;
                }
            }
        }
    for(int n=1;n<N;n++)
        for(int k=1;k<M;k++)
            for(int j=1;j<=n;j++)
                ans[n][k]=(ans[n][k]+sm[k][j]*f[n-j+k]%mod*fav[n-j]%mod)%mod;
}
void work(){
    int n,k;
    cin>>n>>k;
    if(k*(k+1)/2>n)cout<<"0\n";
    else cout<<ans[n][k]<<"\n";
}
signed main(){
    init();
    int _=1;cin>>_;
    while(_--) work();
    return 0;
}