//
// Created by Psy.C on 2026/10/7.
//
/**
g：原图，g.add(u,v) 存边 u→v（正边）。
t：反向图，t.add(v,u) 存边 v→u（即把 u→v 反过来存进 t 的 u 位置，用于"入/出"计算）
out[i]：节点出度（在 tp1 中作为"反向图处理时的剩余入度"使用）。
val[i]：题目给定的某些固定值/强制值（0 表示无强制）。
mn[i]：节点可取值的下界。
q：队列
读入 n 节点、m 边、k（取值上限），val[i] 为强制值，然后分别维护正图 g 和反图 t，以及出度 out[u]、入度 in[v]
先跑两个拓扑函数判断合法性；再检查每个节点下界确实 ≤ 上界；任一不满足输出 -1
所有出度为 0 的节点入队，mn[i] 初始为 val[i]（若强制）否则为 1。
沿反向图 t 传播：对每条反向边 v=to，令 mn[v] = max(mn[v], mn[u]+1)——即后继的下界要比后继的下界至少大 1（因为 u 是 v 的后继）。u+1 中的 u 是当前节点、其后继 mn[u] 已知。
等等，这里方向要仔细：t 存的是反向边，head[u] 遍历的是"u 的前驱"（在原图中）。所以 v 是原图中 u 的前驱（即 v→u 是原图边）。那么 mn[v] = max(mn[v], mn[u]+1) 就是"前驱的下界 ≥ 后继的下界+1"，这符合拓扑约束（v 早于 u，值 v < 值 u，故 mn[v] ≥ mn[u]+1... 若要求严格递增则 +1）。
当某前驱 v 的"剩余出度"清零时出队判断：若强制值 val[v] 小于下界则非法返回 1；否则 mn[v]=max(mn[v],val[v])（强制值必须 ≥ 下界）并入队。
最后若还有 out[i] 不为 0（环），返回 1 表示有环。
所以 mn 是每个节点强制后得到的最低下界
所有入度为 0 的节点：mx[i] 取强制值否则取 k，入队；其余节点 mx[i]=k。
沿正图 g 传播：mx[v] = min(mx[v], mx[u]-1)——后继的上界 ≤ 前驱上界 -1（严格递增约束）。
清零时判断强制值 val[v] 是否 > 上界（非法返回 1），否则把强制值也纳入上界约束。
若剩 in[i] 非 0（环）返回 1。
所以 mx 是每个节点在强制约束下得到的最高上界
把所有节点按 (mn, mx) 排序（下界升序、同下界按上界升序）。
对每个取值 i（从 1 到 k）：
用"扫描线"思路：把所有 mn <= i 的节点插入有序集合 st（按键为 mx），保证下界满足。
从 st 中取 mx 最小（begin）‍ 的节点，赋予值 i，并删除。因为 hv 标记，每轮最多分配给… 实际上内层 while 里每个满足 mx[x] <= i（且 hv 为 0 或 mx<=i 时）的节点都能被分配。
等等，看仔细：内层 while 不断取 begin，若 hv && mx[x] > i 就 break（第一次分配后 hv=1，后面的节点若上界 >i 就无法再分配，停）；每次取出一个节点 ans[x]=i 并从集合删除，hv=1。所以这一轮 i 会把所有 mx<=i 的待分配节点都分配出去（因为它们排序最小、上界又 <= i）。
若这一轮一个也没分配（!hv），即没有任何可用节点，返回 -1（无解）。
最终输出每个节点的分配值 ans[i]。
而为什么要这样分配是正确的：

一个节点只能被赋 mx 以内的值（因为它在集合中且 mx<=当前 i 才会被取出），同时 i>=mn 保证不跌破下界。
每次取 mx 最小的（最早"死线"的），是经典的"按截止时间（上限）排序分配"的贪心，能保证尽量多的节点被成功赋值。
这样分配能保证每个取到的节点 mn<=i<=mx，且由于拓扑约束（mx 从上界递减、mn 从下界递增），最终得到的赋值是严格递增且合法的。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 2e5+5;

struct node {
    int head[N], nxt[N], to[N], tot;
    void add(int u, int v) {
        to[++tot] = v; nxt[tot] = head[u]; head[u] = tot;
    }
} g, t;

int l, r, n, out[N], val[N], mn[N], q[N];
inline int tp1() {
    l = 0, r = -1;
    for (int i = 1; i <= n; ++i)
        if (!out[i])
            mn[i] = val[i] ? val[i] : 1, q[++r] = i;
    int u, i, v;
    while (l <= r) {
        u = q[l++];
        for (i = t.head[u]; i; i = t.nxt[i]) {
            v = t.to[i];
            mn[v] = max(mn[v], mn[u]+1);
            if (!--out[v]) {
                if (val[v] && val[v] < mn[v]) return 1;
                mn[v] = max(mn[v], val[v]);
                q[++r] = v;
            }
        }
    }
    for (i = 1; i <= n; ++i)
        if (out[i]) return 1;//还有未访问 → 有环
    return 0;
}

int in[N], mx[N], k;
inline int tp2() {
    l = 0, r = -1;
    for (int i = 1; i <= n; ++i) {
        if (!in[i]) mx[i] = val[i] ? val[i] : k, q[++r] = i;
        else mx[i] = k;
    }
    int u, i, v;
    while (l <= r) {
        u = q[l++];
        for (i = g.head[u]; i; i = g.nxt[i]) {
            v = g.to[i];
            mx[v] = min(mx[v], mx[u]-1);
            if (!--in[v]) {
                if (val[v] && val[v] > mx[v]) return 1;
                if (val[v]) mx[v] = min(mx[v], val[v]);
                q[++r] = v;
            }
        }
    }
    for (i = 1; i <= n; ++i)
        if (in[i]) return 1;//有环
    return 0;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int m, id[N], ans[N];
set<ii> st;
int main() {
    fast;
    n = rd(); m = rd(); k = rd();
    for (int i = 1; i <= n; ++i) val[i] = rd();
    for (int i = 1, u, v; i <= m; ++i) {
        u = rd(), v = rd();
        in[v]++, out[u]++; g.add(u, v); t.add(v, u);
    }
    if (tp1() || tp2()) return cout << "-1\n", 0;
    for (int i = 1; i <= n; ++i)
        if (mn[i] > mx[i]) return cout << "-1\n", 0;
    for (int i = 1; i <= n; ++i) id[i] = i;
    sort(id+1, id+1+n, [](int a, int b) {
        return mn[a] == mn[b] ? mx[a] < mx[b] : mn[a] < mn[b];
    });
    for (int i = 1, now = 1; i <= k; ++i) {
        while (now <= n && mn[id[now]] <= i)
            st.insert({mx[id[now]], id[now]}), now++;
        int hv = 0;
        while (!st.empty()) {
            int x = st.begin()->second;
            if (hv && mx[x] > i) break;
            ans[x] = i; hv = 1;
            st.erase(st.begin());
        }
        if (!hv) return cout << "-1\n", 0;
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}