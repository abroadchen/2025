//
// Created by Psy.C on 2026/10/13.
//
/**
N 节点规模上限，mod 是哈希/取模用的质数，base=131 是哈希底数，S=26 是字符集大小【自包含，无外部数据】
pw[i]=base^i（哈希用幂）
邻接表，每条边带一个字符 snd（边权）
dep：节点深度；hsh：从根到该节点的路径哈希；fch：节点到父亲的边字符；anc：倍增祖先表
用前缀哈希的"差分"快速得到某一段链的哈希值，用于快速比对两段边字符序列是否相同【树哈希技巧，自包含】
用于后续"树上路径 +1 / 查询子树内贡献"
ins(s,id)：把模式串 s 插入字典树，ed[id] 记录第 id 个串的终止节点【AC 自动机建 trie，自包含】。
build()：BFS 建立 fail 指针，把 fail 边建成树（e[fa[t]]），为后面在 fail 树上做子树查询做准备；同时补全 son 转移。
dfs(id)：给 fail 树求 dfn 序和子树大小（用于把"fail 树子树"映射成一段连续区间，配合 BIT 查询）
这是在 trie/AC 自动机自动机上做 DFS，维护当前树上走到的模式串前缀节点 cur，配合 fail 树 dfn 区间 + BIT 统计，实现"树上每条路径上的模式串匹配计数"【自包含逻辑】
这颗 fail 树（失配树）用于处理字符串的 border / 前后缀相等的长度匹配，为后面"两个串拼起来 / 前后缀条件"的计数服务【自包含】
处理"前缀 + 后缀"拼起来恰好构成完整匹配的情形，利用正/反两个失配树的 dfn 区间做对称统计【自包含逻辑】
标准 O(n log n) 倍增求 SA、rk
用 树哈希 对比"树上某条链"和"后缀数组中的某段"，在树上倍增跳祖先找 LCP 长度【树上 LCP + 后缀数组结合，自包含】。
核心思想：给定询问 (u,v,k)，要找一个后缀最长和"u→某个祖先"的链匹配，通过二分/倍增在 SA 上找最接近的候选
分 calc(rev/u) 和 calc(ori/v) 两次扫描，再用 comb 合并答案

n 个点(树)，m 个模式串，q 个询问
// 读树（边带字符），建 tree
// 读 m 个模式串 s[i]，建两个 AC 自动机 A（正）和 AR（反）
// 处理 q 个询问 (u,v,k)：问 k 号模式串在 树上的 u→v 路径 上出现的次数
路径拐点（最近公共祖先）
// 把路径拆成"向下的一段"和"向上的一段"，分别用 AR 和 A 处理，并用
    // buc[节点] 挂查询，符号正负实现差分（区间减重复部分）
    // 跨过 LCA 中间的部分留给 sa::solve 处理
三部分合并统计
输出每个询问答案
 */
#include <bits/stdc++.h>
#define ii pair<int, int>
using namespace std;

constexpr int N = 2e5+5, mod = 1004535809, K = 18, base = 131, S = 26;

int pw[N], n;
namespace tree {
    vector<ii> e[N];
    int lg, dep[N], hsh[N], fch[N], anc[K][N];
    int get(int u, int v) {//提取 u→v 这条链的哈希（u 是 v 的祖先）
        assert(dep[u] <= dep[v]);
        return (hsh[v] + mod - 1ll * hsh[u] * pw[dep[v] - dep[u]] % mod) % mod;
    }
    void dfs(int id, int ff) {
        dep[id] = dep[anc[0][id] = ff] + 1;
        for(auto [fst, snd] : e[id]) {
            int it = fst;
            if(it == ff) continue;
            hsh[it] = (1ll * hsh[id] * base + snd) % mod;//路径哈希递推
            fch[it] = snd, dfs(it, id);
        }
    }
    void build() {
        lg = 31 - __builtin_clz(n);
        dfs(1, 0);
        for(int i = 1; i <= lg; i++)
            for(int j = 1; j <= n; j++)
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
    }
    int kth(int u, int k) {//向上跳 k 步
        for(int i = lg; ~i; i--) if(k >> i & 1) u = anc[i][u];
        return u;
    }
    int lca(int u, int v) {//最近公共祖先
        if(dep[u] < dep[v]) swap(u, v);
        u = kth(u, dep[u] - dep[v]);
        if(u == v) return u;
        for(int i = lg; ~i; i--) if(anc[i][u] != anc[i][v]) u = anc[i][u], v = anc[i][v];
        return anc[0][u];
    }
}

struct BIT {
    int c[N];
    void add(int x, int v) {while(x < N) c[x] += v, x += x & -x;}//单点加
    void add(int l, int r, int v) {add(l, v), add(r + 1, -v);}//区间加（差分实现）
    int query(int x) {int s = 0; while(x) s += c[x], x -= x & -x; return s;}//单点前缀和
    int query(int l, int r) {return query(r) - query(l - 1);}//区间和
};

