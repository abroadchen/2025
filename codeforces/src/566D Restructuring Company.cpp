//
// Created by Psy.C on 2026/3/12.
//
/**
nxt[N]: 后继数组，用于优化区间操作

将节点x和y所在的集合合并
通过find(x)和find(y)找到各自的根节点
将x的根节点指向y的根节点

区间合并操作：将[x+1, y]范围内的所有相邻节点合并
j = to: 优化循环跳转
fa[find(j - 1)] = find(j): 将j-1和j合并
nxt[j] = nxt[y]: 更新j的后继为y的后继（区间压缩）
to = nxt[j]: 获取下一个需要处理的位置

查询x和y是否在同一连通分量中
如果根节点相同，输出"YES"，否则输出"NO"

单次查询：O(α(n))，α是阿克曼函数的反函数
区间合并：O(k)，k是区间内独立段的数量
总体：近似O(q × α(n))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, q, nxt[N];
int main() {
    fast;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) fa[i] = i, nxt[i] = i + 1;
    for (int i = 1, op, x, y; i <= q; ++i) {
        cin >> op >> x >> y;
        if (op == 1) fa[find(x)] = find(y);
        if (op == 2) {
            int to;
            for (int j = x + 1; j <= y; j = to) {
                fa[find(j - 1)] = find(j);
                to = nxt[j], nxt[j] = nxt[y];
            }
        }
        if (op == 3)
            find(x) == find(y) ? cout << "YES\n" : cout << "NO\n";
    }
    return 0;
}