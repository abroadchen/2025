//
// Created by Psy.C on 2026/1/8.
//
/**
* n：矩形数量
y[N]：辅助数组，记录每个y坐标位置的x边界
l, r, t, d：分别表示左、右、上、下边界
 *
 *假设能拼成矩形
*同时更新边界值：
l：所有矩形的最小x1（最左边）
d：所有矩形的最小y1（最下边）
r：所有矩形的最大x2（最右边）
t：所有矩形的最大y2（最上边）
 *
*外层：遍历所有矩形
内层：遍历矩形的y区间[tr[i].y1, tr[i].y2-1]
if (y[j] == tr[i].x1) y[j] = tr[i].x2;：如果当前位置y[j]正好是矩形的左边界，更新为右边界
else ans = false;：否则说明有重叠或间隙，设置结果为false
 *
*检查y数组的每个位置是否都等于右边界r
如果有任何位置不等于r，说明矩形没有完全填满整个区域
 *检查形成的矩形是否为正方形（r-l表示宽度，t-d表示高度）
 *
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 31401
#define inf 2e9
using namespace std;

//左下角(x1,y1)和右上角(x2,y2)
struct node { int x1, x2, y1, y2; } tr[5];

int main() {
    fast;
    int n, y[N], l, r, t, d; cin >> n;
    bool ans = true; l = d = inf, r = t = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tr[i].x1 >> tr[i].y1 >> tr[i].x2 >> tr[i].y2;
        if (l > tr[i].x1) l = tr[i].x1;
        if (d > tr[i].y1) d = tr[i].y1;
        if (r < tr[i].x2) r = tr[i].x2;
        if (t < tr[i].y2) t = tr[i].y2;
    }
    sort(tr, tr + n, [](const node a, const node b) {
        return a.x1 < b.x1 || (a.x1 == b.x1 && a.y1 < b.y1);
    });
    for (int i = d; i <= t - 1; ++i) y[i] = l;
    for (int i = 0; i < n; ++i) for (int j = tr[i].y1; j <= tr[i].y2 - 1; ++j) {
        if (y[j] == tr[i].x1) y[j] = tr[i].x2; else ans = false;
    }
    for (int i = d; i <= t - 1; ++i) if (y[i] != r) ans = false;
    if (r - l != t - d) ans = false;
    if (ans) cout << "YES\n"; else cout << "NO\n";
    return 0;
}