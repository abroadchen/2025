//
// Created by Psy.C on 2025/11/7.
//
/*
*x: 圆心x坐标
r: 半径
idx: 原始索引
fh: 被哪个点击中（默认-1表示未被击中）
 *
 *按照圆的左端点(x-r)对圆进行排序，确保处理时按从左到右的顺序
 *
 *读取点的坐标sx和sy
*寻找左端点≥sx的第一个圆
c[mid].x + c[mid].r 是圆的右端点
如果圆的右端点小于sx，说明圆在点左边，继续向右搜索
 *
*检查可能包含该点的圆（从位置lo开始的最多3个圆）：
如果圆已经被其他点击中(fh≠-1)，则跳过
 *
*检查点是否在圆内：
计算点到圆心的距离平方：dx² + dy²
计算半径的平方：r²
如果距离平方≤半径平方，说明点在圆内
标记该圆被第i个点击中，增加计数器
 *
 *按照原始索引对圆重新排序，恢复原来的顺序
*第一行输出被击中的圆的总数cnt
第二行输出每个圆被哪个点击中（-1表示未被击中），用空格分隔

排序：O(n log n)
查询：O(m log n + m)
总体：O(n log n + m log n)
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;


typedef long long ll;
struct Circle {
    int x, r, idx, fh = -1;
};


int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n; cin>>n;
    vector<Circle> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i].x >> c[i].r;
        c[i].idx = i;
    }
    sort(c.begin(), c.end(), [&](const Circle& a, const Circle& b) {
        return a.x - a.r < b.x - b.r;
    });
    int cnt(0), m; cin>>m;
    for (int i = 1; i <= m; ++i) {
        int sx, sy; cin>>sx>>sy;
        int lo(0), hi(n);
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (c[mid].x + c[mid].r < sx) lo = mid + 1;
            else hi = mid;
        }
        for (int j = lo; j <= min(n, lo + 2); ++j) {
            if (c[j].fh != -1) continue;
            ll dx = sx - c[j].x, dy = sy;
            if (dx * dx + dy * dy <= 1ll * c[j].r * c[j].r) {
                c[j].fh = i;
                ++cnt;
            }
        }
    }
    sort(c.begin(), c.end(), [&](const Circle& a, const Circle& b) {
        return a.idx < b.idx;
    });
    cout << cnt << '\n';
    for (int i = 0; i < n; ++i) cout << c[i].fh << (i + 1 < n ? ' ' : '\n');
    return 0;
}