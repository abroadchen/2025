//
// Created by Psy.C on 2026/1/8.
//
/**
 *
* 在后序遍历中，我们先访问所有的子节点，再访问当前节点。这意味着：

只有当节点2*u%n和(2*u+1)%n都被处理完，才会处理节点u
这保证了处理节点u之前，它的"依赖节点"已经被处理完毕
2. 拓扑排序的逆序
如果你将边的方向反转（从子节点指向父节点），那么：

2*u%n → u 和 (2*u+1)%n → u
这样就形成了一个有向无环图（DAG）
后序遍历的结果翻转后就是拓扑排序
 *
 *
 *
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;

int vis[N], n, ans[N], tot;
void dfs(const int u) {
    if (vis[u]) return; vis[u] = 1;
    dfs(u * 2 % n); dfs((u * 2 + 1) % n);//递归访问两个子节点
    ans[++tot] = u;//后序遍历，将当前节点u加入答案数组
}


int main() {
    fast;
    cin >> n;
    if (n & 1) return cout << "-1\n", 0;
    dfs(0);
    for (int i = tot; i >= 1; --i) cout << ans[i] << ' ';
    cout << "0\n";
    return 0;
}