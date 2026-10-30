//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
边结构体：to 到达点、nxt 下一条边、w 边权。N<<1 是因为树有
2
(
n
−
1
)
2(n−1) 条有向边，数组开两倍
cnt 边编号计数器，head[rt] 存以 rt 为起点的第一条边的编号。
加一条从 u 到 v 的有向边：把新边插到链表头部（nxt 指向原来的头，再把 head[u] 更新为当前边号）。这是标准的链式前向星 add
记录每个点的父亲 f
遍历 rt 的所有邻边，跳过父亲 f，递归访问子节点。这样得到一棵有根树（根为 1），fa[i] 是每个节点在有根意义下的父节点
从节点 n 出发，沿父指针不断上跳（n → fa[n] → fa[fa[n]] → ... → 1），把这条路径上的所有点标记 vis=true。这条从 1 到 n 的路径就是"主链/脊柱"，接下来的划分都围绕它进行
sz[i]：以 i 为根的子树大小（仅统计主链外的部分，见下面逻辑）。
vec：收集所有主链上的点（按 DFS 顺序）。
p[i]：从主链起点 1 沿主链走到点 i 的距离前缀和（只对主链点累加边权）。
d[i]：从点 i 出发，沿主链外的子树能伸出去的最长深度。
初始化当前点为 1（自己算一个节点）
如果 rt 是主链点，就把它按 DFS 序加入 vec。这样 vec[1..k] 就是主链上点的顺序序列。
遍历子节点 t：

跳过父亲；
若 t 是主链点，则计算 p[t]：主链前缀距离 = 父链点的距离 + 边权；
递归进入 t 的子树
处理完子树 t 后做回传：

若 t 是非主链点，则把 t 的子树并入 rt（sz[rt] += sz[t]），并用 d[t]+边权 更新 d[rt]——即 rt 沿这条非主链支路能伸出的最大深度。
关键语义：sz[i] = i 挂着的非主链子树的节点总数；d[i] = i 沿非主链子树能到达的最深距离。这两个值服务于后面判断"某个主链点的分支有没有"肥"的子树（大小≥3）"。
注意：对主链点，其孩子通常是下一个主链点（继续走主链）；对挂在主链上的支叶子，!vis[t] 分支成立，会把叶子子树并入主链点的 sz
fl（flag）：若存在某点挂着的大小 ≥3 的非主链子树，则标记 fl=1。这个 flag 决定最终答案是否固定等于主链长度 p[n]（见 main 末尾）
pr 与 sf 分别存前缀/后缀最值，初始化为 "负无穷"。vec.size() 就是主链点数 k
计算前缀最值：tmp = p[vec[i]] + d[vec[i]]。

语义：把主链起点 1 的距离前缀 p[vec[i]] 加上该主链点挂的非主链子树最深深度 d[vec[i]]。用 tmp 去和 pr[i-1] 比大小，取较大者作为 pr[i]（即前 i 个主链点中，p+d 的最大值）。同时用 prp[i] 记录取到最大值的位置 i
计算后缀最值：tmp = -p[vec[i]] + d[vec[i]]（注意是负前缀距离 + 深度）。同样记录 sup[i] 为取得最大值的下标。这里的 -p 是为了在后面 pr+sf 相加时抵消掉 p，得到"两个不同主链点的深度之和"这类量
初始化答案为负无穷，后面逐步取 max
遍历分界点 i，把 pr[i-1] + sf[i] 相加——这代表在主链左侧某点的 (p+d) 与主链右侧某点的 (-p+d) 组合，两者相加后 p 相消，得到一个"某种最长链长度"的候选。

跳过条件：当左侧最优取自 i-1 且右侧最优取自 i，且 vec[i-1]、vec[i] 挂的子树大小都恰好为 1（两个相邻主链点都只挂单个节点）时，这种组合退化无意义，跳过。最后统一加上 p[n]（主链总长）得到实际答案基数
对主链上相隔两跳（i 和 i+2）的两个点，计算 p[i] + (主链总长 - p[i+2])：即以主链为线，绕回形成一个环上的路径候选，取最大值
遍历每个挂着大小≥2 非主链子树的主链点（sz>=2 才处理，叶子点跳过）：

