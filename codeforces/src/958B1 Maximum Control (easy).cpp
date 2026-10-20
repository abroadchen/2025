//
// Created by Psy.C on 2026/10/20.
//
/**
a[N]：记录每个节点的度（连了几条边）‍。
ans：答案累加器
读入 n。
循环 i < n，即执行 n-1 次（因为一棵树正好有 n-1 条边）。
每条边 x y，把两端的度数都 +1：a[x]++、a[y]++。
由于是无向边，两个端点都要计，所以两个都加。
遍历所有节点 1..n。
a[i] == 1 为真（1）则加进去，否则加 0 —— 这等价于"统计度为 1 的节点个数"。
输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e3+1;

int n, a[N], ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i < n; ++i) {
        cin >> x >> y;
        a[x]++; a[y]++;
    }
    for (int i = 1; i <= n; ++i) ans += a[i] == 1;
    cout << ans;
    return 0;
}