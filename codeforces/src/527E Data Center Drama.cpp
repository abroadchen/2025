//
// Created by Psy.C on 2026/3/3.
//
/**
边的起点from、终点to和同起点的下一条边的索引nxt
cnt: 当前边的数量计数器
head[N]: 链式前向星表示法的头指针数组

遍历当前节点u的所有邻接边
~i检查是否还有未访问的边（i != -1）
vis[i/2]标记边对（因为添加的是双向边，所以用i/2）
递归访问下一个节点，并将边的索引加入结果

查找所有奇度数节点并进行配对
deg[i]&1检查度数是否为奇数
如果p == -1，记录第一个奇度数节点
如果找到了第二个奇度数节点，就连接它们并重置p
如果实际边数为奇数，添加自环来调整
cnt/2是因为每条边添加了两次（双向）

时间复杂度为O(n+m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 500100;///图的最大边数

struct node { int from, to, nxt; } e[N];

int cnt, head[N];
void add(const int u, const int v) {
    e[cnt] = {u, v, head[u]}, head[u] = cnt++;
}

int vis[N];
vector<int> ans;
void dfs(const int u) {
    for (int& i = head[u]; ~i; i = e[i].nxt) {
        if (vis[i/2]) continue;
        vis[i/2] = 1;
        const int v = e[i].to;
        int t = i; dfs(v);
        ans.push_back(t);
    }
}

int n, m, deg[N];
void init() {
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(deg, 0, sizeof(deg));
    memset(vis, 0, sizeof(vis));
}

int main() {
    fast;
    cin >> n >> m; init();
    while (m--) {
        int u, v; cin >> u >> v;
        add(u, v); add(v, u);
        deg[u]++; deg[v]++;
    }
    int p = -1;
    for (int i = 1; i <= n; ++i) {
        if (deg[i]&1) {
            if (p == -1) p = i;
            else {
                add(i, p); add(p, i);
                deg[i]++, deg[p]++;
                p = -1;
            }
        }
    }
    if ((cnt/2)&1) add(n, n);
    ans.clear(); dfs(1);
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); ++i) {
        if (i&1) cout << e[ans[i]].from << ' ' << e[ans[i]].to << '\n';
        else cout << e[ans[i]].to << ' ' << e[ans[i]].from << '\n';
    }
    return 0;
}