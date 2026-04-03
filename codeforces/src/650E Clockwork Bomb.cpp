//
// Created by Psy.C on 2026/4/2.
//
/**
node: 存储结果的四元组结构
edge: 链式前向星边结构
tot: 边计数器
head[N]: 邻接表头指针
add: 添加边到邻接表

f[N]: 第一棵树的父节点数组
构建以节点x为根的第一棵树
v[N]: 第二棵树的邻接表
g[N]: 第二棵树的父节点数组
构建以节点x为根的第二棵树
递归处理第一棵树
如果y和x在第二棵树中不相邻，则记录差异
find(y): 找到y所属的连通分量代表元
记录四元组：{x, y, 连通分量代表元, 代表元在第二棵树中的父亲}

读入节点数n
读入第一棵树的n-1条边，构建无向图
读入第二棵树的n-1条边，构建邻接表
以节点1为根构建两棵树
初始化并查集，根节点的父节点为自己
构建并查集
如果x和y在两棵树中都是相邻的，将它们合并到同一集合
否则各自成为独立集合

时间复杂度：O(n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e5+5;

struct node { int a, b, c, d; };
struct edge { int to, nxt; } a[N<<1];

int tot, head[N];
void add(int x, int y) {
    a[++tot] = {y, head[x]}, head[x] = tot;
}
int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int f[N];
void dfs(int x) {
    for (int i = head[x]; i; i = a[i].nxt) {
        int y = a[i].to;
        if (y == f[x]) continue;
        f[y] = x; dfs(y);
    }
}

vector<int> v[N];
int g[N];
void dfs2(int x) {
    for (int i = 0; i < v[x].size(); ++i) {
        int y = v[x][i];
        if (y == g[x]) continue;
        g[y] = x; dfs2(y);
    }
}

vector<node> ans;
void dfs3(int x) {
    for (int i = head[x]; i; i = a[i].nxt) {
        int y = a[i].to;
        if (y == f[x]) continue;
        dfs3(y);
        if (g[y] != x && g[x] != y)
            ans.push_back({x, y, find(y), g[find(y)]});
    }
}

int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        add(x, y); add(y, x);
    }
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
    }
    dfs(1); dfs2(1); fa[1] = 1;
    for (int x = 2; x <= n; ++x) {
        int y = g[x];
        if (f[x] == y || f[y] == x) fa[x] = y;
        else fa[x] = x;
    }
    dfs3(1);
    cout << ans.size() << '\n';
    for (auto &[a, b, c, d] : ans)
        cout << a << ' ' << b << ' ' << c << ' ' << d << '\n';
    return 0;
}