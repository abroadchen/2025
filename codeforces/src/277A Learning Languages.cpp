
/*
 * fa数组：并查集中每个元素的父节点，大小为150
*find函数：查找x的根节点（集合代表）
路径压缩优化：fa[x] = find(fa[x])，将路径上所有节点直接连接到根节点
如果x等于其父节点，说明x就是根节点
*join函数：合并x和y所在的集合
先找到x和y的根节点
如果根节点不同，则将x的根节点连接到y的根节点下
 *
*n：人数
m：音乐类型数
ans：没有听任何音乐的人数
vis[105]：记录每种音乐被多少人听过
 *
*循环处理每个人的音乐喜好
t：当前人听的音乐数量
如果t为0，说明这人没听任何音乐，ans++
否则读入这个人听的所有音乐，并：
在vis数组中标记这些音乐被听过
将相邻的两种音乐合并到同一集合（使用join函数）
 *
 *遍历所有音乐类型，如果被听过(vis[i] > 0)且是根节点(fa[i] == i)，说明是一个连通分量的代表
 *由于所有听过音乐的人可能形成一个大组，减去1是因为要排除与"没有音乐"的那个组的连接
 *输出答案：没听音乐的人数 + 额外的连通分量数
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int fa[150];
int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void join(int x, int y) {
    x = find(x); y = find(y);
    if (x != y) fa[x] = y;
}

int main() {
    fast;
    int n, m, ans = 0, vis[105]={}; cin >> n >> m;
    for (int i = 0; i < 101; ++i) fa[i] = i;
    for (int i = 0, t; i < n; ++i) {
        cin >> t;
        if (t == 0) { ans++; continue; }
        int a[105]; cin >> a[0];
        vis[a[0]]++;
        for (int j = 1; j < t; ++j) {
            cin >> a[j];
            vis[a[j]]++;
            join(a[j - 1], a[j]);
        }
    }
    int res = 0;
    for (int i = 1; i <= m; ++i) if (vis[i]) {
        if (fa[i] == i) res++;
    }
    res = max(0, res - 1);
    cout << ans + res << '\n';
    return 0;
}