//
// Created by Psy.C on 2026/3/25.
//
/**
转移边，ch[c]表示通过字符c转移到的节点
该节点表示的最长子串长度
后缀链接（fail指针），指向长度恰好为len-1的最长后缀
后缀自动机的节点数组

O(总字符串长度)
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 5e5+5, M = 1e6+5, P = 1e5+5;

struct node { int ch[26], len, fa; } t[M];

int cnt = 1;///节点计数器，1表示根节点
///在节点x后添加字符c，返回新的状态节点
int add(int x, int c) {
    if(t[x].ch[c]){//已经有通过字符c的转移
        int y=t[x].ch[c];//获取目标节点
        if(t[y].len==t[x].len+1)return y;//y的长度正好是x+1，直接返回
        int yy=++cnt;t[yy]=t[y];//创建新节点yy，复制y的内容
        t[yy].len=t[x].len+1,t[y].fa=yy;//更新yy的长度和y的后缀链接
        for(;x&&t[x].ch[c]==y;x=t[x].fa)t[x].ch[c]=yy;//更新所有指向y的转移
        return yy;
    }
    //没有通过字符c的转移，创建新节点
    int xx=++cnt;t[xx].len=t[x].len+1;
    for(;x&&!t[x].ch[c];x=t[x].fa)t[x].ch[c]=xx;//在后缀链接路径上添加转移
    if(!x){t[xx].fa=1;return xx;}//到达根节点，设置后缀链接为根
    int y=t[x].ch[c];//获取目标节点
    if(t[y].len==t[x].len+1){t[xx].fa=y;return xx;}//长度合适，直接设置后缀链接
    //需要分裂节点
    int yy=++cnt;t[yy]=t[y];
    t[yy].len=t[x].len+1;
    t[y].fa=t[xx].fa=yy;//设置后缀链接
    for(;x&&t[x].ch[c]==y;x=t[x].fa)t[x].ch[c]=yy;//更新转移
    return xx;
}

vector<int> v[M];///构建后缀链接树的邻接表
ll f[M];///每个节点的权值（子串出现次数）
///每个节点的子树权值和
void dfs(int x) {
    for (auto y : v[x])
        dfs(y), f[x] += f[y];
}
///n为字符串数量，S为当前字符串长度
int n, len, S;
char s[N];///临时字符串缓冲区
vector<int> id[P];///每个字符串在后缀自动机中的路径
ll res;
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",s),S=strlen(s);//读入第i个字符串
        //逐步添加字符，记录路径
        for(int j=0,las=1;j<S;j++)id[i].push_back(las=add(las,s[j]-'a'));
    }
    //为每个字符串的路径节点赋予权值
    for(int i=1,x;i<=n;i++){
        scanf("%d",&x);//读入第i个字符串的权值
        for(auto j:id[i])f[j]+=x;//将权值累加到路径上所有节点
    }
    for(int i=2;i<=cnt;i++)v[t[i].fa].push_back(i);//构建后缀链接树
    dfs(1);//每个节点的子树权值和（即该子串在所有字符串中的总权值）
    //寻找最大值：f[i] * t[i].len（权值 × 子串长度）
    for(int i=1;i<=cnt;i++)res=max(res,f[i]*t[i].len);
    printf("%lld\n",res);
    return 0;
}