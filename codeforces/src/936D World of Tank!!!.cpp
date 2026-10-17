//
// Created by Psy.C on 2026/10/17.
//
/**
pre[N][2]：DP 回溯标记（当前状态是由「上一个相同状态」还是「状态翻转」转移来的），用于方案输出。
mp[2][N]：标记某个合并后的坐标点在"类型 0/1"的区间序列里是否处于活动（覆盖）状态。
sh[N] / ls：用于输出一种"shift/开关"方案。
a[N]：合并后去重的关键坐标数组（离散化的时间轴）。
tr[N] / lt：输出普通节点序列。
dp[N][2]：双状态 DP。两种状态 0/1，表示当前处于哪种覆盖模式。
可以理解为：有两类区间集合（b 序列和 c 序列），每类里有若干段"开启"位置，需要判断能否用这若干段拼出 [0, n] 的完整覆盖，并输出操作

手写快输 ll。
负数先输出 -。
把 x 的各位数字从低位存进 p 数组（p[1] 存个位），cnt 表示位数。
从高位往低位依次 putchar(p[cnt--]^48)，^48 把数字转成 ASCII 字符（'0'=0x30, 0x30 与数字异或 0x30 的自己得到 ASCII）。
若指定了结尾字符 c>0 就补上（默认换行）

从 DP 终点 (x,y) 逆推路径。
pre[x][y]==1：当前状态是从 dp[x-1][y] 直接继承来的（不翻转状态）→ x-- 往前退。
并且若 mp[y][x] 为真（这个坐标在类型 y 的区间内处于覆盖状态），则记录一个 sh 值：((a[x]-dp[x][y]+1)<<1)+y，编码了位置和类型。
pre[x][y]==0：当前状态是由状态翻转转移来的 → 记录节点 a[x] 到 tr，把 pre 标记为 1（防重），并翻转状态 y^=1。
循环条件 while(x||y)：直到 x 到 0 且 y 到 0 为止

读入：n 总长度、m1/m2 两类区间个数、t（切换代价/时间）。
对第 1 类的 m1 个位置：把 rd() 存到 b[++n1]，再存一个 b[n1]+1（右端点+1，形成 [l, r+1] 开区间），n1 再 +1。因此每个输入点展开成"一个点的左端 + 右端"两个坐标，存进 b。
对第 2 类 c 同理；即 b 和 c 各自存了"每个区间的左右端点坐标"
双指针归并排序 b 和 c（假定各自已有序），同时去重：若 a[m] != b[i] 才把 b[i] 加入坐标轴 a。
i&1 判断：由于 b 里每条区间被展开成 [左,右] 两个相邻坐标，奇偶可以判断当前是区间的开启端还是结束端。i&1 为真（奇数）表示这是某条区间的左端点/活跃起始，于是把 mp[0][m]=1（类型 0 在这个合并坐标处处于活动状态）。
对 j / 类型 1 同理
归并完成后，把两序列剩余的尾巴各自接上（同样去重、按奇偶设 mp）。
结果：a[1..m] 是所有关键坐标去重后的有序时间轴，mp[0][k]/mp[1][k] 表示在第 k 个坐标处类型 0/1 是否"处于区间内"
若最后一个坐标 <= n，补一个哨兵 n+1 作终点，保证覆盖到 n

dp[0][0]=dp[0][1]=1：初值，从坐标 0 出发，两个状态都可行（值为1表示已能覆盖到状态0且...）。

第一重内层循环 for j in 0..1，若 dp[i-1][j]>0（前一个坐标、状态 j 可达）：

dp[i][j] = dp[i-1][j] + (a[i]-a[i-1]) - mp[j][i]*t：
状态不变（继承 j），走过的真实长度增加 a[i]-a[i-1]；
若 mp[j][i]（在类型 j 的区间覆盖内），消耗 t（切换/代价）。
标记 pre[i][j]=1（表示从同状态前驱继承）。
特殊：若 mp[j][i] 且 dp[i][j]==1（此处被重置到 1 的临界），置 0 表示某边界情况失效。
第二重内层循环 for j in 0..1，若 dp[i][j^1]>0（另一状态 j^1 可达），且当前 不在 mp[j][i] 覆盖内（!mp[j][i]），且 min(dp[i][j^1], 1+t) > dp[i][j]：

状态翻转（从 j^1 翻到 j），代价取 min(dp[i][j^1], 1+t)，更新 dp[i][j]。
pre[i][j]=0（表示由翻转转移来）。
j=2：由于是 for 循环且循环变量是 j，这里赋 j=2 让循环提前终结（j<2 条件不再满足），实现"只处理一次翻转"

若终点坐标 m 的两个状态至少一个有解 → Yes。
从 dp[m][0]、dp[m][1] 较大的那个状态调用 dfs 回溯出方案：
print(lt)：输出第一种方案的元素个数；
倒序输出 tr（位移路径节点）；
print(ls)：输出第二种方案的个数；
对每个 sh[i]，sh[i]>>1 是坐标、(sh[i]&1)+1 是类型编号（0/1 → +1 → 1/2），依次输出。
否则无解 → No
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 3e6+5;

bool pre[N][2], mp[2][N];
int sh[N], ls, a[N], tr[N], lt;
ll dp[N][2];
inline void dfs(int x, bool y) {
    while(x||y){
        if(pre[x][y]){
            if(mp[y][x])sh[++ls]=((a[x]-dp[x][y]+1)<<1)+y;
            x--;
        }
        else tr[++lt]=a[x],pre[x][y]=1,y^=1;
    }
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int p[30], cnt;
inline void print(ll x, char c='\n') {
    if (x < 0) putchar('-'), x = -x;
    p[cnt=1] = x%10;
    while (x > 9) x/=10, p[++cnt] = x%10;
    while (cnt) putchar(p[cnt--]^48);
    if (c > 0) putchar(c);
}



int b[N], n1, c[N], n2, m;
int main() {
    int n = rd(), m1 = rd(), m2 = rd(), t = rd();
    for(int i=1;i<=m1;i++) b[++n1]=rd(),b[n1+1]=b[n1]+1,n1++;
    for(int i=1;i<=m2;i++) c[++n2]=rd(),c[n2+1]=c[n2]+1,n2++;
    int uu=1,vv=1;
    for(int&i=uu,&j=vv;i<=n1&&j<=n2;){
        if(b[i]<=c[j]){
            if(a[m]^b[i])a[++m]=b[i];
            if(i&1)mp[0][m]=1;
            i++;
        }else{
            if(a[m]^c[j])a[++m]=c[j];
            if(j&1)mp[1][m]=1;
            j++;
        }
    }
    for(int&i=uu;i<=n1;i++){
        if(a[m]^b[i])a[++m]=b[i];
        if(i&1)mp[0][m]=1;
    }
    for(int&j=vv;j<=n2;j++){
        if(a[m]^c[j])a[++m]=c[j];
        if(j&1)mp[1][m]=1;
    }
    if(a[m]<=n)a[++m]=n+1;

    dp[0][0]=dp[0][1]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<2;j++)if(dp[i-1][j]>0){
            dp[i][j]=dp[i-1][j]+a[i]-a[i-1]-mp[j][i]*t,pre[i][j]=1;
            if(mp[j][i]&&dp[i][j]==1)dp[i][j]=0;
        }
        for(int j=0;j<2;j++)if(dp[i][j^1]>0&&!mp[j][i]&&min(dp[i][j^1],1ll+t)>dp[i][j])
            dp[i][j]=min(dp[i][j^1],1ll+t),pre[i][j]=0,j=2;
    }
    if(dp[m][0]>0||dp[m][1]>0){
        printf("Yes\n");
        if(dp[m][0]>dp[m][1])dfs(m,0);
        else dfs(m,1);
        print(lt);
        for(int i=lt;i>0;i--)print(tr[i],' ');
        putchar('\n'),print(ls);
        for(int i=ls;i>0;i--)
            print(sh[i]>>1,' '),print((sh[i]&1)+1);
    }
    else printf("No\n");
    return 0;
}