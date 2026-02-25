//
// Created by Psy.C on 2026/2/25.
//
/**
声明两个模数，用于双哈希
双哈希的乘法运算
双哈希的加法运算
双哈希的减法运算
模数数组，用于随机选择
随机选择未使用的模数，避免哈希冲突。

sz[N]：子树大小
dep[N]：节点深度
fa[N]：父节点
head[N]：链式前向星头数组
nxt[N<<1]：链式前向星next数组
to[N<<1]：链式前向星终点数组
son[N]：重儿子
siz：边计数器

第一次DFS，计算子树信息：
sz[u] = 1：初始化子树大小
dep[u] = dep[fa[u]] + 1：计算深度
遍历子节点，更新子树大小和重儿子


top[N]：所在重链的顶端节点
dfn[N]：DFS序
id[N]：DFS序对应的节点
cnt：DFS序计数器
第二次DFS，进行树链剖分：
top[u] = tp：记录重链顶端
dfn[u] = ++cnt：分配DFS序
id[cnt] = u：记录序号对应节点
优先处理重儿子，保持重链连续
处理轻儿子，开启新的重链

树链剖分求LCA：
当两点不在同一重链时，跳到深度较浅的链顶端
直到两点在同一重链，返回深度较浅的点

获取路径上所有区间的函数：
up：存储向上的区间
dw：存储向下的区间
收集x到LCA路径上的区间（向上）
收集y到LCA路径上的区间（向下）
处理特殊情况并合并区间

h1[N]：正向哈希前缀和
h2[N]：反向哈希前缀和
p[N]：哈希基的幂次
获取指定区间的哈希值：
flag=1：反向区间
flag=0：正向区间


n：节点数
m：查询数
s[N]：字符串数组
哈希基，使用双哈希避免冲突
存储查询路径的区间

flf/flg：区间方向标志
lf/lg：区间长度
len：可比较的最小长度
如果当前长度的哈希值相等
更新指针位置，累加匹配长度
二分查找精确的匹配长度

 */
#include <bits/stdc++.h>
#define ll long long
#define P pair<ll, ll>
using namespace std;
constexpr int N = 3e5+1;

ll mod1, mod2;
P operator*(const P& a, const P& b) {
    return {a.first*b.first%mod1, a.second*b.second%mod2};
}
P operator+(const P& a, const P& b) {
    return {(a.first+b.first)%mod1, (a.second+b.second)%mod2};
}
P operator-(const P& a, const P& b) {
    return {(a.first+mod1-b.first)%mod1, (a.second+mod2-b.second)%mod2};
}

constexpr ll modd[] = {
    19260817, 381335473,  252412907, 173275057, 415924151, 490280677, 215695621, 311094167
};
bool vis[11];
int get_mod() {
    int x;
    do {
        x = rand() % 8;
    } while (vis[x]);
    vis[x] = true;
    return modd[x];
}

int read() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

void out(const int x) {
    if (x > 9) out(x/10);
    putchar(x % 10 + '0');
}

int sz[N], dep[N], fa[N], head[N], nxt[N<<1], to[N<<1], son[N], siz;
void add(const int x, const int y) {
    to[++siz] = y; nxt[siz] = head[x]; head[x] = siz;
}

void dfs(const int u) {
    sz[u] = 1; dep[u] = dep[fa[u]] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        const int v = to[i];
        if (v == fa[u]) continue;
        fa[v] = u;
        dfs(v);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
    }
}

int top[N], dfn[N], id[N], cnt;
void dfs(const int u, const int tp) {
    top[u] = tp; dfn[u] = ++cnt; id[cnt] = u;
    if (son[u]) dfs(son[u], tp);
    for (int i = head[u]; i; i = nxt[i]) {
        const int v = to[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs(v, v);
    }
}

int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] > dep[y] ? y : x;
}

vector<P> up, dw;
vector<P> get(int x, int y) {
    const int lca = LCA(x, y); up.clear();
    while (top[x] != top[lca]) {
        up.push_back({dfn[x], dfn[top[x]]});
        x = fa[top[x]];
    }
    up.push_back({dfn[x], dfn[lca]});
    while (top[y] != top[lca]) {
        dw.push_back({dfn[top[y]], dfn[y]});
        y = fa[top[y]];
    }
    if (lca != y) dw.push_back({dfn[son[lca]], dfn[y]});
    while (dw.size()) up.push_back(dw.back()), dw.pop_back();
    return up;
}

P h1[N], h2[N], p[N];
P get(const int flag, const int st, const int len) {
    if (flag) return h2[st-len+1] - h2[st+1] * p[len];
    return h1[st+len-1] - h1[st-1] * p[len];
}

int n, m;
char s[N];
P B = {127, 23333};
vector<P> f, g;
int main() {
    srand(time(0)); mod1 = get_mod(); mod2 = get_mod();
    n = read(); scanf("%s", s+1); p[0] = {1, 1}; p[1] = B;
    for (int i = 2, u, v; i <= n; ++i) {
        u = read(); v = read();
        add(u, v); add(v, u);
        p[i] = p[i-1]*B;
    }
    dfs(1); dfs(1, 1);
    for (int i = 1; i <= n; ++i) {
        int x = s[id[i]];
        h1[i] = h1[i-1]*B + make_pair(x, x);
    }
    for (int i = n; i >= 1; --i) {
        int x = s[id[i]];
        h2[i] = h2[i+1]*B + make_pair(x, x);
    }
    m = read();
    while (m--) {
        const int a = read(), b = read(), c = read(), d = read();
        f = get(a, b); g = get(c, d);
        int i = 0, j = 0, ans = 0;
        while (i < f.size() && j < g.size()) {
            const int f1 = f[i].first, f2 = f[i].second,
            g1 = g[j].first, g2 = g[j].second,
            flf = f2 < f1, flg = g2 < g1,
            lf = abs(f1 - f2) + 1, lg = abs(g2 - g1) + 1,
            len = min(lf, lg);

            if (P hf = get(flf, f1, len), hg = get(flg, g1, len); hf == hg) {
                if (len == lf) i++;
                else f[i].first = flf == 1 ? f1 - len : f1 + len;
                if (len == lg) j++;
                else g[j].first = flg == 1 ? g1 - len : g1 + len;
                ans += len;
            } else {
                int l = 0, r = len, res = 0;
                while (l <= r) {
                    if (const int mid = (l + r) >> 1; get(flf, f1, mid) == get(flg, g1, mid))
                        l = mid + 1, res = mid;
                    else r = mid - 1;
                }
                ans += res;
                break;
            }
        }
        out(ans);
        puts("");
    }
    return 0;
}