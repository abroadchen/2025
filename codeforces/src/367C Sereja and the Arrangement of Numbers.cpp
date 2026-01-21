//
// Created by Psy.C on 2026/1/20.
//
/*
* 预计算：O(N)
排序：O(m log m)
总体：O(N + m log m)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10010
using namespace std;


int main() {
    fast;
    int n, m, w[N*10]; cin >> n >> m;
    ll a[N];
    for (int i = 1; i < N; ++i) {//预计算数组
        if (i&1) a[i] = i * (i-1) / 2 + 1;
        else a[i] = i * i / 2;
    }
    for (int i = 1, t; i <= m; ++i) cin >> t >> w[i];//忽略第一个输入t
    sort(w + 1, w + m + 1, [](const int x, const int y) {
        return x > y;//降序排序权重数组
    });
    int p;
    for (int i = 1; i < N; ++i) { if (a[i] <= n) p = i; else break; }//找到最大的i
    ll ans = 0;
    for (int i = 1; i <= min(m, p); ++i) ans += w[i];
    cout << ans << '\n';
    return 0;
}