//
// Created by Psy.C on 2026/9/23.
//
/**
ans[len]：记录「右区间在某个时刻之前、长度为 len、且价值最小」的值。
a 按左端点 l 升序排序。
b 按右端点 r 升序排序
外层 i 遍历 a（左端点递增），把当前 a[i] 视为右侧区间。
内层 while：把所有右端点 < a[i].l 的区间（即与 a[i] 不相交、完全在左侧）从 b 中取出，更新 ans[它们的长度] 为该长度的最小价值。
对每个 a[i]，需要配一个左区间长度 m - len(a[i])，查 ans[该长度] 是否存在（非无穷），若存在则更新答案 res = min(左区间最小价值 + a[i].val)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
struct node { int l, r, val; } a[N], b[N];
int cmp(const node& x, const node& y) { return x.l < y.l; }
int cmp2(const node& x, const node& y) { return x.r < y.r; }

int n, m, ans[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) ans[i] = INT_MAX;
    for (int i = 0; i < n; ++i) {
        node mid{};
        cin >> mid.l >> mid.r >> mid.val;
        a[i] = b[i] = mid;
    }
    sort(a, a + n, cmp);
    sort(b, b + n, cmp2);
    int t = 0, res = INT_MAX;
    for (int i = 0; i < n; ++i) {
        while (t < n && b[t].r < a[i].l) {
            ans[b[t].r-b[t].l+1] = min(ans[b[t].r-b[t].l+1], b[t].val);
            t++;
        }
        if (m-(a[i].r-a[i].l+1) > 0 && res > ans[m-(a[i].r-a[i].l+1)])
            res = min(ans[m-(a[i].r-a[i].l+1)]+a[i].val, res);
    }
    if (res == INT_MAX) cout << "-1"; else cout << res;
    return 0;
}