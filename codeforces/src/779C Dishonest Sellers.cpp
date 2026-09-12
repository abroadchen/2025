//
// Created by Psy.C on 2026/9/12.
//
/**
g[] 每个元素存 (a,b)。
cmp 按 b - a 降序排序
读入所有 a，再读入所有 b。
按 (b-a) 从大到小排序
前 k 个最大 (b-a) 的对象：取 a（方案 A）。
其余对象：取 min(a,b)（方案 B 或更优）。
累加得到最大总价值 ans 并输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5;
struct node { int a, b; } g[N];
inline bool cmp(const node& o1, const node& o2) {
    return o1.b - o1.a > o2.b - o2.a;
}

int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> g[i].a;
    for (int i = 0; i < n; ++i) cin >> g[i].b;
    sort(g, g + n, cmp);
    int ans = 0;
    for (int i = 0; i < k; ++i) ans += g[i].a;
    for (int i = k; i < n; ++i) ans += min(g[i].a, g[i].b);
    cout << ans << '\n';
    return 0;
}