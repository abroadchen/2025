//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
邻接表结构体。head[u] 表头，y 存终点，nxt 存下一条边下标。
clear()：cnt 置 1（边下标从 2 开始，这样 i^1 可配对反向边），head 清 0。
add(a,b)：链式前向星加一条有向边 a→b。因为 add 成对调用，边 i 与 i^1 互为反向边。
g：原图；
用 use[i/2] 标记"无向边"用过一次，保证 DFS 不重复走同一条无向边——这是边双连通分量（e-DCC）‍的求法（而非强连通分量）。
生成的 id[x] 是每个点所属的边双编号；tot 是边双总数。
注意 low[g.y[i]] 用于后向边（通常写 low[v]=min(low[v],dfn[v]) 更正确，但此实现用 low，可能是针对仙人掌的特定处理，有假定）。
小提示：这里后向边更新用的是 low[g.y[i]] 而不是 dfn，在通用 Tarjan 里应谨慎，但配合 use 只走一次的语义，属于实现细节，我如实标注
cir[ID]：编号 ID 的边双包含的所有点（一个"环"）。
son[u]：后面 build 时记录 u 的孩子。
可确证：dfs 收集同一边双（环）中的所有点到 cir[id[x]]
build(x, pre)：以边双 ID 为节点，从 x 出发遍历该环，把所有跨边双的边作为树边连出去（son[u]），递归 build 子树。
fa[ID]=pre：记录边双的父节点（边双构成的仙人掌/普通树的父边双）。
语义：把原图缩成"边双为节点"的树（如果是仙人掌则每个边双是环或单点，缩后成树）；son[u] 存 u（环上的具体点）连向子边双的入口点。
可确证：build 把每个边双缩成树节点，递归建立"边双树"，son[u] 记录环上点 u 的子树入口
先递归子树，dep[u] = 从 u 出发、经过其子树，能到达的最远边数。
对环 cir[ID]：把环看作一个圈，lm[i]/rm[i] 做前缀/后缀的最大值（结合点在环上的位置 i），模拟"在环上某处切开"后，环上各点到达最远点的距离；sp[x]=v 是最优切点下环长相关距离。
dep[x] = max(dep[x], sp[x])：x 的最终 dep 取二者较大。us[x]=dep[x] 临时保存。
提示：这里含义是"环上距 x 最远的点距离"，通过切割环计算最优值，是仙人掌 DP 常见技巧
两个单调递减队列 ql、qr。push 维护单调性，pop(_d) 按下标淘汰过期元素，front 取当前最大值，nxt_front 取"剔除指定下标 _d 后的最大值"
far[x]：边双 ID 之外的（经由父树方向）到达 x 的最远距离。
将环 cir[ID] 复制三段（n*3）解决"环是循环"的问题。
lv[i]=val[i]+(n*3-i)、rv[i]=val[i]+i+1：把"距离+环上位置"合并，方便用单调队列在两段之间找最优点。
旋转扫描（for i=n+1..2n-1）：用双单调队列 ql/qr 在环的"展开窗口"内，找到使两端最大值最小化的切点（类似求两点间环上距离最小化），从而计算 far[cir[ID][i%n]]。
再对环上每个点的子树递归调用 solve，mx[u][j] = 去掉第 j 棵子树后其余子树深度的最大值；传入子边双的 far = max(sp[u], max(far[u], mx[u][j]))+1。
这一部分是经典"仙人掌偏心距"DP：环上用单调队列 O(n) 旋转求每个位置的最远环外距离，子树用前后缀挖掉单棵后取 max 再递归
读入 n 点 m 边的无向图。
tarjan 求所有边双连通分量（id[]）。
build(1,0) 建树，dfs2(1) 计算各环内部最优距离，solve(1,0) 旋转扫环 + 递归子树。
对每个点输出 max(far[i], dep[i]) = 该点在整张图上的偏心距（到最远节点的最短距离，即图的点 eccentricity）‍。
可确证：输出每个点 max(far[i],dep[i])，即该节点的偏心距（Eccentricity，图直径相关概念）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; i++)
using namespace std;

