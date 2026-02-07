//
// Created by Psy.C on 2026/2/7.
//
/*
排序：O(n log n)
图遍历：O(n + m)
总体：O(n log n + m)
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;

struct node { int id, val; } p[N];//节点ID和值的对
int val[N], n, m;
vector<int> g[N];
void init() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> val[i];
        p[i].id = i;
        p[i].val = val[i];
    }
    sort(p + 1, p + n + 1, [](const node a, const node b) {
        return a.val > b.val;
    });
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
}


int main() {
    fast; init();
    int v[N]{}, ans = 0;//跟踪已处理的节点
    for (int i = 1; i <= n; ++i) {
        const int u = p[i].id; v[u] = 1;
        for (const int vi : g[u]) {
            if (v[vi]) continue;
            ans += val[vi];
        }
    }
    cout << ans << '\n';
    return 0;
}