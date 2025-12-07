//
// Created by Psy.C on 2025/12/6.
//
/*
 *Q 为最大操作次数
*N: 最大节点数
M: 字母表大小（小写字母）
K: 倍增层数上限
B1, B2: 用于字符串哈希的基数
*m: 操作总数
n1: Trie树节点数
n2: 普通树节点数
a[]: Trie节点映射
dep[]: 树深度
op[]: 操作类型
tr[][]: Trie孩子指针
fa[][]: 倍增祖先表
to[]: 当前节点对应的字符
lg[]: 对数预处理数组
b[]: 映射数组
bs[]: 幂次缓存（哈希用）
h[]: 节点哈希值
ans: 答案累计
 *
*计算每个Trie节点子树大小siz[u]
构建哈希值val[v]（类似字符串哈希）
找重儿子hs[u]（用于后续重链剖分
 *
*DFS序dfn[u] 和反向映射id[idx]
重链长度len[u]
保证重儿子优先访问（重链剖分顺序）
 *
*匹配两个结构中具有相同“形态”的节点：
使用倍增+哈希比较的方式寻找最佳匹配点
如果无法继续匹配就返回当前节点
 *
*自定义树状数组结构体，支持单点更新和前缀和查询：
t1: 维护Trie节点相关信息
t2: 维护普通树节点相关信息
 *
 *预处理幂次bs[i]用于哈希计算
*读取并处理m次操作：
op[i]==1: 在Trie中添加边（扩展字典树）
op[i]==2: 在普通树中添加节点（构建新树结构）
同时维护各自结构的相关属性（父子关系、深度、哈希等）
*运行两次DFS完成结构初始化
构建对数表lg[]供倍增使用
构建倍增祖先表fa[][]
 *建立两棵树之间节点的映射关系b[i]，即每个普通树节点在Trie中的对应节点
 *初始化树状数组状态，并设置初始答案为1
*依次处理每次操作并输出当前答案：
若是Trie插入操作，则查询与其相关的普通树节点数量
若是普通树插入操作，则查询与其相关的Trie节点数量
更新相应的树状数组并累加到总答案中
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define p 998244353
#define Q 3e5
using namespace std;

constexpr int N = 3e5+5, M = 26, K = 20, B1 = 47, B2 = 131;
int m, n1, n2, a[N], dep[N], op[N<<1],
tr[N][M+1], fa[N][K], to[N], lg[N<<1], b[N];
ll bs[N<<1], h[N], ans;

int siz[N], val[N], hs[N];
void dfs(const int u) {
    siz[u] = 1;
    for (int i = 0; i < M; ++i) {
        const int v = tr[u][i];
        if (!v) continue;
        val[v] = (B2 * val[u] + i + B1) % p;
        dfs(v);
        siz[u] += siz[v];
        if (siz[v] > siz[hs[u]]) hs[u] = v;
    }
}

int dfn[N], idx, id[N], len[N];
void dfs1(const int u) {
    dfn[u] = ++idx; id[idx] = u;
    if (!hs[u]) return;
    dfs1(hs[u]); len[u] = len[hs[u]] + 1;
    for (int i = 0; i < M; ++i) {
        const int v = tr[u][i];
        if (!v || v == hs[u]) continue;
        dfs1(v);
    }
}

int dfs2(int u, int v, const int s) {
    for (int i = lg[min(len[v], dep[u])]; ~i; --i) {
        if ((h[s] - h[fa[u][i]] + p) % p ==
            val[id[dfn[v]+(1<<i)]] * bs[dep[fa[u][i]]] % p) {//对齐两个字符串的哈希比较基准
            u = fa[u][i];
            v = id[dfn[v]+(1<<i)];
        }
    }
    if (u == 1 || !tr[v][to[u]]) return v;
    return dfs2(fa[u][0], tr[v][to[u]], s);
}

struct ta {
    int t[N];
    static int lb(const int x) { return x&(-x); }
    void update(int x, const int y) {
        for (; x <= Q; x += lb(x)) t[x] += y;
    }
    int query(int x) const {
        int sum = 0;
        for (; x; x -= lb(x)) sum += t[x];
        return sum;
    }
} t1, t2;

int main() {
    fast;
    cin >> m; n1 = n2 = 1; dep[1] = a[1] = 1; bs[0] = 1;
    for (int i = 1; i <= m; ++i) bs[i] = bs[i-1] * B2 % p;
    for (int i = 1; i <= m; ++i) {
        char c; int u;
        cin >> op[i] >> u;
        while (true) { cin.get(c); if ('a' <= c && c <= 'z') break; }
        if (op[i] == 1) {
            n1++;//在字典树中，从节点 a[u] 出发，通过字符 c 可以到达的子节点
            if (!tr[a[u]][c-'a']) tr[a[u]][c-'a'] = n1;//创建新节点
            a[n1] = tr[a[u]][c-'a'];//更新操作序列到字典树节点的映射
        } else {
            n2++;
            dep[n2] = dep[u] + 1; fa[n2][0] = u; to[n2] = c - 'a';
            h[n2] = (h[u] + (static_cast<ll>(B1) + to[n2]) * bs[dep[u]]) % p;
        }
    }
    dfs(1); dfs1(1);
    lg[0] = -1;
    for (int i = 2; i <= m; ++i) lg[i] = lg[i>>1] + 1;
    for (int j = 1; j <= lg[n2]; ++j) {
        for (int i = 1; i <= n2; ++i)
            fa[i][j] = fa[fa[i][j-1]][j-1];
    }
    b[1] = 1;
    for (int i = 2; i <= n2; ++i) b[i] = dfs2(i, 1, i);
    t1.update(dfn[1], 1), t1.update(dfn[1]+siz[1], -1);
    t2.update(dfn[b[1]], 1); ans = 1;
    for (int i = 1, x = 1, y = 1; i <= m; ++i) {
        if (op[i] == 1) {
            const int u = a[++x];
            ans += t2.query(dfn[u]+siz[u]-1) - t2.query(dfn[u] - 1);
            t1.update(dfn[u], 1), t1.update(dfn[u]+siz[u], -1);
        } else {
            const int u = b[++y];
            ans += t1.query(dfn[u]);
            t2.update(dfn[u], 1);
        }
        cout << ans << '\n';
    }
    return 0;
}