constexpr int N = 5e5+5, M = N<<2, inf = 1e9;
struct grh {
    int cnt, y[M], nxt[M], head[N];
    void clear() { cnt = 1; memset(head, 0, sizeof(head)); }
    void add(int a, int b) { y[++cnt]=b, nxt[cnt]=head[a], head[a]=cnt; }
} g;

int dfn[N], low[N], tim, vis[N], in[N], st[N], top, use[M], tot, id[N];
void tarjan(int x) {
    dfn[x]=low[x]=++tim; vis[x] = in[x] = 1; st[++top] = x;
    for (int i = g.head[x]; i; i = g.nxt[i]) {//遍历 x 的所有出边
        if (use[i/2]) continue;//该无向边（边对 i/2）已被用过，跳过（避免来回走同一条无向边）
        use[i/2] = 1;//标记该无向边已使用
        if (!vis[g.y[i]]) {//邻接点未访问
            tarjan(g.y[i]);
            low[x] = min(low[x], low[g.y[i]]);
        }
        //邻接点在栈中（后向边）
        else if (in[g.y[i]]) low[x] = min(low[x], low[g.y[i]]);
    }
    //缩点
    if (dfn[x] == low[x]) {//x 是某个边双的根
        //新边双编号
        tot++; id[st[top]] = tot; in[st[top]] = 0;//栈顶归入该边双
        while (st[top--] != x) { id[st[top]] = tot; in[st[top]] = 0; }//弹出直到 x
    }
}

vector<int> cir[N], son[N];
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = 1;
    cir[id[x]].push_back(x);//把 x 放进它所属边双 cir[ID]
    for (int i = g.head[x]; i; i = g.nxt[i]) {
        int y = g.y[i];
        if (id[y] == id[x]) dfs(y);//同一边双的点沿着边继续收集
    }
}

int fa[N];
void build(int x, int pre) {
    //记录该边双 ID 的"父边双"编号
    int ID = id[x]; fa[ID] = pre; cir[ID].clear(); dfs(x);//收集该边双所有点
    rep(i,cir[ID].size()) {//对环上每个点 u
        int u = cir[ID][i]; son[u].clear();
        for (int j = g.head[u]; j; j = g.nxt[j]) {
            int v = g.y[j];
            if (id[v] == ID || id[v] == pre) continue;//跳过环内边和连回父边双的边
            son[u].push_back(v);//v 属于另一个边双，作为 u 的孩子
            build(v, ID);//递归建孩子边双，pre=当前 ID
        }
    }
}

int dep[N], sp[N], us[N], lm[N], rm[N];
void dfs2(int x) {
    int ID = id[x];
    for (int i : cir[ID]) {//遍历该环所有点
        int u = i, v;  dep[u] = 0;
        rep(j,son[u].size()) {//对 u 的每个子节点
            v = son[u][j]; dfs2(v);//递归：先算子树
            dep[u] = max(dep[u], dep[v]+1);//dep[u]=子树方向能到的最远距离
        }
    }
    //环长 n（-1？通常环长，这里减1说明用0基/1基混合）
    int n = cir[ID].size()-1; lm[0] = rm[n+1] = 0;
    for (int i = 1; i <= n; i++) lm[i] = max(lm[i-1], dep[cir[ID][i]]+i);//前缀最大：dep+沿环位置
    for (int i = n; i >= 1; i--) rm[i] = max(rm[i+1], dep[cir[ID][i]]+(n-i+1));//后缀最大
    int v = inf;
    for (int i = 1; i <= n+1; i++) v = min(v, max(lm[i-1], rm[i]));//在环上切一刀，使两侧最大距离最小
    dep[x] = max(us[x]=dep[x], sp[x]=v);//dep[x] 取"子树内最远"与"环上切点最优"的较大者
}

