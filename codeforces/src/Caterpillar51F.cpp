//
// Created by Psy.C on 2025/10/15.
//
/*
*n, m: 节点数和边数
dfn[N], low[N]: Tarjan算法中的时间戳和最低可达时间戳
clk: 时间戳计数器
s[N], top: 栈和栈顶指针，用于Tarjan算法
bcc: 双连通分量计数器
id[N]: 每个节点所属的双连通分量编号
cnt[N]: 每个双连通分量的度数（连接的其他分量数）
D, tag: 用于计算树直径的辅助变量
dep[N]: 节点深度
ans: 最终答案
vis[N]: 访问标记数组
G[N]: 原图的邻接表
g[N]: 缩点后的图（树）的邻接表
K: 临时存储节点的向量
 *
*Tarjan算法实现，用于寻找双连通分量：
为节点u设置时间戳和最低可达时间戳
将节点u压入栈中
遍历u的所有邻居v：
如果v未访问过，递归调用tarjan
否则如果v不是父节点，更新low值
如果low[u]等于dfn[u]，说明找到一个双连通分量
弹出栈中元素，将它们标记为同一个双连通分量

 *
*DFS函数，用于计算树的直径：
设置节点u的深度
标记u为已访问并加入临时列表K
更新最大深度D和最深节点tag
递归访问所有未访问的邻居节点
 *
*解决函数，计算每个连通分量的贡献：
执行两次DFS来找到树的直径
第一次DFS找到最远点sx
第二次DFS从sx开始找到最远点sy，得到直径D
根据直径计算贡献值
清理访问标记和临时列表
 *
*对每个未访问的节点执行Tarjan算法
k记录连通分量的数量
 *
*构建缩点后的图（将双连通分量缩为点）
如果两个节点属于不同双连通分量，则在它们之间连边
*计算度数小于等于1的双连通分量数量
对每个未访问的双连通分量执行solve函数
根据公式计算最终答案并输出
 *
 *
 *时间复杂度约为O(n+m)
 *
 */
#include <vector>
#include <ios>
#include <iostream>
#include <algorithm>
#define rep(i, n) for (int i = 1; i <= (n); ++i)
using namespace std;

const int N = 2e3+10;
int n, m, dfn[N], low[N], clk, s[N], top, bcc, id[N], cnt[N], D, tag, dep[N], ans;
bool vis[N];
vector<int> G[N], g[N], K;

void tarjan(int u, int p) {
    dfn[u] = low[u] = ++clk;
    s[++top] = u;
    for (int v : G[u]) {
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        } else if (v != p) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        bcc++;
        while (1) {
            int x = s[top--];
            id[x] = bcc;
            if (x == u) break;
        }
    }
}


void dfs(int u, int p) {
    dep[u] = dep[p] + 1; vis[u] = 1;
    K.push_back(u);
    if (D < dep[u]) D = dep[u], tag = u;
    for (int v : g[u]) {
        if (v == p || vis[v]) continue;
        dfs(v, u);
    }
}


void solve(int s) {
    int sx, sy, num(0); D = 0; tag = 0;
    dfs(s, 0);
    for (int u : K) {
        if (cnt[u] <= 1) num++;
        vis[u] = 0;
    }
    D = 0; sx = tag; tag = 0;
    dfs(sx, 0);
    sy = tag;
    ans += (-D + 2);
    if (D == 1) ans--;
    K.clear();
}

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> n >> m;
    int k(0);
    rep(i, m) {
        int u, v; cin >> u >> v;
        G[u].push_back(v); G[v].push_back(u);
    }
    rep(i, n) if (!dfn[i]) k++, tarjan(i, 0);
    rep(i, n) {
        for (int v : G[i]) {
            if (id[i] == id[v]) continue;
            g[id[i]].push_back(id[v]);
            cnt[id[v]]++;
        }
    }
    int num(0);
    rep(i, bcc) if (cnt[i] <= 1) num++;
    rep(i, bcc) if (!vis[i]) solve(i);
    ans += (n + k - num - 1);
    cout << ans;
    return 0;
}