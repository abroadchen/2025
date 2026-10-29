//
// Created by Psy.C on 2026/10/28.
//

/**
真正学会的起点..
fa[x]：x 的父亲。
dep[x]：x 的深度。
sz[x]：x 的子树大小。
son[x]：x 的重儿子（子树最大的儿子）。
e[N]：邻接表。这个数组被重复利用（先存树，后来被清空改存 2-SAT 图的边）。
N=5e6+10 是为了给 2-SAT 图留出空间（2e6 牌变量 ×2×若干边）
从根开始做第一次 DFS：
fa[x]=ff 记录父亲。
dep[x]=dep[ff]+1 深度。
sz[x]=1 先把自己算进去。
遍历所有子节点 y，递归 dfs(y,x)，累加子树大小 sz[x]+=sz[y]。
若 y 的子树大于当前重儿子，son[x]=y 更新重儿子。
这是标准的树链剖分第一遍，得到 fa/dep/sz/son
dfn[x] = ++dfn[0] 给节点分配访问编号（优先访问重儿子，使重链在 dfn 上连续）。
top[x]=ff 记录 x 所在链的链顶。
先递归重儿子（继承同一链顶 ff），再对其他儿子递归（各自新开一条链 dfs2(y,y)）。
完成后，同一条重链上的点在 dfn 区间内是连续的，这是后面"路径转区间"的基础。
到这里 HLD 已经完成。dfn 序把一棵树变成若干个区间，之后的"路径更新"会变成"把一条树链拆成 O(log n) 段 dfn 区间"
pos[id] 是线段树每个节点的"标记板"，存放"覆盖了这个节点代表区间的所有路径编号"。
这是区间更新：若 [L,R] 完全覆盖当前节点区间 [l,r]，就把路径 a 挂到这个节点 pos[id] 上并返回；否则向下递归两个子节点。
作用：为"每条路径覆盖的 dfn 区间"做懒式区间打标，把一条链拆到 O(log n) 个线段树节点上。后续 2-SAT 建图由这些节点串起来。
注意这里 a 是2-SAT 变量编号（后面会看到是 i<<1 或 i<<1|1），作为"该路径覆盖到此区间"的标志
标准 Tarjan 强连通分量算法（用于 2-SAT 判可满足性 + 拓扑定向）。
dfn2/low 是时间戳与最小可达时间戳，st 是栈，c[x] 记录 x 属于哪个 SCC 编号。
若 dfn2[x]==low[x]，x 是某个强连通分量的根，弹出栈内节点归并为一个 SCC。
2-SAT 中：若变量 x 和它的反 x^1 在同一个 SCC，则不可满足
这是 HLD 的路径→区间 过程（把树路径 (x,y) 拆成 O(log n) 个 dfn 连续区间）：
while(top[x]!=top[y])：x、y 不在同一条重链。
把较深链顶所在的那端处理：update(..., dfn[top[x]], dfn[x], t) 把 [dfn[top[x]], dfn[x]] 这段区间挂上标记 t。
x = fa[top[x]]，把 x 跳到链顶的父亲，继续循环。
跳出循环后 x、y 在同一条重链上：
保证 dfn[x]<dfn[y]。
若 dfn[x]<dfn[y]，更新区间 [dfn[x]+1, dfn[y]]。（+1 表示不包含 LCA 本身，因为这条路径通常由两条链拼成，LCA 只在其中一条处理到。）
t 是打在这个区间上的 2-SAT 变量编号，即"该路径覆盖了这段节点区间"。
这一步把"每条路径覆盖哪些 dfn 区间"记录到线段树的 pos[] 上
这是线段树优化建图，构建 2-SAT 的蕴含图。
参数 (id,l,r)：当前线段树节点。返回 z = 该子树代表节点对应的 2-SAT 节点（或 0 表示空）。
递归环节：

若 l!=r，递归处理左右子树得 x,y。
若一个为空 z=x+y（取非空那个）。
若都不为空：新建一对节点 tot（含 tot^1），连边：
x→tot, tot^1→x^1（若左子树成立的区间存在，则 tot 可达；若 tot 成立则左子树必须成立——蕴含关系）。
y→tot, tot^1→y^1（同理右子树）。
z=tot, tot+=2。
这样把"子树区间覆盖"合并成一个节点，形成蕴含（AND）关系的链，用于保证"若某区间被多条路径覆盖，则这些路径存在互斥限制"。
pos 打标环节：

遍历当前节点 pos[id] 里挂的所有路径 i：
若已有 z（此区间非空）：
z→i^1，i→z^1：若这个区间被 z 代表的路径覆盖，则 i 不能同时覆盖（互斥）。
再新建一对节点把 i 并入链中（z→tot, tot^1→z^1; i→tot, tot^1→i^1），z=tot。
若 z==0，直接 z=i（此节点只有一个路径，作为起点）。
语义：同一 dfn 区间被多条路径同时覆盖 → 这些路径两两互斥（不能同时选）‍，转化为 2-SAT 的蕴含约束。
这一步实质是把"同一段树链区间至多选一条路径"的互斥约束，用线段树节点 O(log n) 地编码进 2-SAT 图，避免把每对互斥都显式连边（那样是 O(m²)），从而优化到 O(m log n)。

第 1 段：读树，做树剖

读 n，读 n-1 条边建树。
dfs(1,0) 第一次剖分，dfs2(1,1) 划分链。
第 2 段：清空邻接表，读路径

for(...) e[i].clear();：把存树的邻接表清空，为 2-SAT 图腾地方。（树剖信息已存到 fa/dep/dfn/top 等数组，不再需要 e 存树。）
读 m 组路径。每组是一对树链 (a,b) 和 (c,d)——
update(a, b, i<<1)：把路径 (a,b) 对应的 dfn 区间挂上 2-SAT 变量 i<<1。
update(c, d, i<<1|1)：把路径 (c,d) 挂上变量 i<<1|1（i 的反变量）。
即：第 i 个变量有两个"颜色/朝向"选择：选 (a,b) 则 i<<1 真、选 (c,d) 则反变量真——这就是二选一互斥的 2-SAT 结构。
第 3 段：建图

tot = 2*m+2：变量编号从 2m+2 之后开始新建（线段树优化节点）。
solve(1,1,n)：建 2-SAT 蕴含图。
第 4 段：Tarjan 判 SCC

对每个节点跑 tarjan 求强连通分量，填 c[i]。
第 5 段：判可满足性 + 输出

for i=1..m: if (c[i<<1]==c[i<<1|1])：若变量和它的反变量在同一 SCC，说明既必须真又必须假 → 矛盾，输出 NO，结束。
否则 YES，然后对每个 i 输出选哪个：
1 + (c[i<<1] > c[i<<1|1])：若 i<<1 所在 SCC 编号大于反变量 SCC，输出 2，否则输出 1。这是 2-SAT 的经典拓扑定向取值法（同一 SCC 内编号大的那个是真赋值，保证满足性）。





在 Tarjan 中，dfn2[x] 是节点 x 的访问时间戳，low[x] 是 x 能通过边（及栈内点）到达的最小 dfn。
当 dfn2[x] == low[x]，说明 x 能到达的最小时间戳就是它自己，即 x 是这个强连通分量的根（这个分量里没有其他点能提前到达它）。此时栈顶到 x 之间（包含 x）的所有节点正好组成一个 SCC
c[0] 在这里当作计数器使用：当前已经分出的 SCC 个数。
++c[0] 先自增，得到新的编号。
c[x] = new_no：把根节点 x 先归入这个新 SCC。
例如之前已经有 2 个 SCC，c[0]==2，++c[0] 后为 3，则 c[x]=3
st 是手写的栈，st[0] 存储栈内元素个数（栈顶下标）。
st[st[0]] 即当前栈顶元素。
这个循环的条件：只要栈顶元素不是 x（根节点），就一直弹。
因为 x 在入栈时最先被压入，而它所在 SCC 的其他节点都比 x 后入栈、且在栈顶方向，所以栈里从 x 到栈顶是一整块连续的 SCC 元素，把它们全弹出归组
st[0]--：取出栈顶下标 st[0]，然后自减（模拟出栈，栈内元素个数减 1）。注意 -- 是后置递减，所以先取原值再减。
st[ st[0] ]（取的是递减前的原下标）：拿到栈顶那个节点。
c[ 该节点 ] = c[0]：把这个节点标记为属于 SCC 编号 c[0]
循环不断执行，直到栈顶变成 x 为止。此时 x 之上的所有节点都已弹出并标号，都归入了这个 SCC
上一步循环停在"栈顶 == x"，此时 x 仍在栈中。
这句 st[0]-- 就是把 x 本身也弹出栈（栈元素数减 1）。
x 的编号已经在第 2 步 c[x]=++c[0] 里标记过了，所以这里是纯出栈，不再重复标记



*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e6+10;

int fa[N], dep[N], sz[N], son[N];
vector<int> e[N];
void dfs(int x, int ff) {
    fa[x] = ff, dep[x] = dep[ff] + 1, sz[x] = 1;
    for (int y : e[x]) {
        if (y == ff) continue;
        dfs(y, x);
        sz[x] += sz[y];
        if (sz[son[x]] < sz[y]) son[x] = y;
    }
}

int dfn[N], top[N];
void dfs2(int x, int ff) {
    dfn[x] = ++dfn[0], top[x] = ff;
    if (son[x]) dfs2(son[x], ff);
    for (int y : e[x])
        if (y != fa[x] && y != son[x])
            dfs2(y, y);
}

vector<int> pos[N];
void update(int id, int l, int r, int L, int R, int a) {
    if (L <= l && R >= r)  { pos[id].push_back(a); return; }
    int mid = (l+r)>>1;
    if (L <= mid) update(id<<1, l, mid, L, R, a);
    if (R > mid) update(id<<1|1, mid+1, r, L, R, a);
}

int low[N], dfn2[N], st[N], c[N];
void tarjan(int x) {
    low[x] = dfn2[x] = ++dfn2[0], st[++st[0]] = x;
    for (int y : e[x]) {
        if (!dfn2[y]) { tarjan(y); low[x] = min(low[x], low[y]); }
        else if (!c[y]) low[x] = min(low[x], dfn2[y]);
    }
    if (dfn2[x] == low[x]) {
        c[x] = ++c[0];
        while (st[st[0]] != x) c[st[st[0]--]] = c[0];
        st[0]--;
    }
}

int n;
void update(int x, int y, int t) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        update(1, 1, n, dfn[top[x]], dfn[x], t);
        x = fa[top[x]];
    }
    if (dfn[x] > dfn[y]) swap(x, y);
    if (dfn[x] < dfn[y]) update(1, 1, n, dfn[x]+1, dfn[y], t);
}

int tot;
int solve(int id, int l, int r) {
    int z = 0;
    if (l != r) {
        int mid = (l+r)>>1, x = solve(id<<1, l, mid), y = solve(id<<1|1, mid+1, r);
        if (!x || !y) z = x + y;
        else {
            e[x].push_back(tot); e[tot^1].push_back(x^1);
            e[y].push_back(tot); e[tot^1].push_back(y^1);
            z = tot, tot += 2;
        }
    }
    for (int i : pos[id]) {
        if (z) {
            e[z].push_back(i^1); e[i].push_back(z^1);
            e[z].push_back(tot); e[tot^1].push_back(z^1);
            e[i].push_back(tot); e[tot^1].push_back(i^1);
            z = tot, tot += 2;
        } else z = i;
    }
    return z;
}

int m;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v; e[u].push_back(v); e[v].push_back(u);
    }
    dfs(1, 0); dfs2(1, 1);
    for (int i = 1; i <= n; i++) e[i].clear();
    cin >> m;
    for (int i = 1, a, b, c, d; i <= m; i++) {
        cin >> a >> b >> c >> d;
        update(a, b, i<<1); update(c, d, i<<1|1);
    }
    tot = 2*m + 2;
    solve(1, 1, n);
    for (int i = 1; i < tot; i++) if (!dfn2[i]) tarjan(i);
    for (int i = 1; i <= m; i++)
        if (c[i<<1] == c[i<<1|1]) { cout << "NO\n"; return 0; }
    cout << "YES\n";
    for (int i = 1; i <= m; i++) cout << 1+(c[i<<1]>c[i<<1|1]) << '\n';
    return 0;
}