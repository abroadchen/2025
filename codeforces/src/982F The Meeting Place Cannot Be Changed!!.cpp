//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
M 是边数上限（5e5），e[] 存每条边（起点 a、终点 b），head[] 为邻接表头，nxt[] 链式前向星。
add(a,b)：头插法加入有向边 a→b
c[i]：访问状态。0=未访问，-1=正在访问栈中，1=访问完成。用于找环。
tot：环长计数。ck[i]：已被删除（选中）的点，跳过。
p[]：存环上节点。pre[i]：DFS 树上的父节点。
if (tot || ck[x]) return;：已经找到环，或该点已被删除，直接返回。
c[x] = -1;：标记 x 进入当前 DFS 栈（正在处理）。
遍历 x 的每条出边 x→e[a].b：
if (ck[...]) continue; 终点被删则跳过。
if (c[终点]==-1)：发现回边（终点还在栈中），说明遇到环 → 沿着 pre 回溯收集环上节点：while (x != e[a].b) p[++tot]=x, x=pre[x]; 把从当前点沿父链回溯到终点之前的节点都入环；最后 p[++tot]=e[a].b 把终点（即环的起点）也加入。然后 return 结束。
if (!c[终点]) pre[终点]=x, dfs(终点);：否则若终点未访问，记录父节点为 x，递归。
遍历完后 c[x]=1;：标记 x 处理完成（回溯出栈）。
o=最后选中的删除点，res=覆盖总数，tot 清零。
从每个未访问点 dfs，找到第一个环即停。若整张图无环（tot==0）→ 返回 0（表示已经无环，不需要删点）
翻转环的存储顺序。
tag[p[i]]=1：环上点打标记。
pos[p[i]]=i：记录每个环上点的位置 (1..tot)
dfs2 从每个环上点出发，向"环外的子树"遍历，统计覆盖
从环上起点 s 出发，x 为当前遍历点。flg 防重复访问。
遍历出边 x→e[a].b：
跳过已被删点 ck。
若终点 e[a].b 正是环上点（tag==1）：
若 x 也是环上点且终点也是环上点，说明是环内相邻边，跳过。
若 pos[s] >= pos[终点] 则跳过（避免重复/反向区间）。
否则这是一条"环上点 s 所在连通块 → 环上某点 y"的路径，形成一条对环的"额外覆盖弧"。res++ 记录总覆盖数；用差分数组 sum 标记：覆盖环上区间 [1, pos[s]] 和 [pos[y], tot]（即：删掉 s 或删掉 y 都能破坏这条弧）。
若终点不是环上点且未访问，递归 dfs2(s, 终点) 继续在环外子树里搜
与 dfs2 对称，但条件是 pos[s] < pos[终点] 时跳过，且覆盖区间用 [pos[y], pos[s]]（反向弧）。
用于处理另一方向的覆盖
对差分数组做前缀和，sum[i] = 位置 i（环上第 i 个点）被覆盖的次数。
若某个环位置的覆盖数 sum[i] == res（等于总覆盖弧数），说明所有"额外弧"都经过该点 → 删除该点能破坏所有弧 → 该点就是候选删除点 o。
ck[o]=1 记录已选；返回 o
读入 n,m 和所有有向边。
第一次 solve()：尝试找候选删除点 ans。
若 ans==0（图本身无环，无需删点）→ 输出 -1。
否则，第二次 solve()：此时 ck[ans]=1 已删除该点，再找一次环。
若第二次 solve() 返回 0（删后无环了）→ 输出 ans（成功）。
若第二次还能找到环（返回非 0）→ 说明删 ans 后仍有环 → 输出 -1（失败）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5, M = 5e5+5;
struct node { int a, b; } e[M];

int k, head[N], nxt[M];
void add(int a, int b) {
    e[++k] = {a, b}; nxt[k] = head[a]; head[a] = k;
}

int c[N], tot, ck[N], p[N], pre[N];
void dfs(int x) {
    if (tot || ck[x]) return; c[x] = -1;
    for (int a = head[x]; a&&!tot; a = nxt[a]) {
        if (ck[e[a].b]) continue;
        if (c[e[a].b] == -1) {
            while (x != e[a].b) p[++tot] = x, x = pre[x];
            p[++tot] = e[a].b;
            return;
        }
        if (!c[e[a].b]) pre[e[a].b] = x, dfs(e[a].b);
    }
    c[x] = 1;
}

int flg[N], tag[N], pos[N], res, sum[N];
void dfs2(int s, int x) {
    if (ck[x]) return; flg[x] = 1;
    for (int a = head[x]; a; a = nxt[a]) {
        if (ck[e[a].b]) continue;
        if (tag[e[a].b]) {
            if (tag[x] && tag[e[a].b]) continue;
            if (pos[s] >= pos[e[a].b]) continue;
            int y = e[a].b; res++;
            sum[1]++; sum[pos[s]+1]--;
            sum[pos[y]]++; sum[tot+1]--;
        }
        else if (!flg[e[a].b]) dfs2(s, e[a].b);
    }
}
void dfs3(int s, int x) {
    if (ck[x]) return; flg[x] = 1;
    for (int a = head[x]; a; a = nxt[a]) {
        if (ck[e[a].b]) continue;
        if (tag[e[a].b]) {
            if (tag[x] && tag[e[a].b]) continue;
            if (pos[s] < pos[e[a].b]) continue;
            int y = e[a].b; res++;
            sum[pos[y]]++; sum[pos[s]+1]--;
        }
        else if (!flg[e[a].b]) dfs3(s, e[a].b);
    }
}

int n;
int solve() {
    int o = 0; res = 0; tot = 0; memset(c, 0, sizeof(c));
    for (int i = 1; i <= n && !tot; i++) if (!c[i]) dfs(i);
    if (!tot) return 0;
    reverse(p+1, p+tot+1);
    memset(tag, 0, sizeof(tag));
    memset(pos, 0, sizeof(pos));
    memset(sum, 0, sizeof(sum));
    for (int i = 1; i <= tot; i++) tag[p[i]] = 1, pos[p[i]] = i;
    memset(flg, 0, sizeof(flg));
    for (int i = 1; i <= tot; i++) dfs2(p[i], p[i]);
    memset(flg, 0, sizeof(flg));
    for (int i = tot; i; i--) dfs3(p[i], p[i]);
    for (int i = 1; i <= tot; i++) {
        sum[i] += sum[i-1];
        if (sum[i] == res) { o = p[i]; break; }
    }
    ck[o] = 1;
    return o;
}

int m, ans;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, a, b; i <= m; i++) {
        cin >> a >> b; add(a, b);
    }
    ans = solve();
    if (!ans) { cout << "-1\n"; return 0; }
    if (!solve()) cout << ans << '\n'; else cout << "-1\n";
    return 0;
}