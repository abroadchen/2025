//
// Created by Psy.C on 2026/2/4.
//
/**
* n：顶点数，p：阈值
vis[N]：度数数组，vis[i]表示顶点i的度数
mp：记录边的出现次数（处理重边）

目标值：res = max(0, p - a[i])，即与顶点i配对所需最小度数
查找范围：在[1, i-1]范围内查找第一个度数≥res的位置
统计：i - pos表示与顶点i配对满足条件的顶点数量

时间复杂度：O(n log n)，主要是排序和二分查找的时间
空间复杂度：O(n)，用于存储度数数组和边的映射
 */
#include <algorithm>
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
using namespace std;


int main() {
    fast;
    int n, p, vis[N]; cin >> n >> p;
    map<pair<int, int>, int> mp;
    for (int i = 1, u, v; i <= n; ++i) {
        cin >> u >> v;
        vis[u]++; vis[v]++;
        if (u > v) swap(u, v);
        mp[{u,v}]++;
    }
    int a[N];
    for (int i = 1; i <= n; ++i) a[i] = vis[i];
    sort(a + 1, a + n + 1);
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        const int res = max(0, p - a[i]);
        int l = 1, r = i - 1, pos = i;
        while (l <= r) {
            if (const int mid = (l + r) >> 1; a[mid] >= res) { pos = mid; r = mid - 1; }
            else l = mid + 1;
        }
        ans += i - pos;
    }
    for (auto [fst, snd] : mp) {
        if (int u = fst.first, v = fst.second;
            vis[u] + vis[v] >= p && vis[u] + vis[v] - snd < p) ans--;
    }
    cout << ans << '\n';
    return 0;
}