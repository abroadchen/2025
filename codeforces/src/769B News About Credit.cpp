//
// Created by Psy.C on 2026/9/8.
//
/**
a[N]：存节点信息（first 为某个数值，second 为原始编号）。
vis[N]：存要输出的配对结果（每项是一对 (x, y)）
a[1] 被排除在排序之外——即固定第一个元素（编号对应 a[1].first 的那个节点）放在最前面，其余 n-1 个从大到小排
r 是"当前已覆盖到下标 r"。初始 r=1（即节点 a[1] 已被视为起点）。
对每个 i=1..n：
if (r < i) { cout << -1; return 0; }：如果已经覆盖到了 i 后面（r<i 意味着 i 这个位置还没被覆盖到就被跳过了），说明贪心失败、无法构造，输出 -1 并退出。
内层循环：把 a[i] 与从 r+1 到 r+a[i].first（最多到 n）之间的后续节点逐一配对，记入 vis[++cnt] = {a[i].second, a[j].second}——即"第 i 个大节点"与它后面若干个小节点配对。
r += a[i].first：把已覆盖的右指针向右推进 a[i].first 个位置（即这个节点的"度数"量）。
if (r > n) break;：覆盖完所有节点就提前结束
先输出配对数 cnt，再逐行输出每对 (first, second)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 201;

bool cmp(ii x, ii y) { return x.first > y.first; }

ii a[N], vis[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first; a[i].second = i;
    }
    sort(a+2, a+1+n, cmp);
    int cnt = 0;
    for (int i = 1, r = 1; i <= n; ++i) {
        if (r < i) { cout << -1; return 0; }
        for (int j = r+1; j <= min(r+a[i].first, n); ++j)
            vis[++cnt] = {a[i].second, a[j].second};
        r += a[i].first;
        if (r > n) break;
    }
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; ++i)
        cout << vis[i].first << ' ' << vis[i].second << '\n';
    return 0;
}