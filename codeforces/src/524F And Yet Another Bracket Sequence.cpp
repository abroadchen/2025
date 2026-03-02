//
// Created by Psy.C on 2026/3/2.
//
/**
n：输入字符串长度
q[maxn]：单调队列数组
hd,tl：队列头部和尾部指针
a[maxn]：前缀和数组
tot：总和（'('数量 - ')'数量）
p：结果起始位置
N：扩展后的字符串长度（2n）
c[maxn]：哈希相关的幂次数组
h[maxn]：字符串哈希数组
s[maxn]：输入字符串

a[i]：前缀和数组（平衡值）
c[i]：c[i] = c[i-1] * 2（用于哈希）
h[i]：字符串哈希值
单调队列：维护a数组的单调递减队列
队尾操作：移除不满足条件的元素
队头操作：移除超出范围的元素
更新最优解：在满足条件时更新p
输出结果：输出最优的长度为n的子串
补充')'：根据tot值补充')'字符

反向计算：a[i]=a[i+1]-Get(s[i])，从后往前计算
反向处理：从N-1到1
队列操作：类似的单调队列维护
更新条件：检查a[q[hd]]>=a[i+n]
补充'('：当tot<0时，补充'('字符
输出结果：输出最优子串

字符串扩展：将原字符串复制一份到后面
总和计算：计算'('和')'的差值
 */
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2000005,ha=1e9+9;

///将字符转换为数值：'('为1，')'为-1
inline int Get(char x){ return x=='('?1:-1;}

inline int add(int x,int y){ x+=y; return x>=ha?x-ha:x;}

int n,q[maxn],hd,tl,a[maxn],tot,p,N;
int c[maxn],h[maxn];
char s[maxn];
///从位置x开始长度为len的子串的哈希值
inline int gethash(int x,int len){
    return add(h[x+len-1],ha-h[x-1]*(ll)c[len]%ha);
}
///比较从位置x和y开始的子串的字典序
inline bool cmp(int x,int y){
    int l=0,r=n,mid,an=0;//最长公共前缀长度an
    while(l<=r){
        mid=l+r>>1;
        if(gethash(x,mid)==gethash(y,mid)) an=mid,l=mid+1;
        else r=mid-1;
    }
    return an==n?1:s[x+an]=='(';
}
///!p表示p未初始化，或cmp(x,p)表示x更优
inline void update(int x){ if(!p||cmp(x,p)) p=x; }

inline void solve1(){
    c[0]=1;
    for(int i=1;i<=N;i++){
        a[i]=a[i-1]+Get(s[i]);
        c[i]=add(c[i-1],add(c[i-1],c[i-1]));
        h[i]=add(add(h[i-1],add(h[i-1],h[i-1])),(s[i]=='('?1:2));
    }

    hd=1,tl=0;
    for(int i=1;i<N;i++){
        while(hd<=tl&&a[i]<=a[q[tl]]) tl--;
        q[++tl]=i;
        while(hd<=tl&&q[hd]+n<=i) hd++;
        if(i>=n&&a[q[hd]]>=a[i-n]) update(i-n+1);
    }
    for(int i=0;i<n;i++) putchar(s[p+i]);
    for(int i=1;i<=tot;i++) putchar(')');
}

inline void solve2(){
    c[0]=1;
    for(int i=1;i<=N;i++){
        c[i]=add(c[i-1],add(c[i-1],c[i-1]));
        h[i]=add(add(h[i-1],add(h[i-1],h[i-1])),(s[i]=='('?1:2));
    }
    for(int i=N;i;i--) a[i]=a[i+1]-Get(s[i]);
    hd=1,tl=0;
    for(int i=N-1;i;i--){
        while(hd<=tl&&a[i]<=a[q[tl]]) tl--;
        q[++tl]=i;
        while(hd<=tl&&q[hd]-n>=i) hd++;
        if(i<=n&&a[q[hd]]>=a[i+n]) update(i);
    }
    for(int i=tot;i<0;i++) putchar('(');
    for(int i=0;i<n;i++) putchar(s[p+i]);
}

int main(){
    scanf("%s",s+1),n=strlen(s+1),N=n<<1;
    for(int i=1;i<=n;i++) s[i+n]=s[i],tot+=Get(s[i]);
    if(tot>=0) solve1(); else solve2();
    return 0;
}