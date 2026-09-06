//
// Created by Psy.C on 2026/9/6.
//
/**
DFS(1) → 找到离节点 1 最远的点
l
l。
DFS(l) → 计算
d
l
dl 数组，并找到离
l
l 最远的点
r
r（即直径另一端）。
DFS(r) → 计算
d
r
dr 数组。

确定中心候选点 (
r
t
rt)
条件 dl[i] + dr[i] == dl[r] 确保
i
i 在直径路径上。
取 min(dl[i], dr[i]) 最大的点，即直径的中点（如果长度为偶数，则唯一；奇数时取两个中点之一
子树收集：遍历所有子节点，将其返回值加入向量
v
v。
去重排序：确保
v
v 中仅保留不同的返回值。
非根节点规则：一个节点只能有一种类型的子树（除叶子外）。否则立即判定为不合法。
根节点规则：根节点（或递归入口）可以接受至多两种不同的子树类型（对应左右子树）。
返回值意义：返回当前子树的“层高”或“特征值”。具体来说：
叶子返回 1。
单一路径返回子树值 + 1。
合并两个子树返回两者之和
调用 solve 得到根节点的总层高或特征值
a
n
s
ans。
循环右移（除以 2）直到
a
n
s
ans 为奇数。这里的逻辑是：如果答案是偶数，那么它一定可以被二分成更小的合法结构（因为树的对称性），所以我们一直除以 2，直到得到最小的奇数基准
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;

struct edge { int to, nxt; } e[N<<1];

int cnt, head[N];
inline void add(int x, int y) {
    e[++cnt].to = y; e[cnt].nxt = head[x]; head[x] = cnt;
}
inline void adde(int x, int y) { add(x, y); add(y, x); }

inline void dfs(int x, int fa, int dep, int *d) {
    d[x] = dep;
    for (int i = head[x]; i; i = e[i].nxt)
        if (e[i].to^fa)
            dfs(e[i].to, x, dep+1, d);
}

inline int solve(int x, int fa) {
    vector<int> v;
    //收集所有子树返回值
    for (int i = head[x]; i; i = e[i].nxt)
        if (e[i].to^fa)
            v.push_back(solve(e[i].to, x));
    ranges::sort(v);
    v.resize(ranges::unique(v).begin() - v.begin());
    if (x^fa) {
        if (v.size() > 1) puts("-1"), exit(0);//子树返回值不一致
        if (v.empty()) return 1;//叶子节点
        return v[0] + 1;//单一路径延伸
    }
    //根节点约束（允许最多两个不同的子树）
    if (v.size() > 2) return -1;
    return v[0] + v[v.size()-1];
}

int d[N], l, dl[N], r, dr[N], rt, ans;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v; adde(u, v);
    }
    dfs(1, 0, 0, d);
    for (int i = 1; i <= n; ++i)
        if (d[i] > d[l]) l = i;
    dfs(l, 0, 0, dl);
    for (int i = 1; i <= n; ++i)
        if (dl[i] > dl[r]) r = i;
    dfs(r, 0, 0, dr);
    rt = l;
    for (int i = 1; i <= n; ++i)
        if (dl[i] + dr[i] == dl[r] && min(dl[i], dr[i]) > min(dl[rt], dr[rt]))
            rt = i;
    ans = solve(rt, rt);
    while (ans && !(ans&1)) ans >>= 1;
    cout << ans << '\n';
    return 0;
}