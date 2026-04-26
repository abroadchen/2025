//
// Created by Psy.C on 2026/4/25.
//
/**
递归实现的二分查找
在区间[l,r)中查找满足条件的最左位置
d+mid>fl 是判断条件，寻找第一个使得d+mid>fl不成立的位置

验证给定限制lim是否可行
dis = p[i]-p[i-1]：相邻两个位置的距离差
k = loc(0,dis+1,dis,lim)-1：找到某个关键位置
判断总时间是否超过限制t

递归实现的二分搜索
寻找满足条件的最小值
如果check(mid)为真，说明mid满足条件，向左搜索；否则向右搜索

n：物品数量
m：位置数量
p[0]：起始位置
t：时间限制
c[i], w[i]：第i个物品的代价和权重
p[i]：第i个位置坐标

首先验证最大权重是否可行，不可行则输出-1
使用二分搜索找到临界阈值
找出所有权重大于等于阈值的物品中代价最小的一个
时间复杂度约为 O(m log²(dis) + n log(max_weight))，其中log²项来自于嵌套的二分搜索

将起始位置添加到位置数组末尾
p[0] = 0 作为标准化起点，方便计算相对距离
w[0] 存储最大权重，作为二分搜索的上界
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+7, inf = 1e9;

int loc(int l,int r,int d,int fl){
    if(l>=r)return l;
    int mid=l+r>>1;
    if(d+mid>fl)return loc(l,mid,d,fl);
    return loc(mid+1,r,d,fl);
}

int m, p[N], t;
bool check(int lim){
    int now=0;
    for(int i=1;i<=m;i++){
        int dis=p[i]-p[i-1];
        int k=loc(0,dis+1,dis,lim)-1;
        if(k<0||dis+dis-k+now>t)return false;
        now+=dis+dis-k;
    }
    return true;
}
int Search(int l,int r){
    if(l>=r)return l;
    int mid=l+r>>1;
    if(check(mid))return Search(l,mid);
    return Search(mid+1,r);
}

int n, c[N], w[N], res, ans = inf;
int main() {
    scanf("%d%d%d%d",&n,&m,&p[0],&t);
    for(int i=1;i<=n;i++)scanf("%d%d",&c[i],&w[i]),w[0]=max(w[0],w[i]);
    for(int i=1;i<=m;i++)scanf("%d",&p[i]);
    sort(p+1,p+m+1);p[++m]=p[0];p[0]=0;
    if(!check(w[0]))return puts("-1"),0;
    res=Search(1,w[0]);
    for(int i=1;i<=n;i++)if(w[i]>=res)ans=min(ans,c[i]);
    printf("%d\n",ans);
    return 0;
}