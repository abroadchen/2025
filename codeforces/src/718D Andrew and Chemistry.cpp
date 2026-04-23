//
// Created by Psy.C on 2026/4/22.
//
/**
f[u][fa]：以u为根，fa为父节点的子树哈希值
h：将子树结构映射到唯一ID
tot：哈希值计数器

如果已经计算过以u为根的子树哈希值，直接返回
遍历所有邻居节点v
跳过父节点fa（防止往回走）
递归计算子树的哈希值并存入ve向量
对子树哈希值排序
保证相同结构的树有相同的哈希值（解决同构问题）
如果当前子树结构未出现过，分配新的ID
返回该子树的哈希值

遍历每个节点作为根
if (e[i].size() >= 4) continue;：跳过度数≥4的节点
以节点i为根计算树的哈希值
插入set中自动去重
O(n²logn)：每个节点可能作为根一次，每次DFS需要排序子树
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

vector<int> e[N];
void add(int u, int v) { e[u].push_back(v); }

map<int, int> f[N];
map<vector<int>, int> h;
int tot;
int dfs(int u, int fa) {
    vector<int> ve;
    if (f[u][fa]) return f[u][fa];
    for (int v : e[u]) {
        if (v == fa) continue;
        ve.push_back(dfs(v, u));
    }
    ranges::sort(ve);
    if (!h[ve]) h[ve] = ++tot;
    return f[u][fa] = h[ve];
}

int n;
set<int> s;
int main() {
    fast;
    rd(n);
    for (int i = 1, u, v; i < n; ++i)
        rd(u), rd(v), add(u, v), add(v, u);
    for (int i = 1; i <= n; ++i) {
        if (e[i].size() >= 4) continue;
        s.insert(dfs(i, 0));
    }
    cout << s.size() << '\n';
    return 0;
}