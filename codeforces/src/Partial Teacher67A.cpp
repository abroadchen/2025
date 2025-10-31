//
// Created by Psy.C on 2025/10/31.
//
/*
 *定义pair<int, int>的别名为pii，用于表示边和权重
*n: 节点数量
// l, r: 临时变量，用于存储左右节点
// deg[N]: 每个节点的入度数组
// fa[N]: 并查集父节点数组
ans[N]: 存储每个节点的答案（高度）
 *
 *初始化并查集，每个节点的父节点初始化为自己
 *
 *'R'表示i节点高度应小于i+1节点，建立l->r的边
 *'L'表示i节点高度应大于i+1节点，建立r->l的边
 *
*初始化队列，将所有入度为0的节点加入队列
    // 入度为0意味着没有约束条件要求它比其他节点小
 *
 *
 *遍历u的所有邻接节点
 *更新邻接节点的高度：至少为当前节点高度+边权
 *减少邻接节点的入度
 *如果邻接节点入度变为0，则加入队列
 *
 *输出结果，对每个节点输出其所在集合代表元的高度值
 *
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
const int N = 1005;
int n, l, r, deg[N], fa[N], ans[N];
char s[N];//存储输入的字符序列
vector<pii> e[N];//邻接表，存储图的边
queue<int> q;//用于拓扑排序
//如果x是根节点则返回x，否则递归查找并更新父节点
int find(int x){ return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 1; i < n; ++i) {
        cin >> s[i];
        if (s[i] == '=') fa[i] = fa[i + 1];//合并i和i+1所在的集合
    }
    for (int i = 1; i < n; ++i) {
        l = find(i), r = find(i + 1);//找到节点i和i+1所在集合的代表元（根节点）
        if (l == r) continue;// 如果两个节点已在同一集合，跳过
        if (s[i] == 'R') e[l].push_back({r, 1}), deg[r]++;
        else if (s[i] == 'L') e[r].push_back({l, 1}), deg[l]++;
    }
    for (int i = 1; i <= n; ++i) {
        if (!deg[i]) { ans[i] = 1; q.push(i); }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : e[u]) {
            ans[v.first] = max(ans[v.first], ans[u] + v.second);
            deg[v.first]--;
            if (!deg[v.first]) q.push(v.first);
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[find(i)] << ' ';
    return 0;
}