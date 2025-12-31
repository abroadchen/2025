//
// Created by Psy.C on 2025/12/31.
//
/**
 * 更新变量为较小值，如果更新成功返回true，否则返回false
*in[N]：节点u的进入时间戳
idx：当前时间戳
who[N]：时间戳对应节点   通过时间戳反查节点编号
sz[N]：以节点u为根的子树大小  （包含u自身）
fa[N]：节点u的父节点
wfa[N]：节点u到父节点的边权
fsz[N]：节点u的上方子树大小（整棵树减去u的子树）
n：节点总数
ot[N]：节点u的离开时间戳
g[N]：邻接表存储图
ret：全局结果变量
 *
*时间戳记录：记录进入和离开节点u的时间
子树大小计算：遍历子节点，累加子树大小
父节点和边权设置：记录父节点和到父节点的边权
上方子树大小：fsz[u] = n - sz[u]表示u上方的节点数
初始答案计算：累加每条边对答案的贡献sz[u] * fsz[u] * wfa[u]
离开时间记录：记录离开节点的时间戳
 *
*答案更新：用当前值更新结果
边权重新计算：移除原来边的贡献，加上重计算后的边贡献
递归处理：对子节点继续DFS
csz参数：表示当前考虑的割掉子树的大小
 *
*初始化：重置dp数组和is标记
包含关系判断：检查节点u是否包含节点b（在DFS序中）
子树处理：递归处理子节点，更新dp值
状态转移：根据is[u]的值更新dp[u][0]和dp[u][1]
边权调整：根据是否在路径中调整边权对答案的贡献
 *
*重计算影响：通过dfs2计算移除节点x对答案的影响
DP更新：通过dfs3更新DP状态
返回结果：返回移除节点x后答案的变化量
 *
*输入处理：读取节点数和边信息，构建邻接表
初始DFS：从节点1开始DFS，计算初始答案
枚举删除：尝试删除每个节点，找到最小答案
输出结果：输出最优答案
 *
 *sz[i.second] + csz 合并后的新子树大小
 *csz 代表由于删除操作而与当前子树合并的额外节点数量
 *fsz[i.second] - csz 剩余的上方连通分量大小
 *csz 是从上方部分转移到子树部分的节点数量
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 5007
using namespace std;

template<class T, class U>
bool minn(T& a, U b) { return a > b ? a = b, true : false; }

int in[N], idx, who[N], sz[N], fa[N], wfa[N], fsz[N], n, ot[N];
vector<pair<int, int>> g[N];
ll ret;
void dfs(const int u) {
    in[u] = ++idx;//节点u的进入时间戳
    who[idx] = u;//时间戳idx对应的节点是u
    sz[u] = 1;//节点u本身
    for (const auto& i : g[u]) {
        if (i.second == fa[u]) continue;//邻接点是u的父节点
        fa[i.second] = u;//设置邻接点的父节点为当前节点u
        wfa[i.second] = i.first;//设置邻接点到其父节点的边权为当前边的权重
        dfs(i.second);//对邻接点递归调用
        sz[u] += sz[i.second];//累加子节点的子树大小到当前节点的子树大小
    }
    fsz[u] = n - sz[u];
    ret += 1ll * sz[u] * fsz[u] * wfa[u];//计算边u-fa[u]对答案的贡献：子树内节点数×子树外节点数×边权
    ot[u] = idx;
}
//当前节点u，当前值t，结果引用res，当前割掉的子树大小csz
void dfs2(const int u, const ll t, ll& res, const int csz) {
    minn(res, t);//用当前值t更新结果res（保留较小值）
    for (const auto& i : g[u]) {
        if (i.second == fa[u]) continue;
        ll x = t;//复制当前值到变量x
        x -= 1ll * i.first * sz[i.second] * fsz[i.second];
        x += 1ll * i.first * (sz[i.second] + csz) * (fsz[i.second] - csz);
        dfs2(i.second, x, res, csz);//传入更新后的x值
    }
}

ll dp[N][2];//dp[u][0]和dp[u][1]代表不同状态
bool is[N];//节点是否在特定路径上
//当前节点u，目标节点b，当前割掉的子树大小csz
void dfs3(const int u, const int b, const int csz) {
    dp[u][0] = dp[u][1] = is[u] = false;
    if (in[u] <= in[b] && ot[b] <= ot[u]) is[u] = true;//节点u包含节点b（在DFS序中b在u的子树内）
    ll mx = 0;
    for (const auto& i : g[u]) {
        if (i.second == fa[u] || i.second == b) continue;//是父节点或目标节点b
        dfs3(i.second, b, csz);
        minn(dp[u][0], dp[i.second][0]);//所有子节点dp值的最小值
        if (is[u]) {//当前节点在路径上
            if (is[i.second]) dp[u][1] = dp[i.second][1];//子节点也在路径上，直接传递dp值
            else minn(mx, dp[i.second][1]);//更新mx为子节点dp值的最小值
        } else { minn(dp[u][1], dp[i.second][1]); }//当前节点不在路径上，更新dp[u][1]
    }
    if (is[u]) {
        minn(dp[u][0], dp[u][1] + mx);
        dp[u][1] -= 1ll * wfa[u] * sz[u] * fsz[u];
        dp[u][1] += 1ll * wfa[u] * (sz[u] - csz) * (fsz[u] + csz);
    } else {
        dp[u][1] -= 1ll * wfa[u] * sz[u] * fsz[u];
        dp[u][1] += 1ll * wfa[u] * (sz[u] + csz) * (fsz[u] - csz);
        minn(dp[u][1], 0);//保证dp[u][1]不小于0
    }
}

ll solve(const int x) {//计算移除节点x的影响
    ll res = 0;
    dfs2(x, 0, res, fsz[x]);
    dfs3(1, x, sz[x]);
    res += dp[1][0];//将根节点的dp值加到结果中
    return res;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1, a, b, w; i < n; ++i) {
        cin >> a >> b >> w;
        g[a].emplace_back(w, b);
        g[b].emplace_back(w, a);
    }
    dfs(1);
    ll ans = ret;
    for (int i = 2; i <= n; ++i) { minn(ans, ret + solve(i)); }
    cout << ans << '\n';
    return 0;
}