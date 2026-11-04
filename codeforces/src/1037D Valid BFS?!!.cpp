//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
idx[v] 记录每个节点在给定的目标序列 q 中的位置（用于排序）。
q[] 是题目给出的"合法 BFS 序列"。
ans[] 是程序自己 BFS 跑出来的顺序，用于和 q 对比
读入 n 个节点、n-1 条边的无向树（无向图，加双向边）。
读入目标序列 q，同时记录 idx[节点] = 该节点在 q 中的位置。
因为 BFS 从根节点 1 开始，所以根必须是 q 的第 0 位，否则直接输出 No
对每个节点的邻接表，按照 idx（节点在目标序列中的位置）从小到大排序
从根 1 开始 BFS，把访问到的节点按顺序存入 ans。
每加入一个节点，立即检查它与目标序列 q 在同一位置上的值是否一致。
由于邻接表已按 q 的顺序排好，若 q 是合法的 BFS 序，则 BFS 扩展就会严格复现 q；
一旦某个位置的节点与 q 不符，说明 q 不是合法的 BFS 序，输出 No；
若全程一致，则输出 Yes
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+10;
int idx[N];
bool cmp(int a, int b) { return idx[a] < idx[b]; }

int n, q[N], ans[N], l, r = -1;
vector<int> g[N];
bool vis[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y; g[x].push_back(y); g[y].push_back(x);
    }
    for (int i = 0; i < n; i++) cin >> q[i], idx[q[i]] = i;
    if (idx[1] != 0) return cout << "No\n", 0;
    for (int i = 1; i <= n; i++) ranges::sort(g[i], cmp);
    ans[++r] = 1; vis[1] = 1;
    while (l <= r) {
        int t = ans[l++];//出队
        for (auto z : g[t]) if (vis[z] == 0) {
            ans[++r] = z;//入队
            if (q[r] != ans[r]) return cout << "No\n", 0;
            vis[z] = 1;
        }
    }
    cout << "Yes\n";
    return 0;
}