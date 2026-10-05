//
// Created by Psy.C on 2026/10/5.
//
/**
lg2i(n)：二进制最高位 → 树的层号
用分治掩码求出二进制最高位所在位（即 ⌊log₂n⌋）
节点编号的二进制位数决定它在树中的深度层。
get(p)：求节点 p 子树内实际存在的节点个数（在规模为 n 的堆树中）
dep 为整棵树深度；d 为 p 到叶子还剩几层
先算“按满二叉子树应有 2^d−1 个节点”，再根据 n 截断到实际只会多出 n - (p<<d) + 1 个（最后一层未满），返回该子树在此树中的真实节点数
lca(u,v)：带“记录足迹”的 LCA，并把沿途压缩节点登记进 id/to
利用 lg2i 得到两节点深度，先对齐深度、再同时上跳找 LCA
每次经历一个节点就把该节点加入全局 id（分配新编号到压缩树）、to[cnt] 记录其原始编号 即把虚树所需的节点登记下来。
dfs(p)：在压缩树上做带记忆的求和
沿压缩树的边做 DFS，累加各节点子树大小 sz，得到某种路径总长（对 mod 取模）
读 n、m 若 m=0 直接输出 n*n % mod（无特殊点时的退化情形）
对每个点对反复取 LCA，求出这些点的“全局根” root
确定每个压缩节点的子树大小 sz[p]：若其左右孩子不在登记集合中，则孩子子树按 get() 计入 同时在已有父节点之间连边
再把 m 个原始点对连边
最后 for p: path += sz[p]*dfs(p)，对 mod 求和输出
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int lg2i(int n) {
    int l = 0;
    if (n & 0xFFFF0000) { l |= 16; n &= 0xFFFF0000; }
    if (n & 0xFF00FF00) { l |=  8; n &= 0xFF00FF00; }
    if (n & 0xF0F0F0F0) { l |=  4; n &= 0xF0F0F0F0; }
    if (n & 0xCCCCCCCC) { l |=  2; n &= 0xCCCCCCCC; }
    if (n & 0xAAAAAAAA) { l |=  1; n &= 0xAAAAAAAA; }
    return l;
}
constexpr int N = 640, mod = 1e9+7;

int dep, n;
inline int get(int p) {
    int d = dep - lg2i(p);
    return (1 << d) + max(0, min(n - (p << d) + 1, 1 << d)) - 1;
}

unordered_map<int, int> id;
int cnt, to[N], sz[N];
int lca(int u, int v) {
    int du = lg2i(u), dv = lg2i(v);
    while (du > dv) { if (!id.contains(u)) id[u] = ++cnt, to[cnt] = u; u >>= 1, --du; }
    while (dv > du) { if (!id.contains(v)) id[v] = ++cnt, to[cnt] = v; v >>= 1, --dv; }
    while (u ^ v) {
        if (!id.contains(u)) id[u] = ++cnt, to[cnt] = u; u >>= 1, --du;
        if (!id.contains(v)) id[v] = ++cnt, to[cnt] = v; v >>= 1, --dv;
    }
    if (!id.contains(v)) id[v] = ++cnt, to[cnt] = v;
    return v;
}

bool vis[N];
vector<int> e[N];
ll dfs(int p) {
    ll path = sz[p];
    if (vis[p]) return 0;
    vis[p] = true;
    for (auto& t : e[p]) path = (path + dfs(t)) % mod;
    vis[p] = false;
    return path;
}

int eu[10], ev[10], m;
int main() {
    scanf("%d%d", &n, &m); dep = lg2i(n);
    if (!m) {
        printf("%lld\n", static_cast<long long>(n) * n % mod);
        return 0;
    }

    int root = -1;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", eu + i, ev + i);
        if (root == -1) root = lca(eu[i], ev[i]);
        else root = lca(root, lca(eu[i], ev[i]));
    }

    for (int p = 1; p <= cnt; ++p) {
        sz[p] = 1;
        if (n >= (to[p] << 1) && !id.contains(to[p] << 1))
            sz[p] += get(to[p] << 1);
        if (n >= (to[p] << 1 | 1) && !id.contains(to[p] << 1 | 1))
            sz[p] += get(to[p] << 1 | 1);

        if (to[p] > 1) {
            auto parent_iter = id.find(to[p] >> 1);
            if (parent_iter == id.end()) {
                sz[p] += n - get(to[p]);
            } else {
                e[p].push_back(parent_iter->second);
                e[parent_iter->second].push_back(p);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        auto u_iter = id.find(eu[i]), v_iter = id.find(ev[i]);
        e[u_iter->second].push_back(v_iter->second);
        e[v_iter->second].push_back(u_iter->second);
    }

    ll path = 0;
    for (int p = 1; p <= cnt; ++p)
        path = (path + sz[p] * dfs(p) % mod) % mod;
    printf("%lld\n", path);
    return 0;
}