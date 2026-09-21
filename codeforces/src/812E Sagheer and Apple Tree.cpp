//
// Created by Psy.C on 2026/9/21.
//
/**
从根 1（深度 1）做 DFS，记录每个节点深度 dep[u]，同时找出最大深度 mx
读 n。
读 n 个节点的值 val[i]，用 map mp 统计每种值出现次数。
读 n-1 条边，建无向树（节点是 1..n
DFS 后，mx 是树的最大深度。
遍历所有节点 i：
若 mx % 2 == dep[i] % 2（即奇偶性相同，这类节点我称它"类 A"），那么：
mp[val[i]]--：从 map 里减掉一个该值（保留另一半节点的计数）。
ans ^= val[i]：异或累计这些"类 A"节点的值。
这样处理后：

类 A（mx%2==dep%2）节点：只参与异或 ans，在 mp 中被移除。
类 B（奇偶性不同者）：仍保留在 mp 中，不参与 ans

情况 1：ans == 0

所有"类 A"节点异或为 0。

对每个类 A 节点 i，cnt += mp[val[i]]（在类 B 中找与它值相同的配对，C(n,2) 风格）。
sum = 类 B 节点个数，n-sum = 类 A 节点个数。
再加
s
u
m
(
s
u
m
−
1
)
2
+
(
n
−
s
u
m
)
(
n
−
s
u
m
−
1
)
2
2
sum(sum−1)
​
 +
2
(n−sum)(n−sum−1)
​
 ：类内两两配对的组合数（同色节点内任选两个组成一对）。
逻辑：当 ans==0 时，配对可以发生在同类节点之间（同色），所以加上"类A内任取两个 + 类B内任取两个"的组合数，再补充跨类中值相同的配对。
情况 2：ans != 0

对每个类 A 节点 i，cnt += mp[ans ^ val[i]]：在类 B 中找值等于 ans ^ val[i] 的节点与之配对。
即寻找满足 val[u] ^ val[v] == ans 的跨类点对数量。因为所有类 A 的异或和是 ans，为达全局平衡，需要类 B 中异或值为 ans^val[i] 的与之组合
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

vector<int> vc[N];//邻接表存树
int dep[N], mx;//深度、最大深度
void dfs(int u, int pre, int d) {
    int len = vc[u].size(); dep[u] = d; mx = max(mx, d);
    for (int i = 0; i < len; ++i) {
        int v = vc[u][i];
        if (v == pre) continue;
        dfs(v, u, d+1);
    }
}

map<int, int> mp;//值 -> 计数
int val[N], ans;//节点值、异或累计
int main() {
    fast;
    int n; cin >> n; mp.clear();
    for (int i = 0; i <= n; ++i) vc[i].clear();
    for (int i = 1, x; i <= n; ++i) { cin >> x; val[i] = x; mp[x]++; }
    for (int i = 1, x; i < n; ++i) { cin >> x; vc[x].push_back(i+1); vc[i+1].push_back(x); }
    mx = 0; dfs(1, -1, 1);
    for (int i = 1; i <= n; ++i)
        if (mx%2 == dep[i]%2) mp[val[i]]--, ans ^= val[i];
    ll cnt = 0;
    if (ans == 0) {
        ll sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (mx%2 == dep[i]%2) cnt += mp[val[i]];
            else sum++;
        }
        cnt += (sum*(sum-1)/2+(n-sum)*(n-sum-1)/2);
    } else {
        for (int i = 1; i <= n; ++i)
            if (mx%2 == dep[i]%2) cnt += mp[ans^val[i]];
    }
    cout << cnt << '\n';
    return 0;
}