//
// Created by Psy.C on 2026/10/21.
//
/**
无向边结构体（2N 条边）。
head 为邻接链表头，add 向 u 的链头插入一条边
node 存子节点编号 idx、以及它的两个状态值 c0、c1。
cmp 排序规则：c1 大的排前面；若 c1 相同，c0 小的排前面（即先按 c1 降序、再按 c0 升序
vc[u]：u 的每个儿子对应的 node（在 dfs 中填充）。
deg[u]：u 的儿子数。
tdx[u]：排序后"可强制交换"的子节点分界下标。
f[u][0], f[u][1]：u 在两种"父边处理状态"下的可行性（
递归遍历非父节点 v；每遇到一个儿子 deg[u]++。
递归处理儿子后，若该儿子 f[v][0] 和 f[v][1] 都为 0（即两条路径都不可行），则整棵树无解，置 flg=false 并退出循环。
否则把儿子 v 及其两个状态值 push 进 vc[u]
注意这里 deg 是数组名，作布尔判断：deg[u]==0（叶子节点，无儿子）。
叶子节点：f[u][0]=1（可行），f[u][1]=0（不可行）
使用 <ranges> 按 cmp 对 u 的儿子排序（c1 降序、c0 升序）
找到最靠后的满足 c1==1 && c0==0 的连续区段的末尾下标 tdx[u]。
因为排序后 c1=1 的在前且 c0 升序，所以"c1==1 && c0==0"的节点连成一段前缀（可能连续）。循环从头扫描，只要是这种节点就更新 tdx[u]=i；遇到第一个不是的（c1!=1 或 c0!=0）就 break。
结果：tdx[u] 是这段"c1=1 且 c0=0"连续前缀的最后下标，-1 表示没有
检查 tdx[u]+1（紧接段后的那个）是否恰好也是 c1==1 && c0==0。
由于上面循环遇到非该型就 break，正常情况下 tdx[u]+1 已不是该型；此句作用：若因某种排序边界使得下一项仍满足，则设 tag=true。注意：这与上面循环逻辑略冲突（正常应 break 掉），属于保守校验；更可能 cmp 之后 c1=0 的部分在前缀，tag 通常为 false
cnt1 = deg[u]-(tdx[u]+1) 表示有多少个子节点不在那段"c1=1,c0=0"前缀里（即位于前缀之后的子节点数）。
若 cnt1 为偶数：f[u][0]=1；若还 tag，则 f[u][1]=1。
若 cnt1 为奇数：f[u][1]=1；若还 tag，则 f[u][0]=1。
返回 flg（是否子树可行）
先把 tdx[u] 之前（即那段 c1=1,c0=0 前缀）的儿子以状态 1 递归。
依据当前节点状态 st（0/1）和 cnt1 奇偶，决定是否"先插入中间一个儿子"（状态 1）再输出 u：
st==0 且 cnt1 为奇数时，插入一个儿子（状态1）后再 push u。
st==1 且 cnt1 为偶数（!=1）时，插入一个儿子后再 push u。
把 u 本身 push 进 res（后序/中间插入）。
剩余儿子（前缀之后）以状态 0 递归
读 n；对每个 i 读一个数 u，若 u!=0 则在 u 与 i 之间连一条无向边（表示 u 是 i 的父/祖先关系，构建一棵以 1 为根的树）。
dfs(1,0) 判可行性。
若 ans==0 或根节点 f[1][0]==0（根的状态 0 不可行）则输出 NO。
否则输出 YES，执行 dfs2(1,0)，按构造顺序输出所有顶点编号（每行一个）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5;

struct edge { int v, nxt; } e[N<<1];

int cnt, head[N];
void add(int u, int v) { e[++cnt].v = v; e[cnt].nxt = head[u]; head[u] = cnt; }

struct node { int idx; bool c0, c1; };
bool cmp(const node &a, const node &b) {
    if (a.c1 != b.c1) return a.c1 > b.c1;
    return a.c0 < b.c0;
}

vector<node> vc[N];
int deg[N], tdx[N];
bool f[N][2];
bool dfs(int u, int fa) {
    bool flg = true;
    for (int i = head[u]; i != 0; i = e[i].nxt) {
        int v = e[i].v;
        if (v != fa) {
            deg[u]++;
            dfs(v, u);
            if (f[v][0] == 0 && f[v][1] == 0) { flg = false; break; }
            vc[u].push_back({v, f[v][0], f[v][1]});
        }
    }
    if (deg[u] == 0) { f[u][1] = 0; f[u][0] = 1; }
    ranges::sort(vc[u], cmp);
    tdx[u] = -1;
    for (int i = 0; i < vc[u].size(); i++) {
        if (vc[u][i].c1 == 1 && vc[u][i].c0 == 0) tdx[u] = i;
        else break;
    }
    bool tag = false;
    if (tdx[u]+1 < vc[u].size() && vc[u][tdx[u]+1].c1 == 1 && vc[u][tdx[u]+1].c0 == 0) tag = true;
    if ((deg[u]-(tdx[u]+1))%2 == 0) {
        f[u][0] = 1;
        if (tag) f[u][1] = 1;
    } else {
        f[u][1] = 1;
        if (tag) f[u][0] = 1;
    }
    return flg;
}

vector<int> res;
void dfs2(int u, int st) {
    int i = 0;
    for (; i <= tdx[u]; i++) dfs2(vc[u][i].idx, 1);
    if (st == 0) {
        if ((deg[u]-(tdx[u]+1))%2 != 0) { dfs2(vc[u][i].idx, 1); i++; }
    } else {
        if ((deg[u]-(tdx[u]+1))%2 != 1) { dfs2(vc[u][i].idx,1); i++; }
    }
    res.push_back(u);
    for (; i < vc[u].size(); i++) dfs2(vc[u][i].idx, 0);
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, u; i <= n; i++) {
        cin >> u;
        if (u != 0) add(u, i), add(i, u);
    }
    bool ans = dfs(1, 0);
    if (ans == 0 || f[1][0] == 0) { cout << "NO\n"; return 0; }
    cout << "YES\n"; dfs2(1, 0);
    for (int re : res) cout << re << '\n';
    return 0;
}