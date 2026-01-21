//
// Created by Psy.C on 2026/1/21.
//
/**
 * n（数组长度）、m（查询次数）
 *a（输入数组）、sum（后缀和）、l（查询数组）、vis（访问标记）
 *O(n + m)：一次遍历 + m次查询
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000100
using namespace std;


int main() {
    fast;
    int n, m, i; cin >> n >> m;
    int a[N], sum[N], l[N], vis[N];
    for (i = 1; i <= n; ++i) { cin >> a[i]; sum[i] = 1; }
    for (i = 1; i <= m; ++i) cin >> l[i];
    memset(vis, 0, sizeof vis); sum[n+1] = 0;
    for (i = n; i >= 1; --i) {
        if (vis[a[i]] == 0) sum[i] += sum[i+1];//累加后续和
        else sum[i] = sum[i+1];//如果已出现过，直接继承
        vis[a[i]] = 1;//标记a[i]已访问
    }
    for (i = 1; i <= m; ++i) cout << sum[l[i]] << '\n';//每个查询位置的后缀和值
    return 0;
}