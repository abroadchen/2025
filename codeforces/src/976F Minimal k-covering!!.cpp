//
// Created by Psy.C on 2026/10/22.
//
/**
n：总点数（含源点 0 和汇点 n）。
v[N]：DFS 访问标记（用 cnt 时间戳避免清零）。
f[N][N]：残量网络（当前边的剩余容量）‍。
g[N]：邻接表
从源点 0 走增广路到汇点 n。
if (f[x][y]==0 || v[y]==cnt) continue;：跳过无容量或本轮已访问的边。
找到时沿路更新残量：前进方向 f[x][y]--、反向 f[y][x]++（标准增广路更新）
num[N]：左侧每个点对应的原始边编号列表。
ans[N]：每个度数下界 l 的答案（边编号集合）。
t[N][N]：临时残留表。
读入 n1、n2、k，总点数 n = n1+n2+1（注意：这里把汇点编号定为 n，源点应为... 见下文）。
边 (x, y)：y 偏移到右侧 y += n1。
双向加邻接，num[x] 记录边编号。
f[x][y]++：正向容量 1。
d[x]++、d[y]++：度数。
注意：源点用的是 0，汇点用 n；右侧点的编号是 n1+1 .. n-1（也就是说 n 是汇点，左侧 1..n1，右侧 n1+1..n-1）
m 取所有非源点（1..n-1，即左侧+右侧）度数的最小值。d[i] 是每个点在原始图中的度数
源点 0 连所有左侧点 i，容量 f[0][i] = d[i] - m。
所有右侧点连汇点 n，容量 f[i][n] = d[i] - m。
含义：每个点除了最小度数 m 之外的"多余度数" d[i]-m 通过源/汇路径承载，这样能控制的流量与"度数上限"相关
外层 loop l 从 m 递减到 0：每个 l 对应一个"度数下界"的答案阶段。
cnt++; while (dfs(0)) cnt++;：反复找增广路直到无法增广（跑满当前网络的最大流）。用 cnt 时间戳给每轮做 DFS 标记。
这里 dfs(0) 增广时同时会 cnt++？不，cnt++ 在 while 循环体里，每次 dfs 前自增，dfs(0) 返回 true 表示找到一条增广路并更新了残量，继续；返回 false 表示再无增广路，退出 while。
快照到 t：把左侧点所有出边的残量复制到 t[i][y]（保留当前最大流状态）。
构造本层答案：遍历左侧点 i 的所有出边 y：
若 y && t[i][y]（y 非 0、且有剩余容量），则这条边当前在匹配/解中：t[i][y]-- 占掉，ans[l].push_back(num[i][j]) 把这个边编号加入第 l 层答案。
扩大源/汇容量：f[0][i]++（源到左侧 +1）、f[i][n]++（右侧到汇 +1）——每次把下界 l 降低 1，等价于放宽限制、允许容纳更多边，进入下一轮
对每个 l（0..m）输出一行：先是该层边数（集合大小），再跟随所有边编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; i++)
using namespace std;
constexpr int N = 4e3+10;

int n, v[N], cnt, f[N][N];
vector<int> g[N];
bool dfs(int x) {
    if (x == n) return true;
    v[x] = cnt;
    rep(i,g[x].size()) {
        int y = g[x][i];
        if (f[x][y] == 0 || v[y] == cnt) continue;
        if (dfs(y)) {
            f[x][y]--; f[y][x]++;
            return true;
        }
    }
    return false;
}

vector<int> num[N], ans[N];
int d[N], m, t[N][N];
int main() {
    fast;
    int n1, n2, k, x, y;
    cin >> n1 >> n2 >> k; n = n1+n2+1;
    for (int i = 1; i <= k; i++) {
        cin >> x >> y; y += n1;
        g[x].push_back(y); g[y].push_back(x); num[x].push_back(i);
        f[x][y]++; d[x]++, d[y]++;
    }
    m = k*2;
    for (int i = 1; i < n; i++) m = min(m, d[i]);
    for (int i = 1; i <= n1; i++) {
        g[0].push_back(i); g[i].push_back(0);
        f[0][i] = d[i] - m;
    }
    for (int i = n1+1; i < n; i++) {
        g[i].push_back(n); g[n].push_back(i);
        f[i][n] = d[i] - m;
    }
    for (int l = m; l >= 0; l--) {
        cnt++;
        while (dfs(0)) cnt++;
        for (int i = 1; i <= n1; i++) {
            rep(j,g[i].size()) {
                y = g[i][j]; t[i][y] = f[i][y];
            }
        }
        for (int i = 1; i <= n1; i++) {
            rep(j,g[i].size()) {
                y = g[i][j];
                if (y && t[i][y]) {
                    t[i][y]--;
                    ans[l].push_back(num[i][j]);
                }
            }
        }
        for (int i = 1; i <= n1; i++) f[0][i]++;
        for (int i = n1+1; i < n; i++) f[i][n]++;
    }
    rep(i,m+1) {
        cout << ans[i].size();
        for (auto &an : ans[i]) cout << ' ' << an;
        cout << '\n';
    }
    return 0;
}