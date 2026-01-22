//
// Created by Psy.C on 2026/1/22.
//
/**
* f[N][20]: 倍增祖先数组，f[u][i]表示节点u的2^i代祖先
id[N]: DFS序对应的节点ID
cnt[N]: 节点的DFS序编号
tot: DFS序计数器
dep[N]: 节点深度
 */
#include <iostream>
#include <vector>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
using namespace std;

int f[N][20], id[N], cnt[N], tot, dep[N];
vector<int> g[N];
void dfs(const int u, const int fa) {
    f[u][0] = fa;
    id[cnt[u]=++tot] = u;
    for (int i = 0, v; i < g[u].size(); ++i) {
        v = g[u][i];//v是节点u的第i个邻居
        if (v != fa) dep[v] = dep[u] + 1, dfs(v, u);
    }
}

int lca(int u, int v) {//最近公共祖先
    if (dep[u] > dep[v]) swap(u, v);//确保v更深
    const int k = dep[v] - dep[u];
    int i;
    //将v向上跳k步，k&(1<<i)检查k的第i位是否为1，如果是就跳2^i步
    for (i = 0; i < 20; ++i) if (k&(1<<i)) v = f[v][i];
    if (v == u) return u;//u是v的祖先
    //同时向上跳：从高位到低位，如果u和v的第i个祖先都存在且不相同 同时向上跳2^i步
    for (i = 19; i >= 0; --i) if (f[u][i] && f[v][i] && f[u][i] != f[v][i]) {
        u = f[u][i]; v = f[v][i];
    }
    return f[u][0];//返回u的父亲节点
}

int sum;//当前操作的总和值
set<int> s;
//op=1为添加，op=0为删除，u是要操作的节点
void modify(const int op, const int u) {
    auto it = s.lower_bound(cnt[u]);//it指向第一个>=cnt[u]的元素位置
    if (*it == cnt[u]) {//找到了相同的DFS序
        s.erase(cnt[u]);
        it = s.lower_bound(cnt[u]);//it重新指向第一个>=cnt[u]的位置
    }
    if (s.empty()) {
        if (op == 1) s.insert(cnt[u]);
        return;
    }
    int pre, nxt;//pre前驱节点，nxt后继节点
    if (it == s.begin()) pre = id[*(--s.end())];//如果it在开头，pre是最后一个元素对应的节点
    else pre = id[*(--it)], ++it;//否则pre是it前一个元素对应的节点
    if (it == s.end()) nxt = id[*s.begin()];//如果it在结尾，nxt是第一个元素对应的节点
    else nxt = id[*it];//否则nxt是it位置对应的节点
    //当前节点对结果的贡献
    const int t = dep[u] - dep[lca(pre, u)] - dep[lca(nxt, u)] + dep[lca(pre, nxt)];
    if (op == 1) sum += t, s.insert(cnt[u]);
    else sum -= t;
}

int n, k;//节点总数 限制条件值
int ok(const int m) {//长度为m的区间是否满足条件
    sum = 0; s.clear();
    int i;
    for (i = 1; i <= m - 1; ++i) modify(1, i);//添加前m-1个节点
    for (i = m; i <= n; ++i) {//从第m个节点开始滑动
        modify(1, i);//将第i个节点添加
        if (sum + 1 <= k) return 1;
        modify(0, i + 1 - m);//删除窗口左边的节点
    }
    return 0;
}


int main() {
    fast;
    cin >> n >> k;
    int i, j;
    for (i = 1; i <= n - 1; ++i) {
        int u, v; cin >> u >> v;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(1, 0);//0作为虚拟根节点
    for (i = 1; i < 20; ++i) for (j = 1; j <= n; ++j) {
        //j的第2^i个祖先 = j的第2^(i-1)个祖先的第2^(i-1)个祖先
        f[j][i] = f[f[j][i-1]][i-1];
    }
    int l = 1, r = n, ans = 0;
    while (l <= r) {
        if (const int m = (l + r) >> 1; ok(m)) ans = m, l = m + 1;
        else r = m - 1;
    }
    cout << ans;
    return 0;
}