int k[N], ans[N];
struct ac {
    int node{}, son[N][S]{}, fa[N]{}, ed[N]{};
    void ins(const string& s, int id) {
        int p = 0;
        for(char it : s) {
            if(!son[p][it - 'a']) son[p][it - 'a'] = ++node;
            p = son[p][it - 'a'];
        }
        ed[id] = p;
    }
    int dn{}, dfn[N]{}, sz[N]{};
    vector<int> e[N], buc[N];
    void dfs(int id) {
        dfn[id] = ++dn, sz[id] = 1;
        for(int it : e[id]) dfs(it), sz[id] += sz[it];
    }
    void build() {
        queue<int> q;
        for(int i = 0; i < S; i++) if(son[0][i]) q.push(son[0][i]);
        while(!q.empty()) {
            int t = q.front(); q.pop();
            e[fa[t]].push_back(t);
            for(int i = 0; i < S; i++)
                if(son[t][i]) q.push(son[t][i]), fa[son[t][i]] = son[fa[t]][i];
                else son[t][i] = son[fa[t]][i];
        }
        dfs(0);
    }
    BIT tr{};
    void solve(int id, int ff, int cur) {
        if(cur) tr.add(dfn[cur], 1);//当前路径位置 +1
        for(int it : buc[id]) {//处理挂在 id 上的查询（含差分正负号）
            int id = abs(it), c = id / it;//it 带符号：负号表示差分减
            //第 id 个询问对应的模式串的末尾节点 该节点在 fail 树上的子树区间
            int x = ed[k[id]], l = dfn[x], r = dfn[x] + sz[x] - 1;
            ans[id] += tr.query(l, r) * c;//累加贡献，c=±1 实现加/减
        }
        for(auto [fst, snd] : tree::e[id]) {//沿原树 DFS，同步 AC 自动机状态 cur
            int it = fst;
            if(it != ff) solve(it, id, son[cur][snd - 'a']);
        }
        if(cur) tr.add(dfn[cur], -1);//回溯时撤销
    }
} A, AR;

struct border {
    int lg{}, dn{}, dfn[N]{}, sz[N]{}, nxt[N]{}, anc[K][N]{};
    vector<int> e[N];
    void dfs(int id) {
        dfn[id] = ++dn, sz[id] = 1;
        for(int it : e[id]) dfs(it), sz[id] += sz[it];
    }
    void build(int n, int *s) {
        dn = 0;
        for(int i = 0; i <= n; i++) e[i].clear();
        for(int i = 2, j = 0; i <= n; i++) {
            while(j && s[j + 1] != s[i]) j = nxt[j];
            anc[0][i] = nxt[i] = j += s[j + 1] == s[i];
        }
        //用 next 边建成"失配树"（fail 树），并倍增
        for(int i = 1; i <= n; i++) e[nxt[i]].push_back(i);
        //求 dfn、子树，建倍增
        dfs(0), lg = 31 - __builtin_clz(dn);
        for(int i = 1; i <= lg; i++)
            for(int j = 0; j <= dn; j++)
                anc[i][j] = anc[i - 1][anc[i - 1][j]];
    }
    int binary(int x, int lim) {//二分/倍增跳到父链上<=lim 的最高祖先
        if(x <= lim) return x;
        for(int i = lg; ~i; i--) if(anc[i][x] > lim) x = anc[i][x];
        return anc[0][x];
    }
} ori, rev;

int varg[N], uarg[N], ulcp[N], vlcp[N];
namespace comb {
    vector<int> buc[N];
    BIT tr;
    void dfs(int n, int id) {
        //反串的 fail 树区间
        int l = rev.dfn[n - id], r = l + rev.sz[n - id] - 1;
        if(id && id < n) tr.add(l, r, 1);
        for(int it : buc[id]) ans[it] += tr.query(rev.dfn[varg[it]]);
        for(int it : ori.e[id]) dfs(n, it);//沿正串 fail 树递归
        if(id && id < n) tr.add(l, r, -1);
    }
    void solve(int n, vector<int> &qu) {
        for(int i = 1; i <= n; i++) buc[i].clear();
        for(int it : qu) {
            uarg[it] = ori.binary(uarg[it], ulcp[it]);
            varg[it] = rev.binary(varg[it], vlcp[it]);
            if(uarg[it] + varg[it] < n) continue;
            buc[uarg[it]].push_back(it);
        }
        dfs(n, 0);
    }
}

