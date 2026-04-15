//
// Created by Psy.C on 2026/4/15.
//
/**
N<<1：边数组大小扩大一倍（因为是无向图，每条边添加两次）
siz[i]：以节点i为根的子树大小
fa[i]：节点i的父节点
mx[i]：节点i的所有子树中最大的子树大小
初始化：如果已计算过就返回，否则初始化siz[x]=1
第一轮遍历：递归计算子树大小
第二轮遍历：更新mx[x]为所有子树中的最大值
vis数组：存储每个节点的重心编号
核心逻辑：遍历子节点，找到具有最大子树的子节点
重心转移：根据重心定义，逐步向上寻找最优重心

构建树：从节点2开始，读取每个节点的父节点并建立双向边
标记内部节点：flag数组标记哪些节点不是叶子节点
初始化叶子节点：叶子节点的重心就是自己
两次DFS预处理：计算所有节点的子树信息和重心
处理查询：对每个查询，直接输出对应的重心节点编号
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

int ver[N<<1], nxt[N<<1], head[N], tot;
void add(int x, int y) {
    ver[++tot] = y;
    nxt[tot] = head[x], head[x] = tot;
}

int siz[N], fa[N], mx[N];
void dfs(int x) {
    if (siz[x]) return; siz[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (fa[x] == y) continue;
        dfs(y);
        siz[x] += siz[y];
    }
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (fa[x] == y) continue;
        mx[x] = max(mx[x], siz[y]);
    }
}

int vis[N];
void dfs2(int x) {
    if (vis[x]) return;
    for (int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if (fa[x] == y) continue;
        dfs2(y);
        if (siz[y] != mx[x]) continue;
        int cnt = vis[y];
        while (cnt) {
            int s = max(mx[cnt], siz[x]-siz[cnt]),
            t = max(mx[vis[x]], siz[x]-siz[vis[x]]);
            if (s < t || !vis[x])
                vis[x] = cnt, cnt = fa[cnt];
            else break;
        }
    }
}

int n, q;
bool flag[N];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 2, x; i <= n; ++i) {
        cin >> x;
        add(x, i); add(i, x);
        fa[i] = x; flag[x] = 1;
    }
    for (int i = 1; i <= n; ++i)
        if (!flag[i]) vis[i] = i;
    dfs(1); dfs2(1);
    for (int i = 1, rt; i <= q; ++i) {
        cin >> rt;
        cout << vis[rt] << '\n';
    }
    return 0;
}