//
// Created by Psy.C on 2026/2/4.
//
/**
* if(((i>>k)&1)!=a[k][j])
即判断第k行第j列是否需要翻转。
 *
*情况1：O(n²m)
情况2：O(2ⁿm)
总体：取决于k与n的关系
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[110][110];
int main(){
    int n,m,k;
    while(~scanf("%d%d%d",&n,&m,&k)){
        for(int i=0;i<n;++i)for(int j=0;j<m;++j)scanf("%d",a[i]+j);
        int ans=k+1;//作为不可能达到的大值
        if(k<n){
            for(int i=0;i<n;++i){//以每一行i作为基准
                int tmp=0;//以第i行为基准的总代价
                for(int j=0;j<n;++j){//计算与所有行j的差异
                    int dis=0;//当前两行的汉明距离
                    for(int k=0;k<m;++k)
                        dis+=(a[i][k]^a[j][k]);//第i行和第j行在第k列的异或值
                    tmp+=min(dis,m-dis);//是否翻转这一行
                }
                ans=min(ans,tmp);//更新最小代价
            }
        }
        else {
            for(int i=(1<<n)-1;i>=0;--i){//枚举所有可能的翻转状态（2^n种）
                int tmp=0;
                for(int j=0;j<m;++j){
                    int dis=0;
                    for(int k=0;k<n;++k)
                        if((i&(1<<k))==(a[k][j]<<k))//第k位是否为1
                            dis++;
                    tmp+=min(dis,n-dis);
                }
                ans=min(ans,tmp);
            }
        }
        if(ans==k+1)puts("-1");
        else printf("%d\n",ans);
    }
    return 0;
}