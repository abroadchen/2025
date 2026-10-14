//
// Created by Psy.C on 2026/10/14.
//
/**
N = 3e5+5：最大节点数及边数上限。
n, m：节点数、边的数量。
x, y：读边用的临时变量（有向边 x→y）。
in[N]：每个节点的入度，用于拓扑排序。
f[N][30]：DP 表，f[i][j] 表示到达节点 i 的某条路径上，字符 j（0-25 对应 'a'-'z'）出现的最大次数。
ans：全局最大值（答案）。
cnt：拓扑排序处理过的节点数，用于检测是否有环。
s：节点上标定的字符串（每个节点一个字母）。
g[N]：邻接表（出边）。
q：拓扑排序用的队列
读入 n、m 和字符串 s。
循环 m 次读入边 x→y：g[x] 加入出边 y，同时 y 的入度 in[y]++。
s = ' ' + s：在 s 前拼接一个空格，使下标从 1 对齐节点编号 1..n
所有入度为 0 的节点（拓扑起点）入队 q。
并把自身的字母位置 f[i][s[i]-'a'] 初始化为 1（该路径上这个字母出现 1 次）
to = q.front(); q.pop();：取出队首节点 to（处理当前节点）。

遍历 to 的所有出边邻居 i（边 to→i）：

状态转移（对每个字母 j，0-25）
从 to 走到 i 时，如果节点 i 的字母恰好等于 j（s[i]-'a' == j），则这一段的 j 计数 +1，否则 +0。
与 i 之前已记录的 f[i][j] 取 max。
这条转移对所有 26 个字母都做一遍，因为要找的是"出现最多的那个字母"。
ans = max(ans, f[i][j])：更新全局最大值。

入度递减与拓扑推进
处理完边 to→i 后，节点 i 的入度减 1；若减到 0，说明 i 的所有前驱都已处理完，把 i 入队继续 DP
cnt++：统计已处理的节点数。
若 cnt < n，说明拓扑排序处理完的节点少于总数，即图中存在环（有向环上无法完成拓扑），输出 -1。
否则输出 ans，即路径上出现次数最多的字母的最大出现次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

ll n, m, x, y, in[N], f[N][30], ans, cnt;
string s;
vector<ll> g[N];
queue<ll> q;
int main() {
    fast;
    cin >> n >> m >> s;
    while (m--) { cin >> x >> y; g[x].emplace_back(y); in[y]++; }
    s = ' ' + s;
    for (int i = 1; i <= n; ++i)
        if (!in[i]) { q.push(i); f[i][s[i]-'a'] = 1; }
    while (!q.empty()) {
        ll to = q.front(); q.pop();
        for (auto i : g[to]) {
            for (int j = 0; j < 26; ++j) {
                f[i][j] = max(f[i][j], f[to][j]+1ll*(s[i] - 'a' == j));
                ans = max(ans, f[i][j]);
            }
            if (!--in[i]) q.push(i);
        }
        cnt++;
    }
    cout << (cnt < n ? -1 : ans);
    return 0;
}