//
// Created by Psy.C on 2026/10/20.
//
/**
从根 1 出发，计算每个节点的子树大小 sz 和深度 d
对每个节点 u 选重儿子 h[u]（满足 2*sz[重] > sz[u]，即"子树超过一半"）。
t[u] 记录该重链的链头：重儿子继承父亲链头 t[u]，轻儿子自成链头 t[v]=v。
调用入口在外层是 dfs2(t[1]=1)（根所在链头为 1）
先访问重儿子再轻儿子，保证同一条重链上的节点 dfn 连续 → 使得"一条链"对应 dfn 上的连续区间，可用线段树区间操作
sum：区间和（当前累加的平铺量）。
sq：区间平方和。
add：区间懒惰加法标记
区间整体加 k：
区间加了 k 后，sum_new = sum_old + len*k；
sq_new = Σ(x_i+k)² = Σx_i² + 2kΣx_i + len·k² = sq_old + 2k·sum_old + len·k²。
这正是代码里 sq += 2*k*sum + (r-l+1)*k*k; sum += (r-l+1)*k。
部分覆盖时下放子树，再从两个孩子的 sum/sq 上推，并把本节点的 add 贡献也计入（2*add*sum + len*add²）。
全程动态开点（if (x==NULL) x=new node()），只有实际被修改的区间才建节点。
可确证：这是支持 区间加、维护区间和与区间平方和 的动态开点线段树，用惰性标记 add。它没有做真正的持久化复制（无版本分裂），rt[] 多棵树共享节点池
对颜色 k 的线段树，把节点 x 到根的整条路径（拆成若干重链段）统一加 v。
每段区间为 [dfn[chain头], dfn[x]]（重链 dfn 连续），然后 x = f[t[x]] 跳到上一条链继续。
这是标准的树链剖分路径更新写法：chain(a[i], i, 1) 就是把"到根路径"上所有点（按颜色分组）各自 +1
输入：n（节点数）、m（颜色种类数）、q（操作数）、c（某个全局常数）。
a[i]：节点 i 的颜色。
f[i]（i≥2）：节点 i 的父节点（故建树 g[f[i]].push_back(i)）。
b[i]：第 i 种颜色带的一个权值。
预处理：dfs/dfs2/dfs3 完成剖分标号；然后对每个节点 i，chain(a[i], i, 1) 把"节点 i 到根路径"在颜色 a[i] 线段树上加 1。
操作：
op 为奇数（op&1）：改色。先 chain(旧色, x, -1) 撤销旧路径贡献，再 chain(新色=a[x]=y, x, 1) 加新路径。

op 为偶数：查询第 x 种颜色。若该色线段树为空（rt[x]==NULL）输出 c*c；否则输出
( b[x]²·sq - 2·b[x]·c·sum + n·c² ) / n
其中 sum、sq 是该色线段树根节点的区间和与平方和（值域 [1,n]）

记该颜色有 k 个节点，每个节点在"到根路径累加"中贡献了某个量 x_i（由 chain(...) 累加得到，实际是每个该色节点到根路径被加过多少次，与祖先中同色/该色路径计数相关）。则：

sum = Σ x_i
sq = Σ x_i²
输出 = (b²·Σx_i² - 2bc·Σx_i + n·c²)/n
这形如去掉平方展开：b²·Σx² - 2bc·Σx + n·c² = Σ (b·x_i - c)²，再除以 n，得到

Σ (b·x_i - c)² / n
即 一组量 (b·x_i) 相对常数 c 的均方偏差（方差相关）‍。

语义推断（强相关，待题面确证）：输出是"整棵树上第 x 种颜色的所有节点贡献量 x_i，经加权 b[x]·x_i 后相对常数 c 的均方差 Σ(b·x_i - c)²/n"；颜色为空时 Σ=0 → (0 - c)²·n/n = c²，正好对应代码 c*c
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 5e4+5;

struct node {
    int sum, sq, add;
    node *lc, *rc;
    node() { sum = sq = add = 0; lc = rc = NULL; }
} *rt[N];

int sz[N], d[N];
vector<int> g[N];
void dfs(int u) {
    sz[u] = 1;
    for (int v : g[u]) {
        d[v] = d[u] + 1;
        dfs(v);
        sz[u] += sz[v];
    }
}

int t[N], h[N];
void dfs2(int u) {
    for (int v : g[u]) {
        if (sz[v]<<1ll > sz[u]) t[h[u]=v] = t[u]; else t[v] = v;
        dfs2(v);
    }
}

int dfn[N], cnt;
void dfs3(int u) {
    dfn[u] = ++cnt;
    if (h[u]) dfs3(h[u]);
    for (int v : g[u]) if (v^h[u]) dfs3(v);
}

#define ls x->lc
#define rs x->rc
void modify(node* &x, int l, int r, int L, int R, int k) {
    if (x == NULL) x = new node();
    if (L <= l && r <= R) {
        x->add += k; x->sq += 2*k*x->sum+(r-l+1)*k*k; x->sum += (r-l+1)*k;
    } else {
        int mid = (l+r)>>1ll;
        if (L <= mid) modify(ls, l, mid, L, R, k);
        if (R > mid) modify(rs, mid+1, r, L, R, k);
        x->sum = x->sq = 0;
        if (ls != nullptr) { x->sum += ls->sum; x->sq += ls->sq; }
        if (rs != nullptr) { x->sum += rs->sum; x->sq += rs->sq; }
        x->sq += 2*x->add*x->sum+(r-l+1)*x->add*x->add;
        x->sum += (r-l+1)*x->add;
    }
}

int n, f[N];
void chain(int k, int x, int v) {
    while (x) {
        modify(rt[k], 1, n, dfn[t[x]], dfn[x], v);
        x = f[t[x]];
    }
}

int m, q, c, a[N], b[N];
signed main() {
    fast;
    cin >> n >> m >> q >> c;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 2; i <= n; ++i) {
        cin >> f[i]; g[f[i]].emplace_back(i);
    }
    for (int i = 1; i <= m; ++i) { rt[i] = nullptr; cin >> b[i]; }
    dfs(1); dfs2(t[1]=1); dfs3(1);
    for (int i = 1; i <= n; ++i) chain(a[i], i, 1);
    for (int op, x, y; q--; ) {
        cin >> op >> x;
        if (op&1ll) {
            cin >> y;
            chain(a[x], x, -1);
            chain(a[x]=y, x, 1);
        } else {
            if (rt[x] == nullptr) cout << c*c << '\n';
            else cout << fixed << setprecision(12) << (1.0*b[x]*b[x]*rt[x]->sq-
                1.0*2*b[x]*c*rt[x]->sum+n*c*c)/n << '\n';
        }
    }
    return 0;
}