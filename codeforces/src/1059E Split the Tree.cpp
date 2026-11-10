//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
head/nxt：邻接表（链式前向星）‍存储儿子，head[u] 指向 u 的第一个儿子，nxt[i] 指向下一个兄弟。
dep[u]：u 的深度（根=1）。
pre[u]：从根到 u 的权值前缀和（pre[u] = sum(val 沿根→u)）。
S：路径权值上限；L：深度跨度上限。
st[]、sp[]、top：DFS 栈。st 保存当前祖先链上的节点 id，sp 保存这些节点的前缀和（用于二分）。
to[u]：u 往上合法能到达的最(靠上/满足约束)的祖先（后面会用到逆序去重）
读 n、L、S；读点权，若某点权值已然 > S，则该点所在的任何链都无法满足 → 直接 -1。
读父节点，初始化每个点的深度
前缀和 pre[i]。
建子节点链（前向星，从 2..n 挂到父节点）
入口：把 u 压入祖先栈，记录其前缀和到 sp。
线索 1（权值和 ≤ S）‍：sp[1..top] 是从根到祖先链的前缀和序列（递增）。要找最上面的（最靠近根、使链权和尽量大但仍 ≤S）合法祖先，等价于找 sp 中第一个 ≥ pre[u]-S 的位置。lower_bound(...) - sp + 1 得到该位置下标 to[u]（栈下标），这是满足"权值和 ≤ S"的约束下，能取到的最靠近根的祖先层
线索 2（深度差 ≤ L）‍：还要保证 u 到该祖先的深度差 ≤ L，即祖先深度 ≥ dep[u]-L+1。所以取 max(dep[u]-L+1, to[u]) 作为最终栈下标——取两者中较深者（更深=更靠近 u=更安全），to[u] = st[该下标] 即合法上限祖先 id。
递归儿子，回溯时 top-- 出栈。
to[u] 的物理意义：从 u 出发、沿祖先方向，在不破坏"S 权值和、L 深度"两个约束的前提下，能达到的最上（最深越界点之上的）合法节点。它是"能覆盖 u 的可行域的上边界"
并查集，get 带路径压缩。
初始化每个点独立。
从编号 n 向 1 逆序遍历节点 i：
若 rt[i] != i，说明这个点已经被某个前面的点覆盖/吸收，跳过。
否则：需要新选一个点 ans++，选的正是这个节点 i。
然后用并查集把 i 所在连通块「向上合并并标记已覆盖」：把 rt[u] 一路改为父节点 fa[u]，不断向上爬，直到 get(u) 到达的深度 < dep[to[i]]（即超出 i 的合法覆盖范围）为止。
内层 rt[u] = fa[u] + get 的作用：把整段 [i ... 到 i 的合法上限)  的祖先链合并进并查集，标记为已覆盖，后续点若落在其中则被跳过（rt[u]!=u）。
效果：每个点 i 选一次作为代表，并把它"能合法覆盖到的最上范围"全部合并，避免重复选择。逆序（从深处到根）保证每个"最深的尚未被覆盖"的节点一定会被选，从而点数最少。这正是贪心：优先切顶部/深点，用并查集标记已覆盖区间
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr int N = 1e5+5;

int st[N], top, to[N], dep[N], L, head[N], nxt[N];
ll sp[N], pre[N], S;
void dfs(int u) {
    st[++top] = u, sp[top] = pre[u];
    to[u] = lower_bound(sp,sp+top+1,pre[u]-S) - sp + 1;
    to[u] = st[max(dep[u]-L+1, to[u])];
    for (int i = head[u]; i; i = nxt[i]) dfs(i);
    top--;
}

int rt[N];
inline int get(int x) {
    while (x != rt[x]) x = rt[x] = rt[rt[x]];
    return x;
}

int n, val[N], fa[N], ans;
int main() {
    fast;
    cin >> n >> L >> S, dep[1] = 1;
    rep(i,1,n) {
        cin >> val[i];
        if (val[i] > S) return cout << "-1\n", 0;
    }
    rep(i,2,n) cin >> fa[i], dep[i] = dep[fa[i]] + 1;
    rep(i,1,n) pre[i] = pre[fa[i]] + val[i];
    rep(i,2,n) nxt[i] = head[fa[i]], head[fa[i]] = i;
    dfs(1);
    rep(i,1,n) rt[i] = i;
    for (int i = n, u; i >= 1; i--) {
        if (rt[u=i] != i) continue;
        for (ans++, rt[u]=fa[u]; ; rt[u] = fa[u])
            if (dep[u=get(u)] < dep[to[i]]) break;
    }
    cout << ans;
    return 0;
}