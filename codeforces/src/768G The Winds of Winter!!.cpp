//
// Created by Psy.C on 2026/9/8.
//
/**
N：节点数上限。
node：边结构体，to 目标点，nxt 下一条边的下标。
a[N<<1]：存所有边（无向图每条边存两次，故乘 2
head[fr]：fr 的第一条边下标（头插法）。
add：把新边插入到 fr 的边表头部
sz[u]：以 u 为根时的子树大小。
mn[u]：u 的所有"独立分支"中最小的大小。
ans[u]：u 的最终答案。
n：节点总数。
son[u]：u 的重儿子（子树最大的儿子）。
mx[u]：u 子树最大的儿子编号。
sec[u]：u 子树第二大的儿子编号。
rt：整棵树的根。
oth：全局 multiset，存"子树大小×2"的集合，供后续快速查找某区间内的值

sz[u]=1; mn[u]=ans[u]=n;：初始化，子树大小 1，mn 和 ans 都先设为 n（极大值）。
遍历 u 的所有邻接点 v（跳过父亲 fa），对每个 v 先递归 dfs(v,u)。
递归返回后累加子树大小 sz[u] += sz[v]，并维护：
son[u]：若 v 的子树比当前重儿子大，则更新重儿子。
mn[u]：取所有儿子子树大小的最小值。
mx[u] / sec[u]：记录最大和第二大儿子子树大小的编号（第一大更新成 v，原第一大降级为第二大；否则比较看是否成为新的第二大）。
若 u 不是根 rt，考虑"u 上方"那一块（大小 n-sz[u]，即去掉子树后剩余部分）作为一条"虚拟分支"：
用它更新 mn[u]。
用它与儿子比较，更新 mx/sec（把 n-sz[u] 当作编号 0 的分支参与排序）。
最后把 2*sz[u] 插入全局集合 oth

T：某个 multiset（存的是 2*某块大小 或 2*某子树大小）。
maxx：当前最大的那块的"目标大小"。
minx：最小块的"目标大小"。
v：答案引用，用来更新最优值。
rd：修正值（用于把存储在集合里的"2 倍大小"转换回实际大小，因为集合里存的是 ×2 后的值）。
目的：在集合 T 中找一个值 t（代表某块大小），使得 maxx - t/2 与 minx 尽量接近，从而让"最大块与最小块"的差尽量小。它用 lower_bound 找关键分界点，再在前一个元素也检查一次，取更优者写入 v

del：从 multiset 删除一个值 v（用 lower_bound 定位后 erase 一个）。
calc(u, b)：计算 u 的"第 b 个分支"的大小——若 b 是某个儿子则返回它子树大小 sz[b]；若 b==0 表示取"u 上方那部分"，返回 n-sz[u]

anc：当前祖先链上"上方块大小×2"的集合。
Q[x]：每个"颜色/链"对应的 multiset，保存该重链上各子树大小的×2 值。
id[u]：u 属于的 Q 集合的编号（启发式合并时可能交换）。
cnt：Q 集合计数器
先把 2*sz[u] 从 oth 删除（因为 u 自己已不在"其它块"集合中）。
若 u 不是根，把 2*sz[fa]（即父亲那一块的大小×2）插入 anc——表示 u 的祖先链上那块。
若 son[u]==0（u 是叶子，没有儿子）：
ans[u]=n-1：叶子去掉后只剩一块大小为 n-1，差为 0（或题面定为 n-1）。
分配一个新 Q 集合给 u，插入值 2（对应一份大小为 1 的伪块）。
直接返回
对 u 的所有轻儿子 v 先递归 dfs2。
递归返回后，把 v 所属 Q 集合里的所有值插入到全局 oth（表示这些块从"u 内部"移动到了"外部其它块"集合，供后面匹配）
递归重儿子 son[u]，并把 u 的 Q 编号继承为重儿子的（重儿子最后处理、保留集合——启发式合并的关键
现在轻儿子都处理完了，把之前插入 oth 的各轻儿子链的值再删回去（把它们从中"借"出来，恢复现场），因为这些块实际属于 u 的内部。
MAX = calc(u, mx[u])、SEC = calc(u, sec[u])：取 u 的最大和第二大分支的实际大小（可能是儿子子树，也可能是上方那块
若最大与第二大分支大小相等：说明所有分支都一样大，直接 ans[u]=MAX（已经均分，差值为 0 或最优即 MAX）。
否则需要"从最大的分支里切出一部分给最小的分支"来拉平：
若最大分支是某个儿子 mx[u]：到该儿子的 Q 集合里用 check 找到最合适的切分点（rd=0）。
若最大分支是"上方那块"（mx[u]==0）：分两处找——从 anc（祖先块，rd=2*sz[u]）和从 oth（其它外部块，rd=0）里用 check 找。
最后 ans[u] = max(ans[u], SEC)：答案至少要取到第二大块的大小（因为第二大块无法被切，是下界）
再次遍历 u 的轻儿子 v，把它们的 Q 集合并入 u 的 Q 集合（启发式合并：总是把小集合并入大集合以降低复杂度，因此若 Q[now] 更大就交换 id）。合并后清空较小的集合。
若 u 不是根，把之前插入 ancestor 的 2*sz[fa] 删掉（恢复现场）。
最后把 2*sz[u]（u 自己这一整块的大小×2）插入 u 的 Q 集合，作为它的"代表块"供祖先使用


循环读 n 条边描述 u, v：
若 !u || !v（其中一个是 0）——说明 v（或 u）是"根"标记：题目输入里根用 0 占位，故 rt = u+v 确定真正的根。
否则正常加双向边，并统计每个点的度数 deg。
dfs(rt,0)：以根做第一遍 DFS，得到 sz、son、mx、sec、mn。
dfs2(rt,0)：做第二遍 DSU on tree 计算出每个节点的 ans。
若根 rt 的度数恰为 1（根是链的一端/叶子），则去掉根后只剩一块，答案 ans[rt]=n-1 特判。
最后顺序输出每个节点 1..n 的答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;
struct node { int to, nxt; } a[N<<1];

int tot, head[N];
void add(int fr, int to) {
    a[++tot].to = to, a[tot].nxt = head[fr], head[fr] = tot;
}

int sz[N], mn[N], ans[N], n, son[N], mx[N], sec[N], rt;
multiset<int> oth;
void dfs(int u, int fa) {
    sz[u] = 1; mn[u] = ans[u] = n;
    for (int i = head[u]; i != 0; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
        mn[u] = min(mn[u], sz[v]);
        if (sz[v] > sz[mx[u]]) sec[u] = mx[u], mx[u] = v;
        else {
            if (sz[v] > sz[sec[u]]) sec[u] = v;
        }
    }
    if (u != rt) {
        mn[u] = min(mn[u], n-sz[u]);
        if (n-sz[u] > sz[mx[u]]) sec[u] = mx[u], mx[u] = 0;
        else {
            if (n-sz[u] > sz[sec[u]]) sec[u] = 0;
        }
    }
    oth.insert(2*sz[u]);
}

void check(multiset<int> &T, int maxx, int minx, int &v, int rd) {
    auto x = T.lower_bound(maxx-minx+rd);
    if (x == T.end()) {
        --x;
        v = min(v, maxx-((*x)-rd)/2);
    } else {
        v = min(v, minx+(*x-rd)/2);
        if (x != T.begin()) {
            --x;
            v = min(v, maxx-((*x)-rd)/2);
        }
    }
}

void del(multiset<int> &T, int v) { T.erase(T.lower_bound(v)); }
int calc(int u, int b) { return b ? sz[b] : n-sz[u]; }

multiset<int> anc, Q[N];
int id[N], cnt;
void dfs2(int u, int fa) {
    del(oth, 2*sz[u]);
    if (u != rt) anc.insert(2*sz[fa]);
    if (!son[u]) {
        ans[u] = n-1; id[u] = ++cnt;
        Q[cnt].insert(2);
        return;
    }
    for (int i = head[u]; i != 0; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa || v == son[u]) continue;
        dfs2(v, u);
        for (auto it = Q[id[v]].begin(); it != Q[id[v]].end(); ++it)
            oth.insert(*it);
    }
    dfs2(son[u], u); id[u] = id[son[u]];
    for (int i = head[u]; i != 0; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa || v == son[u]) continue;
        for (auto it = Q[id[v]].begin(); it != Q[id[v]].end(); ++it)
            del(oth, *it);
    }
    int MAX = calc(u, mx[u]), SEC = calc(u, sec[u]);
    if (MAX == SEC) ans[u] = MAX;
    else {
        if (mx[u]) check(Q[id[mx[u]]], MAX, mn[u], ans[u], 0);
        else {
            check(anc, MAX, mn[u], ans[u], 2*sz[u]);
            check(oth, MAX, mn[u], ans[u], 0);
        }
        ans[u] = max(ans[u], SEC);
    }
    for (int i = head[u]; i != 0; i = a[i].nxt) {
        int v = a[i].to;
        if (v == fa || v == son[u]) continue;
        int now = id[v];
        if (Q[now].size() > Q[id[u]].size()) swap(id[u], now);
        for (auto it = Q[now].begin(); it != Q[now].end(); ++it)
            Q[id[u]].insert(*it);
        Q[now].clear();
    }
    if (u != rt) del(anc, 2*sz[fa]);
    Q[id[u]].insert(2*sz[u]);
}

inline int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int deg[N];
int main() {
    fast;
    n = read();
    for (int i = 1; i <= n; ++i) {
        int u = read(), v = read();
        if (!u || !v) rt = u + v;
        else {
            add(u, v); add(v, u);
            ++deg[u]; ++deg[v];
        }
    }
    dfs(rt, 0); dfs2(rt, 0);
    if (deg[rt] == 1) ans[rt] = n-1;
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
    return 0;
}