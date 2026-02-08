//
// Created by Psy.C on 2026/2/8.
//
/**
sz[N]: 每个节点的子树大小
fa[N]: 每个节点的父边编号
g[N]: 邻接表表示的树
dp[u][j]: 在以u为根的子树中选择j个节点的最小代价
v[u][j]: 记录达到dp[u][j]状态的选择方案

根节点的父节点编号为 0
f = 0，条件 if(f) 为假
普通节点的父节点编号是真实节点编号（>0）
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 510
#define inf 2e9
#define ii pair<int, int>
using namespace std;

int sz[N], fa[N];
vector<ii> g[N];
void dfs(const int u, const int f) {//计算子树大小
    sz[u] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        const int to = g[u][i].first;//相邻节点
        if (to == f) continue;
        dfs(to, u);//递归处理子节点
        fa[to] = g[u][i].second;//到达子节点的边编号
        sz[u] += sz[to];//累加子树大小
    }
}

int dp[N][N];
vector<ii> v[N][N];
void dfs2(int u, const int f, int idx) {//树形DP
    for (int i = 0; i < g[u].size(); ++i) {
        int to = g[u][i].first;
        if (to == f) continue;
        dfs2(to, u, g[u][i].second);
        //背包DP：合并当前节点和子节点的结果
        for (int j = sz[u]; j >= 0; --j)//j: 当前考虑在u子树中选择的节点总数
            //不能超过子树大小和剩余容量
            for (int k = 0; k <= min(sz[to], j); ++k)//k: 考虑在to子树中选择的节点数量
                //选择k个节点在子树to中 + 选择j-k个节点在其他子树中 < 当前方案
                if (dp[u][j-k] + dp[to][k] < dp[u][j]) {
                    dp[u][j] = dp[u][j-k] + dp[to][k];
                    v[u][j] = v[u][j-k];//复制之前的选择方案
                    v[u][j].emplace_back(to, k);//添加新的选择：子树to中选k个
                }
    }
    if (f) {//不是根节点
        dp[u][sz[u]] = 1;//选择整个子树的代价为1
        v[u][sz[u]].clear();//"切断"与父节点的连接
        v[u][sz[u]].emplace_back(u, sz[u]);
    }
    else dp[u][sz[u]] = 0;//根节点选择整个子树代价为0
}

int vis[N];
void dfs3(const int u, const int x) {
    vis[u] = 1;
    if (sz[u] == x) {//当前子树大小等于目标大小
        cout << fa[u] << ' ';//输出到达此节点的边
        return;
    }
    //递归处理选择的子节点
    for (auto &[fst, snd] : v[u][x]) dfs3(fst, snd);
}


int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1, a, b; i < n; ++i) {
        cin >> a >> b;
        g[a].emplace_back(b, i);//添加边，记录边编号
        g[b].emplace_back(a, i);
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) dp[i][j] = inf;
    dfs(1, 0); dfs2(1, 0, 0);
    //从根节点保留n-k个节点的代价
    int ans = dp[1][n-k], j = 1;
    for (int i = 2; i <= n; ++i)//每个节点作为"切断点"，计算最小代价
        ///否则无法从中删除k个节点 1: 切断节点i与其父节点的连接（代价为1）
        ///以i为根的子树中保留sz[i]-k个节点的最小代价
        if (sz[i] >= k && 1 + dp[i][sz[i]-k] < ans) {
            ans = min(ans, 1 + dp[i][sz[i]-k]);
            j = i;
        }
    cout << ans << '\n';
    if (j != 1) cout << fa[j] << ' ';//不是根节点，输出边
    dfs3(j, sz[j] - k);//输出选择的节点路径
    return 0;
}