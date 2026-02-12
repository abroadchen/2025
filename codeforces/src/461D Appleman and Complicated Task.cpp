//
// Created by Psy.C on 2026/2/12.
//

#include<bits/stdc++.h>
#define int long long
#define pc putchar
#define mo 1000000007

using namespace std;
const int N=200005;
int n,k,f[N];
char s[5];
inline int read(){
    int ret=0,ff=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') ff=-1;ch=getchar();}
    while(isdigit(ch)){ret=ret*10+(ch^48);ch=getchar();}//字符转为数字
    return ret*ff;
}
//递归输出高位数字，最后输出个位
void write(int x){if(x<0){x=-x,pc('-');}if(x>9) write(x/10);pc(x%10+48);}

int ksm(int x,int y){
    int res=1;
    while(y){
        if(y&1) res=res*x%mo;
        y>>=1;
        x=x*x%mo;
    }
    return res;
}
int find(int x){
    return f[x]==-1?x:f[x]=find(f[x]);
}
bool merge(int x,int y){
    int tx=find(x),ty=find(y);
    if(find(x^1)==ty) return 0;//相反状态在同一集合
    if(find(y^1)==tx) return 0;
    if(tx!=ty) f[tx]=ty;
    return 1;
}
bool check(int l,int r,int t){
    if(t==0){//s[l]^s[r]=0
        return merge(l*2,r*2)&&merge(l*2+1,r*2+1);
    }
    //s[l]^s[r]=1
    return merge(l*2,r*2+1)&&merge(l*2+1,r*2);
}
signed main(){
    n=read(),k=read();
    memset(f,-1,sizeof(f));
    for(int i=1;i<=k;i++){
        int x=read()-1,y=read()-1;//转换为0基索引
        int l=x-y,r=x+y;
        if(l<0) l=-l;
        if(r>n-1) r=(n-1)*2-r;
        scanf("%s",s);//约束类型（'x'或'o'）
        if(!check(l,r+2,s[0]=='x'?0:1)){//约束冲突
            write(0);
            return 0;
        }
    }
    int ans=0;//并查集中独立连通分量的数量
    for(int i=0;i<=(n+2)*2;i++)
        if(find(i)==i)
            ans++;
    write(ksm(2,ans/2-2));//2的幂次表示方案数
    return 0;
}