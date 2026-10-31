//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
node：描述虚拟树上的一条边：
to：子节点编号；
w：块内操作产生的「翻转次数贡献」（继承过来的）;
dis：从当前增查点向下到该点的深度（距离）
vis[N]：标记当前块内被操作涉及的节点（「特殊点」）；
b[N]：节点当前是否为黑色；
tr[N]：虚拟树（只保留被操作节点及其朴素祖先的链），用于块内快速传播；
e[N]：原始树的邻接表（父节点存孩子）
now：当前遍历到的节点；pre：上一个特殊点；w：累计的黑色计数；dis：当前深度距上一个特殊点的距离。
逻辑：

若 now 是特殊点（vis[now]）：

如果它不是第一个特殊点（pre!=0），则在 tr[pre] 里加入一条到 now 的边：w 存「从 pre 到 now 路径上的黑色节点数」，dis 存「路径长度」。
然后从 now 的孩子继续 build，此时 pre 变为 now，重置 w=0, dis=0。
若 now 不是特殊点：

若它当前是白色且不是特殊染色节点（!b[now]），则 w++（这一段的黑色计数加一，之后会通过虚拟边传递）;
等等——仔细看：if (!b[now]) w++; 是加在 w 注记上的。其实它数的是「沿路径从 pre 到 now 之间那些不黑的节点数」……不过由于 dis 也在累加，二者关系需结合 dfs 使用。

继续向下 build，dis+1 累计距离。
作用：把「本次块内涉及的所有特殊点」及其朴素结构压缩成一棵小的虚拟树，每条边的 w/dis 记录了块内路径上的信息，避免每次都扫全树。
处理操作 1（翻转）‍：把 now 变黑。

如果 now 当前是白色（!b[now]），直接置黑返回。
如果 now 已经是黑色，则now要变白……但这里代码实际上是沿着虚拟树继续翻转：
p[now]++ 记录 now 被翻转的次数（或者说被推下来的需求累积）；
遍历 now 的虚拟树边，若 p[now] > tr[now][i].w（下推的次数大于路径上的……），则清零该边 w 并递归 dfs 到子节点，继续下推翻转标记。
这本质上是把「翻转」动作沿着压缩后的虚拟树向下传播，用 p 数组做延迟计数，避免直接操作大片子树
处理操作 2（变白）‍：把 now 整棵子树清为白色。

b[now]=false 置白，p[now]=0 清空翻转计数，cl[now]=true 标记「这棵子树被整体清白过」；
沿着虚拟树递归，把每个边的 w 重置为 dis（清空沿途影响），再递归子树。
cl[] 数组记录该子树是否被整体「覆盖成白」，供后续 dfs3 延迟处理真实整棵子树
在每一块的末尾调用，把块内虚拟树上的延迟操作真正落到真实树上：

cr：是否处于「被整体清白」的子树中（继承）；
ps：待下发的剩余翻转次数（继承）。
逻辑：

若 now 是特殊点：用 cl[now]、p[now] 刷新 cr/ps（特殊点的真实状态，块内已记录）；
若不是特殊点：按继承下来的 cr/ps 应用状态：
若 cr 真，则置白 b[now]=false；
若当前为白且 ps>0，则置黑 b[now]=true 并消耗一次 ps--。
沿真实树 e[now] 递归下传。
这一步把块内做的「局部模拟」，合并成对整个树的真实染色，保证跨块查询结果正确

n, q；
对 i=2..n，读入父节点 x，e[x].push_back(i)（约定 1 为根，形成父子结构的树）;
读入 q 组 (t[i], v[i])。
分块：块大小 bl = √n。

对每一块 [i, i+bl)：

清空标记：vis, cl, p 清零；
标记特殊点：本块内所有操作涉及的节点 v，清空其 tr 数组并设置 vis[v]=true；
建虚拟树：build(1,0,0,0) 从根开始，把特殊点压缩成虚拟树；
执行块内所有操作：逐个执行 dfs（翻转）/ dfs2（清白）/ 查询输出；
下发真实状态：dfs3(1,0,0) 把块内的延迟结果真正落在整棵树上，供下一块使用
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
using namespace std;

constexpr int N = 1e5+5;

struct node { int to, w, dis; };

bool vis[N], b[N];
vector<node> tr[N];
vector<int> e[N];
void build(int now, int pre, int w, int dis) {
    if (vis[now]) {
        if (pre != 0) {
            node t{}; t.to = now; t.w = w; t.dis = dis;
            tr[pre].push_back(t);
        }
        rep(i,e[now].size()) build(e[now][i], now, 0, 0);
    } else {
        if (!b[now]) w++;
        for(int i : e[now]) build(i, pre, w, dis+1);
    }
}

int p[N];
void dfs(int now) {
    if (!b[now]) { b[now] = true; return; }
    p[now]++;
    rep(i,tr[now].size()) if (p[now] > tr[now][i].w) {
        tr[now][i].w = 0;
        dfs(tr[now][i].to);
    }
}

bool cl[N];
void dfs2(int now) {
    b[now] = false; p[now] = 0; cl[now] = true;
    for (auto &[to, w, dis] : tr[now]) {
        w = dis; dfs2(to);
    }
}

void dfs3(int now, bool cr, int ps) {
    if (vis[now]) { cr = cl[now]; ps = p[now]; }
    else {
        if (cr) b[now] = false;
        if (!b[now] && ps > 0) { b[now] = true; ps--; }
    }
    for (int i : e[now]) dfs3(i, cr, ps);
}

int t[N], v[N];
int main() {
    fast;
    int n, q; cin >> n >> q;
    for (int i = 2, x; i <= n; i++) {
        cin >> x; e[x].push_back(i);
    }
    for (int i = 1; i <= q; i++) cin >> t[i] >> v[i];
    int bl = sqrt(n);
    for (int i = 1; i <= q; i += bl) {
        memset(vis, 0, sizeof(vis));
        memset(cl, 0, sizeof(cl));
        memset(p, 0, sizeof(p));
        for (int j = 0; j < bl && i+j <= q; j++) {
            tr[v[i+j]].clear();
            vis[v[i+j]] = true;
        }
        build(1, 0, 0, 0);
        for (int j = 0; j < bl && i+j <= q; j++) {
            switch (t[i+j]) {
                case 1: dfs(v[i+j]); break;
                case 2: dfs2(v[i+j]); break;
                case 3: if (b[v[i+j]]) cout << "black\n"; else cout << "white\n";
            }
        }
        dfs3(1, 0, 0);
    }
    return 0;
}