struct mnq {
    int h, t, q[N*3], d[N*3];
    void clear() { h = 1, t = 0; }
    int front() const { return h <= t ? q[h] : -inf; }//队首值
    void push(int v, int _d) {//插入，v=值,_d=下标
        while (h <= t && q[t] <= v) t--;//单调递减
        q[++t] = v, d[t] = _d;
    }
    void pop(int _d) { while (h <= t && d[h] < _d) h++; }//弹出下标< _d 的过期元素
    int nxt_front(int _d) const {//返回"不是 _d 下标"的队首
        if (h > t) return -inf;
        if (d[h] != _d) return q[h];//队首下标不是 _d，直接返回
        return h == t ? -inf : q[h+1];//否则看第二元素
    }
} ql, qr;

int far[N], val[N*3], lv[N*3], rv[N*3];
vector<int> mx[N];
void solve(int x, int f) {
    int ID = id[x]; far[x] = f;//f: 从父边双传入的"环外最远距离"
    int n = cir[ID].size();//环长
    for (int i = 1; i < n; i++) val[i] = dep[cir[ID][i]];//环上点 1..n-1 的 dep
    val[0] = max(us[x], far[x]);//0 号点取"原 dep"与"环外传入"较大
    for (int i = n; i < n*3; i++) val[i] = val[i%n];//把环复制 2 圈，处理循环
    for (int i = 0; i < n*3; i++) { lv[i] = val[i]+n*3-i; rv[i] = val[i]+i+1; }//封装：加位置偏移
    ql.clear(), qr.clear();
    int lp = 2, rp = n+1;
    for (int i = lp; i <= n; i++) ql.push(lv[i], i);//右移前初始化 ql
    for (int i = n+1; i < n*2; i++) {//对环展开的一半作旋转扫描
        int res = inf, v1 = n*3-i, v2 = i+1;
        while (rp < i) {//扩展窗口
            lp++, ql.pop(lp); rp++;
            if (rp != i) qr.push(rv[rp], rp);
        }
        while (ql.nxt_front(lp)-v1 > max(qr.front(), rv[rp+1])-v2) {//平衡两侧最大值
            res = min(res, ql.front()-v1);
            lp++, ql.pop(lp); rp++;
            qr.push(rv[rp], rp);
        }
        res = min(res, ql.front()-v1);
        res = min(res, max(qr.front(), rv[rp+1])-v2);
        ql.push(lv[i], i); qr.pop(i+2);
        far[cir[ID][i%n]] = res;//环上对应点得到的"环外最远距离"
    }
    for (int i = 0; i < n; i++) {//对该环每个点 u，处理其子树
        int u = cir[ID][i], m = son[u].size();
        lm[0] = rm[m+1] = 0;
        for (int j = 1; j <= m; j++) lm[j] = max(lm[j-1], dep[son[u][j-1]]+1);//前缀 max
        for (int j = m; j >= 1; j--) rm[j] = max(rm[j+1], dep[son[u][j-1]]+1);//后缀 max
        mx[u].clear();
        for (int j = 0; j < m; j++) mx[u].push_back(max(lm[j], rm[j+2]));//挖掉第 j 个子树后其余子树的 max
        for (int j = 0; j < m; j++) solve(son[u][j], max(sp[u], max(far[u], mx[u][j]))+1);//递归子边双
    }
}

int n, m;
int main() {
    fast;
    cin >> n >> m; g.clear();
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b; g.add(a, b); g.add(b, a);
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) tarjan(i);//求所有边双
    memset(vis, 0, sizeof vis);
    build(1, 0); dfs2(1); solve(1, 0);//建仙人掌树 + 三遍DP
    for (int i = 1; i <= n; i++) cout << max(far[i], dep[i]) << ' ';//输出每个点偏心距
    return 0;
}