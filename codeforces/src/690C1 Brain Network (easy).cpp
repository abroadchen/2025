//
// Created by Psy.C on 2026/4/16.
//
/**
如果x的父节点就是自己，则返回x；
否则递归查找父节点，并将路径上的节点直接连接到根节点（路径压缩）

for (int i = 0, x, y; i < m; ++i)：循环m次，处理m条边
cin >> x >> y;：读入边的两个端点x和y
x = find(x); y = find(y);：查找x和y各自的根节点
if (x == y) ok = false; else fa[y] = x;：
如果x和y的根节点相同，说明这条边会形成环，将ok设为false
否则将y的根节点连接到x的根节点下，实现合并操作

ok：表示没有形成环（即没有重复连接同一连通分量内的节点）
m == n-1：边数等于节点数减1（这是树的性质）
cout << "yes\n";：如果两个条件都满足，输出"yes"
else cout << "no\n";：否则输出"no"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;

int fa[N];
int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

int n, m;
int main() {
    fast;
    cin >> n >> m;
    bool ok = true;//标记图是否符合条件
    for (int i = 1; i <= n; ++i) fa[i] = i;
    for (int i = 0, x, y; i < m; ++i) {
        cin >> x >> y; x = find(x); y = find(y);
        if (x == y) ok = false; else fa[y] = x;
    }
    if (ok && m == n-1) cout << "yes\n"; else cout << "no\n";
    return 0;
}