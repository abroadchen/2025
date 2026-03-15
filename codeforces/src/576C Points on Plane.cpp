//
// Created by Psy.C on 2026/3/15.
//
/**
p[N]：存储所有点
v[M+5]：分块容器，每个vector存储一个块中的点

将点按x坐标分块
(p[i].x-1)/M+1 计算点属于哪一块
每块的x坐标范围大约是 [k*M+1, (k+1)*M]，其中k是块号

第一层排序：按x坐标整体排序
分块：将x坐标相近的点分为一组
对每一块内的点按y坐标排序
按顺序输出每个块内排序后的点的原始ID

排序：O(n log n)
分块：O(n)
块内排序：O(n log n)（各块排序之和）
总体：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, M = 1e3;
struct node { int x, y, id; } p[N];
vector<node> v[M+5];
int n;
int main() {
    fast;
    cin >> n;
    int mx = 0;
    for (int i = 1; i <= n; ++i)
        cin >> p[i].x >> p[i].y, p[i].id = i, mx = max(mx, p[i].x);
    sort(p + 1, p + n + 1, [](node a, node b) {
        return a.x < b.x;
    });
    for (int i = 1; i <= n; ++i)
        v[(p[i].x-1)/M+1].push_back(p[i]);
    for (int i = 1; i <= M; ++i) {
        ranges::sort(v[i], [](node a, node b) {
            return a.y < b.y;
        });
        for (int j = 0; j < v[i].size(); ++j)
            cout << v[i][j].id << ' ';
    }
    return 0;
}