//
// Created by Psy.C on 2026/3/17.
//
/**
n: 字符串s的长度
m: 字符串a的长度
tot: AC自动机节点总数
ch[i][j]: AC自动机第i个节点的第j个字符的子节点编号
fail[i]: AC自动机第i个节点的失配指针
dep[i]: 第i个节点在Trie树中的深度
dp[...][...][...][...]: 四维DP数组，用于数位DP
now: 当前使用的DP数组索引

s: 主字符串
a, b: 范围边界值
将x对mod取模，确保结果为正数
向AC自动机构建Trie树，从位置x开始插入s的后缀
node=0: 从根节点开始
遍历从位置x到n的字符
如果当前节点没有对应字符的子节点，则创建新节点
更新节点深度
构建AC自动机的失配指针（KMP思想）
将所有根节点的子节点加入队列
BFS遍历，构建fail指针
如果存在子节点，设置其fail指针；否则将其指向fail[k]对应字符的子节点

memset(dp,0,sizeof dp): 初始化DP数组
dp[0][1][0][0]=1: 初始状态，表示第一位、限制状态、匹配状态、节点
lim=str[i]-'0': 当前位置的最大数字限制
now^=1: 交替使用两个DP层以节省空间
j&&g==lim: 是否仍受上界限制
k||dep[ch[p][g]]>=(m>>1): 是否已经匹配到目标模式串
最后统计所有匹配成功的方案数

读入主串s和范围[a,b]
为了计算区间[a,b]内的计数，转换为solve(b)-solve(a-1)
将a减1得到a-1（处理借位）
为每个位置开始的后缀构建AC自动机
构建fail指针
输出结果，即在[b+1,a]范围内满足条件的数量

 */
#include <bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,m,tot,ch[500001][11],fail[500001],dep[500001],dp[2][2][2][500001],now;
string s,a,b;
inline int Mod(int x) {
    return x>=mod? x-mod:x;
}
inline void insert(int x) {
    int node=0;
    for(int i=x;i<=n;++i) {
        if(!ch[node][s[i]-'0']) {
            ch[node][s[i]-'0']=++tot;
            dep[tot]=dep[node]+1;
        }
        node=ch[node][s[i]-'0'];
    }
}
inline void getfail() {
    queue<int> q;
    for(int i=0;i<10;++i)
        if(ch[0][i])
            q.emplace(ch[0][i]);
    while(!q.empty()) {
        int k=q.front();
        q.pop();
        for(int i=0;i<10;++i)
            if(ch[k][i]) {
                fail[ch[k][i]]=ch[fail[k]][i];
                q.emplace(ch[k][i]);
            }
            else
                ch[k][i]=ch[fail[k]][i];
    }
}
inline int solve(string str) {
    memset(dp,0,sizeof dp);
    now=0;
    dp[0][1][0][0]=1;
    for(int i=1;i<=m;++i) {
        int lim=str[i]-'0';
        now^=1;
        memset(dp[now],0,sizeof dp[now]);
        for(int j=0;j<2;++j)
            for(int k=0;k<2;++k)
                for(int p=0;p<=tot;++p)
                    if(dp[now^1][j][k][p])
                        for(int g=0;g<=(j? lim:9);++g)
                            dp[now][j&&g==lim][k||dep[ch[p][g]]>=(m>>1)][ch[p][g]]=
                                Mod(dp[now][j&&g==lim][k||dep[ch[p][g]]>=(m>>1)][ch[p][g]]+dp[now^1][j][k][p]);
    }
    int res=0;
    for(int i=0;i<2;++i)
        for(int j=0;j<=tot;++j)
            res=Mod(res+dp[now][i][1][j]);
    return res;
}
int main() {
    cin>>s>>a>>b;
    n=s.length(); m=a.length();
    s=" "+s; a=" "+a; b=" "+b;
    --a[m];//先将最低位减1
    for(int i=m;i>=1&a[i]<'0';--i) {
        a[i]='9';
        --a[i-1];//向高位借位
    }
    for(int i=1;i<=n;++i)
        insert(i);
    getfail();
    cout<<Mod(solve(b)-solve(a)+mod)<<'\n';
    return 0;
}