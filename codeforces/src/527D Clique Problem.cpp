//
// Created by Psy.C on 2026/3/3.
//
/**
循环读入每对(x, y)，并将其转换为区间[x-y, x+y]
这里进行了坐标变换，将原问题转换为区间覆盖问题

按照右端点r升序排列
如果右端点相同，则按照左端点l升序排列

如果当前区间左端点a[i].l大于等于上一个选中区间的右端点x
说明这两个区间不重叠，可以选择当前区间
ans++增加计数
更新x = a[i].r，记录当前选中区间的右端点
时间复杂度为O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1, inf = 0x3f3f3f3f;
struct node { int l, r; } a[N];
int n;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x, y; i <= n; ++i) {
        cin >> x >> y;
        a[i].l = x - y, a[i].r = x + y;
    }
    sort(a + 1, a + n + 1, [](const node x, const node y) {
        return x.r == y.r ? x.l < y.l : x.r < y.r;
    });
    int x = -inf, ans = 0;
    for (int i = 1; i <= n; ++i)
        if (x <= a[i].l) ans++, x = a[i].r;
    cout << ans << '\n';
    return 0;
}