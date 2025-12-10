//
// Created by Psy.C on 2025/12/10.
//
/*
*fa[N]：并查集的父节点数组
dis[N]：距离数组，用于记录节点到根节点的某种状态（异或值）
 *
*如果u是根节点（u == fa[u]），直接返回根节点
否则记录当前父节点t
递归查找父节点的根，并进行路径压缩（fa[u] = find(fa[u])）
更新dis[u]：dis[u] ^= dis[t]，实现异或值的传递
返回根节点
 *
 *
*如果u和v在同一个集合中：
计算dis[u] ^ dis[v] ^ c
如果结果为0，说明出现矛盾，将flag设为false
这里的逻辑是检查当前边是否与已有约束一致
 *
*如果u和v在不同集合中：
将y的根节点连接到x的根节点（合并两个集合）
更新dis[y]的值，使其满足新的约束关系
公式1 ^ dis[u] ^ dis[v] ^ c用于维护异或关系的一致性
 *
 *
*声明数组ans用于存储结果，cnt计数器
遍历所有节点，重新执行find操作确保路径压缩完成
如果dis[i]非零（即dis[i] == 1），将节点i加入结果数组
 *
*首先输出满足条件的节点个数cnt
然后输出所有满足条件的节点编号，用空格分隔
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 102
using namespace std;

int fa[N], dis[N];
int find(const int u) {
    if (u == fa[u]) return fa[u];
    const int t = fa[u];
    fa[u] = find(fa[u]);
    dis[u] ^= dis[t];
    return fa[u];
}

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) { fa[i] = i; dis[i] = 0; }
    bool flag = true;//无矛盾
    while (m--) {
        int u, v, c; cin >> u >> v >> c;
        if (flag == false) continue;//如果已经发现矛盾（flag == false），则跳过后续处理
        const int x = find(u), y = find(v);//查找节点u和v的根节点
        if (x == y) { if ((dis[u]^dis[v]^c)==0) flag = false; }
        else { fa[y] = x; dis[y] = 1 ^ dis[u] ^ dis[v] ^ c; }
    }
    if (flag == false) cout << "Impossible";
    else {
        int ans[N], cnt = 0;
        for (int i = 1; i <= n; ++i) {
            find(i);
            if (dis[i]) ans[cnt++] = i;
        }
        cout << cnt << '\n';
        for (int i = 0; i < cnt; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}