//
// Created by Psy.C on 2026/9/26.
//
/**
node：邻接表边，to = 另一端点，i = 这条边在原始输入中的编号（边的 ID）。
e[x]：顶点 x 的所有邻边
fa[x]：顶点 x 的父节点（在 DFS 树中）。
fe[x]：连接 x 与其父节点的那条边的编号。
d[x]：顶点 x 的目标奇偶性（0/1），或 -1（不限/任意）。
ans[top]：收集选中边的编号，top 是数量
第一段：递归遍历子树

对每个邻居 to，如果它既不是父节点、且还没被访问过（!fa[to]），就设它为子节点（fa[to]=x），记录边编号 fe[to]，递归 dfs(to)。
这是构建 DFS 树的过程。
第二段：后序处理奇偶性（关键）‍

当 x 自己的子树都处理完后，检查 d[x]：
若 d[x] == 1（x 还需要"奇数次覆盖"）：把连接 x 与其父节点的边 fe[x] 选入答案（ans[++top]），并把奇偶性"上传"给父节点：d[fa[x]] ^= 1（异或翻转父的目标奇偶性）。
if (d[fa[x]] != -1)：父节点不是"不限"时才翻转。
这是树上自底向上的贪心：

每个节点的目标奇偶性 d[x] 若为 1，就必须通过与其父相连的那条边来补足奇偶（因为子树的边只能影响子树内，连接父的边是"把奇偶性需求向上传递"的唯一通道）。
选这条关键边后，将奇偶性需求取反传给父节点（因为选这条边会同时改变父、子的覆盖奇偶）。
若 d[x] = -1（不限），则不求、不传递。

n 个点，m 条边。
读入每个点的目标奇偶性 d[i]：
u：统计 d[i] == 1 的个数（有明确"奇"需求的点数）。
bf：是否存在 d[i] == -1（"不限"的点）的标记。
st：记录第一个 d[i] == -1 的点作为 DFS 的根（若有则 st=它，否则保持 st=1）
若奇偶需求为 1 的点总数 u 是奇数，且没有"不限"（-1）的点 → 无解，输出 -1。
原因：树边每次会被两点共享（选一条边翻转两点奇偶），总翻转为偶数次；奇偶需求为 1 的点数必须是偶数才可能满足。只有存在 "不限" 的点时才能打破奇偶守恒（那个点可吸收多余的一次），否则为奇数即无解。
建图并 DFS

读入 m 条无向边，加入邻接表，并记录边编号。
以 st 为根（fa[st]=st，自环根）执行 dfs(st)
输出 top（选中的边数）。
对边编号排序后逐行输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10;

struct node { int to, i; };
vector<node> e[N];

int fa[N], fe[N], d[N], ans[N], top;
void dfs(int x) {
    for (int i = 0; i < e[x].size(); ++i) {
        int to = e[x][i].to;
        if (to != fa[x] && !fa[to]) {
            fa[to] = x; fe[to] = e[x][i].i;
            dfs(to);
        }
    }
    if (d[x] == 1) {
        ans[++top] = fe[x];
        if (d[fa[x]] != -1) d[fa[x]] ^= d[x];
    }
}

int n, m, u, st(1), bf;
int main() {
    fast;
    cin>>n>>m;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
        if (d[i] == 1) u++;
        if (d[i] == -1) st = i, bf = 1;
    }
    if (u%2 == 1 && !bf) { cout << -1; return 0; }
    for (int i = 1, x, y; i <= m; ++i) {
        cin >> x >> y;
        e[x].push_back({.to = y, .i = i});
        e[y].push_back({.to = x, .i = i});
    }
    fa[st] = st; dfs(st);
    cout << top << '\n';
    sort(ans+1, ans+1+top);
    for (int i = 1; i <= top; ++i) cout << ans[i] << '\n';
    return 0;
}