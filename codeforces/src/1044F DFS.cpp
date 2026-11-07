//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
建无向树的邻接表
dfn[now]：DFS 序（进入时间），用于把子树映射成连续区间。
sz[now]：子树大小 → 子树区间 = [dfn[now], dfn[now]+sz[now]-1]。
fa[now][0]=f：父节点。之后 fa[i][j]=fa[fa[i][j-1]][j-1] 构建倍增祖先表，用于快速判定祖先关系和求"某点是某子树下哪一层"
倍增往上跳，直到 u 跳到 v 下面最近的那个直接子节点（即"v 下的孩子节点"）。
用途：当一条边的两个端点是祖先后代关系时，用来确定"断开后归属于外侧的那棵子树"的区间。
判断条件 dfn[fa[u][i]] > dfn[v]：fa[u][i] 仍在 v 的子树内（dfn 落在 v 之后）就继续上跳
dat：惰性标记（区间加）。
mn：区间最小值（代表该区间内"不满足条件被加上次数最少的层"）。
sum：最小值对应的叶子个数
mn = 两儿子 mn 的较小值。
sum = "mn 等于该最小值"的分支的 sum 之和 → 总量 = 取到最小值的叶子个数
区间加的惰性下传
叶子初始化 sum=1（每个叶子作为一个计数单位），mn=0
标准区间加（支持 L>R 空区间直接跳过）
一棵树，每条边可以动态"开/关"。每次切换一条边，问有多少个节点满足「当前被提供的边覆盖次数」为全局最小（即输出 tr[1].mn==0 ? 0 : tr[1].sum）。

每次操作对一条边 (s,e) 切换状态（vis 取反，f=±1）。
对以 e 为子树根的整棵子树内所有节点做区间加/减（f=±1），表示"这条边对内/外交界处次数变化"。
特殊处理祖先后代关系。
两种情况（dfn[s]<dfn[e]，s 为祖先）

情况 A：dfn[s]+sz[s] > dfn[e]（e 在 s 的子树内，祖先后代）‍
此时 e 是 s 的后代（在 s 的子树里），中间隔着一个孩子 t。
对「e 子树内部」之外的 s 子树部分做区间加减（取补集，跳过 e 子树本身）——具体是把 s 子树拆成两段去除 e 的子树区间。
情况 B：否则（e 在 s 的子树之外，非祖先后代）‍
把整个树分成三段，除去 s、e 两棵子树各自内部区间后，对"外侧区间"做区间加。
相当于：把这条边对的"覆盖区间"设为除两棵子树外的所有点，然后区间动态修改。
若全局最小 mn != 0 → 说明所有节点都被覆盖过 → 输出 0。
否则 mn==0 → 输出覆盖次数为 0 的节点个数（tr[1].sum）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); ++i)
#define ii pair<int,int>
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define mid ((l+r)>>1)
using namespace std;

constexpr int N = 2e5+5, M = 4e5+5;

int tot, nxt[M], ver[M], head[N];
void add(int s, int e) {
    ver[++tot] = e; nxt[tot] = head[s]; head[s] = tot;
}

int dfn[N], sz[N], fa[N][19], tim;
void dfs(int now, int f) {
    dfn[now] = ++tim; sz[now] = 1; fa[now][0] = f;
    for (int i = head[now]; i; i = nxt[i]) {
        if (ver[i] == f) continue;
        dfs(ver[i], now);
        sz[now] += sz[ver[i]];
    }
}
int find(int u, int v) {
    for (int i = 18; i >= 0; --i)
        if (dfn[fa[u][i]] > dfn[v]) u = fa[u][i];
    return u;
}

struct sgt { int dat, sum, mn; } tr[N*5];

void update(int p) {
    int x = ls(p), y = rs(p), mn = tr[p].mn = min(tr[x].mn, tr[y].mn);
    tr[p].sum = (tr[x].mn == mn)*tr[x].sum + (tr[y].mn == mn)*tr[y].sum;
}

void spread(int p) {
    if (!tr[p].dat) return;
    int x = ls(p), y = rs(p);
    tr[x].dat += tr[p].dat, tr[x].mn += tr[p].dat;
    tr[y].dat += tr[p].dat, tr[y].mn += tr[p].dat;
    tr[p].dat = 0;
}

void build(int p, int l, int r) {
    if (l == r) return void(tr[p].sum = 1);
    build(ls(p), l, mid), build(rs(p), mid+1, r);
    update(p);
}

void change(int p, int l, int r, int L, int R, int d) {
    if (L > R) return;
    if (l >= L && r <= R) { tr[p].dat += d, tr[p].mn += d; return; }
    spread(p);
    if (L <= mid) change(ls(p), l, mid, L, R, d);
    if (R > mid) change(rs(p), mid+1, r, L, R, d);
    update(p);
}

int n, q, s, e, f, t;
map<ii,bool> vis;
int main() {
    fast;
    cin >> n >> q;
    rep(i,n-1) { cin >> s >> e; add(s, e), add(e, s); }
    dfs(1,0);
    rep(j,18) rep(i,n) fa[i][j] = fa[fa[i][j-1]][j-1];
    build(1,1,n);
    while (q--) {
        cin >> s >> e;
        if (dfn[s] > dfn[e]) swap(s, e);
        vis[{s,e}] ^= 1; f = vis[{s,e}] ? 1 : -1;
        if (dfn[s] + sz[s] > dfn[e]) {
            t = find(e, s);//e 在 s 下的直接孩子
            change(1,1,n,dfn[t], dfn[e]-1, f);//区间 [t子树起点, e子树起点)
            change(1,1,n,dfn[e]+sz[e], dfn[t]+sz[t]-1, f);//区间 [e子树终点, t子树终点)
        } else {
            change(1,1,n,1,dfn[s]-1,f);//[1, s子树起点)
            change(1,1,n,dfn[s]+sz[s],dfn[e]-1,f);//[s子树终点, e子树起点)
            change(1,1,n,dfn[e]+sz[e],n,f);//[e子树终点, n]
        }
        cout << (tr[1].mn ? 0 : tr[1].sum) << '\n';
    }
    return 0;
}