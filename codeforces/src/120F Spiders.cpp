//
// Created by Psy.C on 2025/11/16.
//
/*
*N = 105：最大节点数
dis：记录最大距离
pos：记录最远节点位置
g[N]：邻接表表示的图（树）
 *
*DFS函数计算从节点x出发的最远距离：
x：当前节点
fa：父节点（避免回溯）
sum：当前距离
如果当前距离更大，更新最大距离dis和最远节点pos
递归访问所有子节点
 *
 *初始化函数：重置距离、位置和邻接表
*n：树的个数
ans：所有树直径的总和
*对每棵树：
初始化状态
m：该树的节点数
读取m-1条边构建树（树有n个节点n-1条边）
*两次DFS计算树的直径：
第一次DFS：从节点1开始，找到距离最远的节点pos
重置距离dis = 0
第二次DFS：从最远节点pos开始，找到真正的最远距离（即树的直径）
累加到总答案ans
 *
*每棵树：O(m)（两次DFS）
总计：O(∑m) = O(节点总数)
 */
#include <vector>
#include <iostream>
using namespace std;

const int N = 105;
int dis, pos;
vector<int> g[N];

void dfs(int x, int fa, int sum) {
    if (sum >= dis) { dis = sum; pos = x; }
    for (auto i : g[x]) {
        if (i == fa) continue;
        dfs(i, x, sum + 1);
    }
}
void init() {
    dis = pos = 0;
    for (int i = 0; i < N; ++i) g[i].clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, ans(0); cin >> n;
    for (int i = 1, m; i <= n; ++i) {
        init(); cin >> m;
        for (int j = 1, u, v; j < m; ++j) {
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, -1, 0);
        dis = 0;
        dfs(pos, -1, 0);
        ans += dis;
    }
    cout << ans << '\n';
    return 0;
}