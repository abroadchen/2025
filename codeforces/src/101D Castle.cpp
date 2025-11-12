//
// Created by Psy.C on 2025/11/12.
//
/*
*n为节点数
s1[N]和s2[N]为辅助数组
e[N]存储每个节点的边索引
to存储边的目标节点
we存储边的权重
 *
*添加无向边(u,v)，权重为w
使用邻接表存储图，但通过索引方式存储
每条边在两个节点的邻接表中都存储
 *
 *s1[u]初始化为1（包含自身）
 *ans存储子节点
 *
*遍历当前节点的所有邻接边：
to[v] ^ fa确保不访问父节点（异或不等于）
递归计算子树结果
累加边权重与子树大小的乘积
更新s2和s1数组
将子节点加入ans
 *
*s1[u]：以u为根的子树节点数
s2[u]：子树内边的贡献值 w

从剩余节点数中减去当前子树的节点数
表示处理完这个子树后，还剩下多少节点需要处理
s2[v]：表示处理子树v时每条相关路径的单位代价
tot：表示当前还有多少节点会受到这个子树处理的影响
s2[v] * tot：表示处理子树v的总代价

比较两个节点的单位权重比：s2[节点] / s1[节点]
优化目标
分子 s2[节点]：表示该子树的权重贡献
分母 s1[节点]：表示该子树的规模
比值：表示单位规模的权重贡献
 *
 *
 *tot为剩余节点数
 *O(n log n)：主要是排序的开销
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;
const int N = 1e5;
int n, s1[N], s2[N];
vector<int> e[N], to, we;

void add(int u, int v, int w) {
    e[u].push_back(sz(to));
    to.push_back(v);
    we.push_back(w);
    e[v].push_back(sz(to));
    to.push_back(u);
    we.push_back(w);
}

ll dfs(int u, int fa) {
    ll res(0); s1[u] = 1, s2[u] = 0;
    vector<int> ans;
    for (int v : e[u]) if (to[v] ^ fa) {
        res += dfs(to[v], u);
        res += 1ll * we[v] * s1[to[v]];
        s2[to[v]] += we[v] * 2;
        s1[u] += s1[to[v]];
        s2[u] += s2[to[v]];
        ans.push_back(to[v]);
    }
    sort(ans.begin(), ans.end(), [&](int p, int q) {
        return 1ll * s2[p] * s1[q] < 1ll * s2[q] * s1[p];
    });
    int tot = s1[u] - 1;
    for (int v : ans) tot -= s1[v], res += 1ll * s2[v] * tot;
    return res;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.precision(12);
    cin >> n;
    for (int i = 1, u, v, w; i < n; ++i) {
        cin >> u >> v >> w; --u, --v;
        add(u, v, w);
    }
    cout << fixed << 1. * dfs(0, -1)/(n - 1) << '\n';
    return 0;
}