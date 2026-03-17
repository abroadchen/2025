//
// Created by Psy.C on 2026/3/16.
//
/**
f[u][i][0/1] 表示以u为根的子树中，恰好有i个叶子节点被匹配，且节点u是否参与匹配的最小代价

u不参与匹配，所以u的贡献是 f[u][j][0]
v的子树可以选择：
v也不参与匹配：代价 f[v][k][0]
v参与匹配（但不是与u）：代价 f[v][k][1] + 1
取两者中的较小值
总共有j+k个叶子节点被匹配

u参与匹配，所以u的贡献是 f[u][j][1]
v的子树可以选择：
v不参与匹配（但与u有连接）：代价 f[v][k][0] + 1
v参与匹配（在自己子树内部）：代价 f[v][k][1]
取两者中的较小值
总共有j+k个叶子节点被匹配

时间复杂度：O(n²)
空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define minn(a,b) ((a)=min((a),(b)))
using namespace std;
constexpr int N = 5005;
///n:节点数，deg[]:度数数组，rt:根节点
int n, deg[N], rt;
vector<int> *g;//邻接表
void init() {
    cin >> n;
    g = new vector<int>[n+1];//动态分配邻接表
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    //第一个度数>1的节点作为根
    for (rt = 1; rt < n && deg[rt] == 1; ++rt) {}
}

int f[N][N][2], flag[N], t[N][2];
void dfs(int u, int fa) {
    if (deg[u] == 1) {
        f[u][1][0] = f[u][0][1] = 0;//初始化叶子状态
        flag[u] = 1;//标记此节点为叶子
        return;
    }
    flag[u] = 0;//非叶子节点
    f[u][0][0] = f[u][0][1] = 0;//初始化
    for (int i = 0; i < deg[u]; ++i) {//遍历所有邻居
        int v = g[u][i];
        if (v == fa) continue;
        dfs(v, u);//递归处理子树
        memset(t, 0x3f, sizeof t);
        for (int j = flag[u]; ~j; --j)//遍历当前子树的匹配数
            for (int k = flag[v]; ~k; --k) {//遍历新子树的匹配数
                //合并状态：u不匹配，v可以匹配或不匹配
                minn(t[j+k][0], f[u][j][0] + min(f[v][k][0], f[v][k][1] + 1));
                //u匹配，v可以匹配或不匹配
                minn(t[j+k][1], f[u][j][1] + min(f[v][k][0] + 1, f[v][k][1]));
            }
        flag[u] += flag[v];//累计叶子节点数
        //更新当前节点的DP值
        for (int j = 0; j <= flag[u]; ++j)
            f[u][j][0] = t[j][0], f[u][j][1] = t[j][1];
    }
}

void out() {
    memset(f, 0x3f, sizeof f);
    dfs(rt, 0);
    int j = flag[rt] >> 1, ans = min(f[rt][j][0], f[rt][j][1]);
    cout << ans << '\n';
}

int main() {
    fast;
    init(); out();
    return 0;
}