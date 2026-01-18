//
// Created by Psy.C on 2026/1/18.
//
// 检查线段i是否嵌套在线段j中：
// seg[i].l > seg[j].l: i的左端点在j的右
// seg[i].l < seg[j].r: i的左端点在j内部
// seg[i].r > seg[j].r: i的右端点在j的右侧
// 即：j.l < i.l < j.r < i.r，形成了"包含"关系
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1003
using namespace std;

struct node { int l, r; } seg[N];

int main() {
    fast;
    int n, x[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> x[i];//每个点的坐标
    for (int i = 1; i < n; ++i) {
        seg[i].l = min(x[i], x[i + 1]);//线段左端点为相邻两数的较小值
        seg[i].r = max(x[i], x[i + 1]);
    }
    sort(seg + 1, seg + n, [](const node a, const node b) {
        if (a.l == b.l) return a.r < b.r;
        return a.l < b.l;
    });
    for (int i = 2; i < n; ++i) for (int j = 1; j < i; ++j) {//遍历所有线段对
        if (seg[i].l > seg[j].l && seg[i].l < seg[j].r && seg[i].r > seg[j].r) {
            cout << "yes\n";
            return 0;
        }
    }
    cout << "no\n";
    return 0;
}