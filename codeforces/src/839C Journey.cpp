//
// Created by Psy.C on 2026/9/26.
//
/**
N = 1e5+5：最大节点数。
vector<int> q[N]：邻接表存树，q[x] 存与节点 x 相连的所有邻居。
double ans：累计的期望步数总和。
bool vis[N]：DFS 访问标记，防止走回头路（树无环但邻接表是无向的）
x：当前节点。
w：到达当前节点 x 的概率。
len：从根走到 x 经过的边数（步数）。
叶子判断：q[x].size() == 1 表示 x 只有一个邻居（是叶子），且 x != 1（排除根只有一条边时被当成叶子的情况）。

如果是叶子：累加 ans += w * len——即"以概率 w 走到这个叶子、走了 len 步"，期望贡献是 w * len。然后返回（不再下探）
遍历当前节点 x 的所有邻居 k。
如果 k 没被访问过，就进入：
标记 vis[k] = true。
计算走向 k 的概率，并用新的概率递归：
若 x 是根（x == 1）‍：根有 q[x].size() 个可选邻居，每个概率均分，所以 w * 1/q[x].size()。
若 x 不是根：x 已经有父节点（从父节点来的方向已经走过），所以可选的下一个方向数是 q[x].size() - 1（排除父节点），每个概率均分，w * 1/(q[x].size()-1)。
递归步数 len+1

读入 n（节点数）。
读入 n-1 条边（树有 n-1 条边），无向图存入邻接表 q
重置访问标记，根节点 1 标记为已访问。
从根 dfs(1, 概率=1, 步数=0) 开始遍历。
输出 ans，保留 15 位小数。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;

vector<int> q[N];
double ans;
bool vis[N];
void dfs(int x, double w, int len) {
    if (q[x].size() == 1 && x != 1) { ans += w*len; return; }
    for (int i = 0; i < q[x].size(); ++i) {
        int k = q[x][i];
        if (vis[k] == false) {
            vis[k] = true;
            if (x == 1) dfs(k, w*1/q[x].size(), len+1);
            else dfs(k, w*1/(q[x].size()-1), len+1);
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        q[x].push_back(y); q[y].push_back(x);
    }
    memset(vis, false, sizeof(vis)); vis[1] = true;
    dfs(1, 1, 0);
    printf("%.15lf", ans);
    return 0;
}