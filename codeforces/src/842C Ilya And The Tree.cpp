//
// Created by Psy.C on 2026/9/27.
//
/**
mp[j] 表示"当前 DFS 路径上，已遍历节点中权值含因数 j 的节点个数"（维护的是根到当前节点路径上所有已处理节点的因数出现次数，作用是全局计数器，DFS 进入时 ++、回溯时 --，从而始终反映"当前路径"上的统计）。

对节点 u：

g[u] = gcd(g[fa], k)：前缀 gcd，即根→u 路径所有节点权值的 gcd（包含 u）。

res[u] 初始 = g[fa]（根→u 的父亲，即不含 u 的路径 gcd 上界）。

然后枚举 k（u 自己的权值）的所有因数 j，mp[j]++。

判定：若 mp[j] >= dep-1，表示"根到 u 的父亲这一段路径上所有节点（共 dep-1 个）的权值都含有因数 j"，那么去掉 u 之后的那段路径（不含 u）的 GCD 至少是 j，用 max 更新 res[u]。

dep 是当前深度（根 dep=1，调用时 dfs(1,2) 表示根的子节点 dep=2）。dep-1 = 根→u 路径上除 u 外的节点数。
判断 mp[j] >= dep-1：因为 mp[j] 统计的是根→u（含 u 处理完后）的节点中因数出现次数，若去掉 u 后仍全部含 j（即根→fa[u] 全部含 j），则数量恰好 ≥ dep-1。
处理完 u 后递归进入子节点（dfs(u, dep+1)）。

回溯时把 u 的因数计数减掉（mp[j]--），恢复现场，使 mp[] 只反映当前根路径——这就是树上"路径统计"的标准回溯技巧。

根节点 1：res[1] = num[1]（根无父，答案就是自身的权值），g[1] = num[1]。
先把根的因数加入 mp。
从 dfs(1, 2) 开始（dep=2，即根的子节点）。
最后输出每个节点的 res[i]

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

vector<int> e[N];
int num[N], g[N], res[N], mp[N];
bool vis[N];
void dfs(int fa, int dep) {
    int l = e[fa].size();
    for (int i = 0, u, k; i < l; ++i) {
        u = e[fa][i]; k = num[u];
        if (!vis[u]) {
            vis[u] = true;
            g[u] = gcd(k, g[fa]);
            res[u] = g[fa];
            for (int j = 1; j*j <= k; ++j) {
                if (k%j == 0) {
                    mp[j]++;
                    if (mp[j] >= dep-1)
                        res[u] = max(res[u], j);
                    if (j*j != k) {
                        int t = k/j; mp[t]++;
                        if (mp[t] >= dep-1)
                            res[u] = max(res[u], t);
                    }
                }
            }
            dfs(u, dep+1);
            for (int j = 1; j*j <= k; ++j)
                if (k%j == 0) {
                    mp[j]--;
                    if (j*j != k) mp[k/j]--;
                }
        }
    }
}

int n;
int main() {
    fast;
    cin >> n;
    memset(vis, 0, sizeof vis);
    for (int i = 1; i <= n; ++i) cin >> num[i];
    for (int i = 0, a, b; i < n-1; ++i) {
        cin >> a >> b;
        e[a].push_back(b); e[b].push_back(a);
    }
    vis[1] = 1; res[1] = num[1]; g[1] = num[1];
    memset(mp, 0, sizeof mp);
    for (int j = 1; j*j <= num[1]; ++j)
        if (num[1]%j == 0) {
            mp[j]++;
            if (j*j != num[1]) mp[num[1]/j]++;
        }
    dfs(1, 2);
    cout << res[1];
    for (int i = 2; i <= n; ++i) cout << ' ' << res[i];
    cout << '\n';
    return 0;
}