//
// Created by Psy.C on 2026/2/6.
//
/**
n(模式串数量), m(字符集大小), k(权值阈值)
rt=1: 根节点设为1
cn=1: 节点计数器，初始为1
tr[N][25]: trie树，最多N个节点，每个节点最多25个子节点
fail[N]: 失配指针数组
ans[N]: 每个节点的权值
g[N]: 邻接表存储图结构

向trie树插入一个字符串
u从根节点开始遍历
对于字符串的每个字符s[i]，如果没有对应子节点就创建新节点
在终点节点累加权值，不超过k+1

构建AC自动机的失配指针
BFS遍历所有节点，建立fail指针
将fail关系加入图中作为边
DFS遍历，将父节点的权值传递给子节点

T: AC自动机实例
L[N], R[N]: 左右边界数组
la, lb: 左右边界数组长度
f[205][205][505][2][2]: 记忆化搜索的DP数组
a[N]: 辅助数组

加法取模操作，确保结果在模M范围内
bt: 当前处理的位数
po: 当前在AC自动机中的位置
va: 当前累计权值
pl: 前导零标记
o: 是否开始填数字的标记
递归计算满足条件的方案数

printf返回打印字符数，取反后总是返回0，实现输出并正常退出
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define N 5005
#define M 1000000007
using namespace std;

int n,m,k;
struct ACAM{
    int rt=1,cn=1,tr[N][25],fail[N],ans[N]; vector<int>g[N];
    void addE(int x,int y){g[x].pb(y),g[y].pb(x);}
    void ins(int *s,int ln,int val){
        int u=rt;
        for(int i=0;i<ln;i++){//遍历字符串每个字符
            int &v=tr[u][s[i]];//当前字符对应的子节点引用
            if(!v) v=(++cn); u=v;//移动到子节点
        }ans[u]=min(ans[u]+val,k+1);
    }void build(){
        queue<int>q; q.push(1);//从根节点开始
        memset(fail,0,sizeof(fail));
        for(int i=0;i<m;i++) tr[0][i]=1;//设置虚拟节点0的所有转移指向根节点
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int i=0;i<m;i++)
                if(tr[u][i]) fail[tr[u][i]]=tr[fail[u]][i],q.push(tr[u][i]);
                else tr[u][i]=tr[fail[u]][i];//将不存在的转移指向fail节点的对应转移
            if(u>1) g[fail[u]].pb(u);//在fail树上添加边
        }
    }
    void dfs(int x) {
        for(int &u:g[x])//遍历节点x的所有子节点u
            ans[u]=min(ans[u]+ans[x],k+1),dfs(u);//将x的权值加到u上 递归处理子节点
    }
}T;
//位数、位置、权值、前导零状态、开始标志
int L[N],R[N],la,lb,f[205][205][505][2][2],a[N];
void inc(int &x,int y){x+=y; if(x>=M) x-=M;}
int dfs(int bt,int po,int va,int pl,int o){
    if(va>k) return 0;//权值超过k
    if(bt<0) return 1;//处理完所有位
    int &sum=f[bt][po][va][pl][o];//获取记忆化数组引用
    if(sum>=0) return sum;//已计算过
    sum=0;
    int ri=(pl?m-1:a[bt]);//当前位可填的最大数字
    for(int i=0;i<=ri;i++){//枚举当前位可填的数字
        //在AC自动机中转移到下一状态 更新是否已开始的标记 计算新的权值
        int nx=T.tr[po][i],ol=(o|(i>0)),v0=va+(ol?T.ans[nx]:0);
        //递归处理下一位并累加结果
        inc(sum,dfs(bt-1,ol?nx:po,min(v0,k+1),pl|(i<ri),ol));
    }return sum;
}signed main(){
    scanf("%d%d%d",&n,&m,&k),memset(f,-1,sizeof(f));
    scanf("%d",&la); for(int i=0;i<la;i++) scanf("%d",&L[i]);
    scanf("%d",&lb); for(int i=0;i<lb;i++) scanf("%d",&R[i]);
    reverse(L,L+la),reverse(R,R+lb);//从低位到高位处理
    for(int i=1;i<=n;i++){//读入n个模式串及其权值，插入到AC自动机中
        int ln,val; scanf("%d",&ln);
        for(int j=0;j<ln;j++) scanf("%d",&a[j]);
        scanf("%d",&val); T.ins(a,ln,val);
    }T.build(),T.dfs(T.rt);//更新权值
    for(int i=0;i<=lb;i++) a[i]=R[i];//小于等于右边界R的合法方案数
    int ans=dfs(lb-1,T.rt,0,0,0);
    memset(f,-1,sizeof(f)); int u=T.rt,sum=0;
    for(int i=0;i<=la;i++) a[i]=L[i];//小于等于左边界L的合法方案数
    ans=(ans+M-dfs(la-1,T.rt,0,0,0))%M;
    for(int i=la-1;~i;i--) sum=min(sum+T.ans[u=T.tr[u][L[i]]],k+1);
    return !printf("%d\n",ans+(sum<=k));//区间[L,R]内满足条件的数量加上L本身是否满足条件
}