//
// Created by Psy.C on 2026/1/20.
//
/**
 * N=1010（节点数），M=3030（边数
*L[N][M], R[N][M]：边的左右边界约束
vx[N], vy[N]：访问状态记录
 *
*now：当前节点
l, r：当前区间
if (now == n)：到达目标节点n，更新答案
从后往前遍历邻居（优化）
nl = max(l, L[now][i]), nr = min(r, R[now][i])：更新区间边界
if (nl <= nr && ...)：检查约束条件
递归搜索
回溯：vis[g[now][i]] = false
 *
 *最坏情况：O(路径数 × 每条路径长度)
 *
*g[a].size()：节点a的邻接点数量
g[a].size()-1：最新的那个邻接点的索引

vx[g[now][i]]：访问节点 g[now][i] 时的最小值
vy[g[now][i]]：访问节点 g[now][i] 时的最大值
这个条件判断：是否值得继续探索
// vx[g[now][i]] < nl：之前记录的最小值 < 当前最小值
// vy[g[now][i]] > nr：之前记录的最大值 > 当前最大值
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
#define M 3030
#define inf 1e6
using namespace std;

int n, ans, L[N][M], R[N][M], vx[N], vy[N];
vector<int> g[N];
bool vis[N];
void dfs(const int now, const int l, const int r) {
    if (now == n) {
        ans = max(ans, r - l + 1);
        return;
    }
    for (int i = static_cast<int>(g[now].size())-1; i >= 0; --i) {
        if (!vis[g[now][i]]) {
            const int nl = max(l, L[now][i]), nr = min(r, R[now][i]);
            vis[g[now][i]] = true;//邻居节点
            if (nl <= nr && nr - nl + 1 > ans &&
                (vx[g[now][i]] > nl || vy[g[now][i]] < nr)) {//>最大 <最小
                //记录到达节点 g[now][i] 时的区间状态 [nl, nr] 避免重复访问相同状态 记忆化剪枝
                vx[g[now][i]] = nl, vy[g[now][i]] = nr;
                dfs(g[now][i], nl, nr);
            }
            vis[g[now][i]] = false;
        }
    }
}

int main() {
    fast;
    int m; cin >> n >> m;
    for (int i = 1, a, b, l, r; i <= m; ++i) {
        cin >> a >> b >> l >> r;
        if (a == b) continue;
        g[a].push_back(b); g[b].push_back(a);
        R[a][g[a].size()-1] = r;//为边(a,b)存储右边界
        R[b][g[b].size()-1] = r;//为边(b,a)存储右边界
        L[a][g[a].size()-1] = l;
        L[b][g[b].size()-1] = l;
    }
    ans = 0; vis[1] = true; vx[1] = 1, vy[1] = inf;
    dfs(1, 1, inf);
    if (ans == 0) cout << "Nice work, Dima!\n"; else cout << ans << '\n';
    return 0;
}