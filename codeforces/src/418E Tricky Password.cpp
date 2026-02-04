//
// Created by Psy.C on 2026/2/3.
//
/**
* const int S=1000;  // 块大小，每块包含1000个元素
int a[100010];     // 存储原始值的编号
int f[110][200010]; // f[block_id][value] = 该值在块中的出现次数
int g[110][200010]; // g[block_id][freq] = 出现freq次的数字个数
int val[200010];   // val[id] = 原始值
map<int,int>mp;    // 映射原始值到编号
int M;             // 当前使用的编号总数
 *
 *将原始值映射到连续的编号空间
 *
*f[block][value] 记录值在该块中的出现次数
g[block][freq] 记录在该块中有多少个数出现了freq次
 *
*删除y位置原来的值在各块中的统计
更新y位置的新值
在各块中加入新值的统计
 *
*如果x==1，直接输出y位置的值
否则临时统计从块开头到位置y的频次信息
如果x是奇数，查询有多少个数与a[y]具有相同的出现频率
如果x是偶数，查询a[y]在当前块中的出现次数
清除临时统计信息
 *
*时间复杂度：修改O(√n)，查询O(√n)
空间效率：通过分块减少空间使用
 */
#include<stdio.h>
#include<string.h>
#include<map>
using namespace std;
const int S=1000;
int a[100010],f[110][200010],g[110][200010],val[200010],M;
map<int,int>mp;
int num(int x){
    if(!mp.contains(x)){
        M++;
        mp[x]=M;
        val[M]=x;
    }
    return mp[x];
}
int main() {
    int n,m,i,j,x,y,z;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&x);
        a[i]=num(x);
    }
    x=0;
    for(i=1;i<=n;i+=S){
        z=min(i+S-1,n);
        memcpy(f[(i-1)/S+1],f[(i-1)/S],sizeof(f[(i-1)/S]));
        memcpy(g[(i-1)/S+1],g[(i-1)/S],sizeof(f[(i-1)/S]));
        for(j=i;j<=z;j++){
            f[(i-1)/S+1][a[j]]++;
            g[(i-1)/S+1][f[(i-1)/S+1][a[j]]]++;
        }
    }
    scanf("%d",&m);
    while(m--){
        scanf("%d%d%d",&i,&x,&y);
        if(i==1){
            for(i=(y-1)/S+1;(i-1)*S+1<=n;i++){
                g[i][f[i][a[y]]]--;
                f[i][a[y]]--;
            }
            a[y]=num(x);
            for(i=(y-1)/S+1;(i-1)*S+1<=n;i++){
                f[i][a[y]]++;
                g[i][f[i][a[y]]]++;
            }
        }else{
            if(x==1){
                printf("%d\n",val[a[y]]);
                continue;
            }
            for(i=(y-1)/S*S+1;i<=y;i++){
                f[(y-1)/S][a[i]]++;
                g[(y-1)/S][f[(y-1)/S][a[i]]]++;
            }
            printf("%d\n",(x&1)?g[(y-1)/S][f[(y-1)/S][a[y]]]:f[(y-1)/S][a[y]]);
            for(i=(y-1)/S*S+1;i<=y;i++){
                g[(y-1)/S][f[(y-1)/S][a[i]]]--;
                f[(y-1)/S][a[i]]--;
            }
        }
    }
}