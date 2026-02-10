//
// Created by Psy.C on 2026/2/10.
//
/**
ans：存储所需操作总数
s：起始节点（第一个值为1的节点）
n：图中的节点数量
m：图中的边数
v[N]：访问数组，跟踪已处理的节点
c[N]：存储每个节点当前状态的数组（0或1）
g[N]：图的邻接表表示

r[N<<2]：记录操作序列的数组（N<<2表示N*4）
set函数使用异或运算(c[u] ^= 1)翻转节点u的值
通过将节点添加到结果数组并递增操作计数来记录操作

首先对当前节点u执行设置操作并将其标记为已访问
对于u的每个未访问邻居，递归处理它
从递归调用返回后，对u执行另一个设置操作
如果子节点在处理后仍然为1，则执行额外操作来清除它
 */
#include <iostream>
#include <vector>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int ans, s, n, m, v[N], c[N];
vector<int> g[N];
void init() {
    ans = s = 0;
    cin >> n >> m;
    memset(v, 0, sizeof(v));
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
        if (c[i]) s = i;//将第一个值为1的节点识别为起点
    }
}

int r[N<<2];
inline void set(const int u) {
    c[u] ^= 1;
    r[ans++] = u;
}

void dfs(const int u) {
    set(u); v[u] = 1;
    for (int i = 0; i < g[u].size(); ++i) {
        if (v[g[u][i]]) continue;
        dfs(g[u][i]);
        set(u);
        if (c[g[u][i]]) {
            set(g[u][i]);
            set(u);
        }
    }
}

bool ok() {//是否所有节点都已成功翻转为0
    for (int i = 1; i <= n; ++i) if (c[i]) return false;
    return true;
}

int main() {
    fast;
    init(); dfs(s);
    if (c[s]) { c[s] = 0; ans--; }//处理起始节点可能仍为1的特殊情况
    if (ok()) {//所有节点都已成功清零（全部变为0），则输出操作数和序列
        cout << ans << '\n';
        if (ans) {
            cout << r[0];
            for (int i = 1; i < ans; ++i) cout << ' ' << r[i];
            cout << '\n';
        }
    } else cout << "-1\n";
    return 0;
}