//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
v[N]：树的邻接表。
len[u]：从 u 出发向下（子树内）能延伸的"最长合法路径长度"。
f[u]：子树 u 内被"切断/需要额外路径"的计数累积。
k：每条路径允许的最大长度
树上的贪心合并：

对每个叶子（无儿子），直接返回，len[u] 不设（为 0），因为它没有方向。
对单儿子节点：len[u] = len[son]+1，路径直接往上走，不需要处理配对。
对多儿子节点 u：
把所有儿子的 len+1 收集进 l 并排序。
目标：尽量多地把"短的"两两配对，使配对的长度和 ≤ k（这样两条短路径可以在 u 处接成一条合法路径，省一条路径）。
排序后，从最短的开始贪心：l[p]+l[p+1] ≤ k 则配一对（p 后移）。
剩下的唯一一条最长者（len[u]=l[p]）继续向上延伸；其余未配对的都要在 u 处断掉（f[u] += l.size()-1-p 计入计数）。
逻辑：把儿子们延伸上来的路径，能两两配成 ≤k 的就配对（在 u 相接），最长的那个保留继续向上，剩下的断掉——这是经典树路径覆盖的贪心
读入 n、k 和 n-1 条边，建树（无向边，d 记录度）。
找一个非叶子节点（度 > 1）作根 rt（避开只有一边的歧义）。
dfs(rt, 0) 递归。
输出 f[rt] + 1：根处剩余的路径 + 最后一条作为"终点"（因为从根出发最终还有一条向上延伸路径没被断掉，所以 +1）。

状态：len[u] = 从 u 向下能延伸的最长合法长度；f[u] = 子树内被"截断"的路径数。
贪心：对多儿子节点，把儿子上来的长度排序，尽量把短的配对（配对长度和 ≤ k），最长的那条继续向上延伸，剩下的截断计入。
答案 = 根处的 f[rt]+1（剩余延伸路径算一条）。
trick（if (p == l.size()-2 && ...) p++ 那行）：当所有儿子都能两两配对且还剩最后两条也合法时，p 需要再多处理一次——这个分支是在处理"排序后恰好剩最后两个也能配对"的特殊情形，本质是把 l.size()-1（最后两个）纳入配对
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
using namespace std;

constexpr int N = 1e6+10;

vector<int> v[N];
int len[N], f[N], k;
void dfs(int u, int fa) {
    vi l;
    for (int j : v[u]) {
        if (j == fa) continue;
        dfs(j, u);
        l.push_back(len[j]+1);
        f[u] += f[j];
    }
    if (l.empty()) return;
    if (l.size() == 1) { len[u] = l[0]; return; }
    ranges::sort(l);
    int p = 0;
    for (; p < l.size()-1; p++)
        if (l[p] + l[p+1] > k) break;
    if (p == l.size()-2 && l[p] + l[p+1] <= k) p++;
    len[u] = l[p];
    f[u] += l.size() - 1 - p;
}

int n, d[N];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        v[x].push_back(y); v[y].push_back(x);
        d[x]++, d[y]++;
    }
    int rt;
    for (rt = 1; rt <= n; rt++) if (d[rt] > 1) break;
    dfs(rt, 0);
    cout << f[rt]+1 << '\n';
    return 0;
}