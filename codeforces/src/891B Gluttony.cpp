//
// Created by Psy.C on 2026/10/9.
//
/**
读入
n
n 个数，结构体 a[i] 存值 x 和原始下标 id
按数值从小到大排序。注意之后 a[i] 的下标不再对应原输入位置，而是按值排序后的位置
对于排序后的位置：第
i
i 小（
i
<
n
i<n）的元素，其答案设为第
i
+
1
i+1 小的值（即"下一个更大"的数）。
最大的元素（排序后第
n
n 位）‍，其答案设为最小的数 a[1].x（循环回去）。
结果写回对应原下标 id
按原输入顺序输出每个位置的新值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 205, M = 25;
struct node { int x, id; } a[N];
bool cmp(node x, node y) { return x.x < y.x; }

int ans[M];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].x; a[i].id = i;
    }
    sort(a+1, a+n+1, cmp);
    for (int i = 1; i < n; ++i)
        ans[a[i].id] = a[i+1].x;
    ans[a[n].id] = a[1].x;
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}