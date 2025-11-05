//
// Created by Psy.C on 2025/11/5.
//
/*
*读取节点数n
读取每个节点的权值a[i]（表示需要访问该节点的次数）
*构建树的邻接表表示
读取n-1条边，建立无向图（树）
 *读取起始节点s（转换为0-based索引）
*定义递归DFS函数，返回值为pair<ll, int>：

first: 从节点x出发遍历其子树所需最小代价
second: 遍历完后剩余的"盈余"次数
*v: 存储所有子树的遍历代价
d: 所有子树遍历后总的盈余次数
对每个子节点y（除了父节点p），递归计算子树信息
*计算当前节点x的净需求次数：

a[x]: 该节点需要访问的次数
(bool)~p: 如果p不是-1（即不是根节点），则减1
这是因为进入节点x需要一次移动，但如果x是起点则不需要
*计算遍历子树的代价：

将子树代价按降序排列（优先选择代价大的）
对于前w个子树，每个都需要额外代价2（来回的移动）
累加这些代价到e
 *
*first: 总代价 = 子树代价e + min(w,d)*2
min(w,d)*2: 多余的需求次数w与盈余次数d的匹配，每匹配一对节省2的代价
second: 剩余的净需求次数 = w - min(w,d)
 *
*从起始节点s开始DFS，输出最小代价
父节点传-1表示s是根节点
 *
*auto &&self: 这是一个通用引用参数

&& 在这里不是右值引用，而是通用引用
它可以接受左值或右值参数
self 参数的用途:

当我们调用 dfs(dfs, s, -1) 时
第一个参数 dfs 被传递给 self 形参
在函数内部，通过 self(self, y, x) 实现递归调用
 *
 *
*时间复杂度：O(n log n)（主要是排序）
空间复杂度：O(n)
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, s; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; cin >> x >> y; x--; y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    cin >> s; s--;

    auto dfs = [&](auto &&self, int x, int p) -> pair<ll, int> {
        vector<ll> v;
        ll d(0);
        for (int y : adj[x]) {
            if (y != p) {
                auto [e, w] = self(self, y, x);
                v.push_back(e);
                d += w;
            }
        }
        int w = a[x] - (bool)~p;
        ll e(0);
        sort(v.begin(), v.end(), greater<ll>());
        for (auto i : v) {
            if (!w) break;
            e += i + 2;
            w -= 1;
        }
        return {e + min((ll)w, d)*2, w - min((ll)w, d)};
    };
    cout << dfs(dfs, s, -1).first << '\n';
    return 0;
}