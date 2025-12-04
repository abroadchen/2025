//
// Created by Psy.C on 2025/12/3.
//
/*
*n: 节点数量
ans: 结果累加值
p[N]: 并查集父节点数组
dep[N]: 深度/距离数组，存储节点到根节点的距离
 *
 *如果x是根节点（父节点等于自己），直接返回x
 *递归查找x的父节点的根节点
 *路径压缩时更新dep[x]：将x到原父节点的距离加上原父节点到根的距离
 *将x的父节点直接指向根节点（路径压缩），并返回根节点
 *
 *f函数，用于连接两个节点并更新相关信息
 *x和y是要连接的节点，w是它们之间的权重
 *保存原始的y节点值
 *找到x和y的根节点
 *获取原来y节点的深度值
*将y的根节点连接到x的根节点下
更新y根节点的深度：原深度d加上新边的权重w（经过模运算处理）
 *将y根节点的新深度累加到答案中
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7;
int n, ans;
int p[N], dep[N];

int find(const int x) {
    if (p[x] == x) return x;
    const int t = find(p[x]);
    dep[x] = (dep[x] + dep[p[x]]) % mod;
    return p[x] = t;
}

void f(int x, int y, const int w) {
    const int t = y;
    x = find(x), y = find(y);
    const int d = dep[t];
    p[y] = x, dep[y] = ((w + mod) % mod + d) % mod;
    ans = (ans + dep[y]) % mod;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) p[i] = i;//每个节点的父节点初始化为自己
    for (int i = 1, m; i <= n; ++i) {//处理每个节点i（从1到n）
        cin >> m;//输入与节点i相连的边数m
        for (int j = 1, u, w; j <= m; ++j) {//处理与节点i相连的每条边
            cin >> u >> w;
            f(i, u, w);//连接节点i和u，权重为w
        }
    }
    cout << ans << '\n';
    return 0;
}