若 i 不是第一个主链点：候选 = 从前一个主链点绕到 i，再伸进 i 的大子树，再经主链绕到 n。
若 i 不是最后一个主链点：候选 = 到 i 后伸入大树再绕回末尾 n。
这些分支都在尝试构造"绕过主链、经过某棵大树"的更长的链
每次查询读入一个 x，输出一个答案：

若 fl==1（存在大小≥3 的分支）：直接输出 p[n]（主链长度，固定值）。
否则输出 min( ans+x, p[n] )，即取 ans+x 与主链长度 p[n] 的较小者。其中 ans+x<=0 时输出 p[n]（防止负值）
*/
#include <bits/stdc++.h>
#define ll long long
using namespace std;

constexpr int N = 3e5+10;
constexpr ll inf = 2e18;

struct edge { int to, nxt, w; } a[N<<1];

int cnt, head[N];
inline void add(int u, int v, int w) {
    a[++cnt].to = v; a[cnt].w = w; a[cnt].nxt = head[u]; head[u] = cnt;
}

int fa[N];
inline void dfs(int rt, int f) {
    fa[rt] = f;
    for (int i = head[rt]; i; i = a[i].nxt) {
        int t = a[i].to;
        if (t == f) continue;
        dfs(t, rt);
    }
}

int sz[N];
bool vis[N];
vector<int> vec;
ll p[N], d[N];
inline void dfs2(int rt) {
    sz[rt] = 1;
    if (vis[rt]) vec.push_back(rt);
    for (int i = head[rt]; i; i = a[i].nxt) {
        int t = a[i].to;
        if (t == fa[rt]) continue;
        if (vis[t]) p[t] = p[rt] + a[i].w;
        dfs2(t);
        if (!vis[t]) {
            sz[rt] += sz[t];
            d[rt] = max(d[rt], d[t] + a[i].w);
        }
    }
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
template<class T>
void write(T x) {
    if (x < 0) { putchar('-'); x = -x; }
    T y = 1;
    int len = 1;
    for (; y <= x/10; y *= 10) ++len;
    for (; len; --len, x %= y, y /= 10) putchar(x/y+48);
}

bool fl;
ll pr[N], sf[N];
int prp[N], sup[N];
int main() {
    int n=read(),q=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }
    dfs(1,0);
    for(int i=n;i;i=fa[i]) vis[i]=1;
    vec.push_back(0);
    dfs2(1);
    for(int i=1;i<=n;i++)
        if(sz[i]>=3) fl=1;
    pr[0]=sf[vec.size()]=-inf;
    for(int i=1;i<vec.size();i++){
        ll tmp=p[vec[i]]+d[vec[i]];
        if(tmp>pr[i-1]) pr[i]=tmp,prp[i]=i;
        else pr[i]=pr[i-1],prp[i]=prp[i-1];
    }
    for(int i=vec.size()-1;i;i--){
        ll tmp=-p[vec[i]]+d[vec[i]];
        if(tmp>sf[i+1]) sf[i]=tmp,sup[i]=i;
        else sf[i]=sf[i+1],sup[i]=sup[i+1];
    }
    ll ans = -inf;
    for(int i=1;i<vec.size();i++){
        if(prp[i-1]==i-1&&sup[i]==i&&sz[vec[i-1]]==1&&sz[vec[i]]==1) continue;
        ans=max(ans,pr[i-1]+sf[i]);
    }
    ans+=p[n];
    for(int i=1;i<vec.size()-2;i++)
        ans=max(ans,p[vec[i]]+p[n]-p[vec[i+2]]);
    for(int i=1;i<vec.size();i++){
        if(sz[vec[i]]==1) continue;
        if(i!=1) ans=max(ans,p[vec[i-1]]+d[vec[i]]+p[n]-p[vec[i]]);
        if(i!=vec.size()-1) ans=max(ans,p[vec[i]]+d[vec[i]]+p[n]-p[vec[i+1]]);
    }
    while(q--){
        int x=read();
        write(fl?p[n]:min(ans+x<=0?p[n]:ans+x,p[n])),putchar('\n');
    }
    return 0;
}