int m, d[N], u[N], v[N];
string s[N];
namespace sa {
    int n, s[N];
    vector<int> qu[N];
    int sa[N], rk[N], ork[N], buc[N], id[N], hsh[N];
    int get(int l, int r) {return l--, (hsh[r] + mod - 1ll * hsh[l] * pw[r - l] % mod) % mod;}
    bool cmp(int a, int b, int w) {return ork[a] == ork[b] && ork[a + w] == ork[b + w];}
    void build() {
        int m = 1 << 7, p = 0;
        memset(rk, 0, n + 5 << 2);
        memset(buc, 0, m + 5 << 2);
        for(int i = 1; i <= n; i++) buc[rk[i] = s[i]]++;
        for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
        for(int i = n; i; i--) sa[buc[rk[i]]--] = i;
        for(int w = 1; ; w <<= 1, m = p, p = 0) {
            for(int i = n - w + 1; i <= n; i++) id[++p] = i;
            for(int i = 1; i <= n; i++) if(sa[i] > w) id[++p] = sa[i] - w;
            memset(buc, 0, m + 5 << 2);
            memcpy(ork, rk, n + 5 << 2);
            p = 0;
            for(int i = 1; i <= n; i++) buc[rk[i]]++;
            for(int i = 1; i <= m; i++) buc[i] += buc[i - 1];
            for(int i = n; i; i--) sa[buc[rk[id[i]]]--] = id[i];
            for(int i = 1; i <= n; i++) rk[sa[i]] = cmp(sa[i - 1], sa[i], w) ? p : ++p;
            if(p == n) break;
        }
    }
    pair<int, ii> lcp(int id, int d, int u) {
        assert(u != d);
        auto chk = [&](int p) {
            int dis = tree::dep[p] - tree::dep[d];
            if(id + dis - 1 > n) return false; // add this line
            return tree::get(d, p) == get(id, id + dis - 1);
        };
        for(int i = tree::lg; ~i; i--) {
            int x = tree::anc[i][u];
            if(tree::dep[x] <= tree::dep[d]) continue;
            if(!chk(x)) u = x;
        }
        int nct = 0;
        if(!chk(u)) nct = tree::fch[u], u = tree::anc[0][u];
        int L = tree::dep[u] - tree::dep[d];
        return {L, {s[id + L], nct}};
    }
    void solve() {
        for(int i = 1; i <= m; i++) {//对字符串 i 建后缀数组（反串）
            if(qu[i].empty()) continue;
            n = ::s[i].size(), s[n + 1] = 0;
            for(int j = 1; j <= n; j++) s[j] = ::s[i][n - j];
            auto calc = [&](border &T, int *u, int *L, int *arg) {
                for(int j = 1; j <= n; j++) hsh[j] = (1ll * hsh[j - 1] * base + s[j]) % mod;
                build(), T.build(n, s);
                for(int it : qu[i]) {
                    int l = 0, r = n;
                    while(l < r) {
                        int m = l + r + 2 >> 1;
                        auto [fst, snd] = lcp(sa[m], d[it], u[it]).second;
                        if(fst < snd) l = m;
                        else r = m - 1;
                    }
                    if(l) {
                        int tmp = lcp(sa[l], d[it], u[it]).first;
                        if(tmp > L[it]) L[it] = tmp, arg[it] = sa[l];
                    }
                    if(l < n) {
                        int tmp = lcp(sa[l + 1], d[it], u[it]).first;
                        if(tmp > L[it]) L[it] = tmp, arg[it] = sa[l + 1];
                    }
                    if(!L[it]) continue;
                    arg[it] = n - arg[it] + 1;
                }
            };
            //通过 calc 计算正反两个方向的最长公共前缀，确定匹配区间
            calc(rev, u, ulcp, uarg), reverse(s + 1, s + n + 1);
            calc(ori, v, vlcp, varg), comb::solve(n, qu[i]);
        }
    }
}

inline int rd() {
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

int q;
int main() {
    cin >> n >> m >> q;
    for(int i = pw[0] = 1; i < N; i++) pw[i] = 1ll * pw[i - 1] * base % mod;
    for(int i = 1; i < n; i++) {
        int x = rd(), y = rd();
        char ch;
        cin >> ch;
        tree::e[x].emplace_back(y, ch);
        tree::e[y].emplace_back(x, ch);
    }
    tree::build();
    for(int i = 1; i <= m; i++) {
        cin >> s[i], A.ins(s[i], i);
        ranges::reverse(s[i]), AR.ins(s[i], i);
        ranges::reverse(s[i]);
    }
    A.build(), AR.build();
    for(int i = 1; i <= q; i++) {
        u[i] = rd(), v[i] = rd(), k[i] = rd();
        int L = s[k[i]].size();
        if(L > n) continue;
        d[i] = tree::lca(u[i], v[i]);
        int du = tree::dep[u[i]] - tree::dep[d[i]];
        if(du >= L) {
            int anc = tree::kth(u[i], du - L + 1);
            AR.buc[anc].push_back(-i);
            AR.buc[u[i]].push_back(i);
            u[i] = anc, du = L - 1;
        }
        int dv = tree::dep[v[i]] - tree::dep[d[i]];
        if(dv >= L) {
            int anc = tree::kth(v[i], dv - L + 1);
            A.buc[anc].push_back(-i);
            A.buc[v[i]].push_back(i);
            v[i] = anc, dv = L - 1;
        }
        if(u[i] != d[i] && v[i] != d[i] && du + dv >= L) sa::qu[k[i]].push_back(i);
    }
    A.solve(1, 0, 0);
    AR.solve(1, 0, 0);
    sa::solve();
    for(int i = 1; i <= q; i++) write(ans[i]), putchar('\n');
    return 0;
}