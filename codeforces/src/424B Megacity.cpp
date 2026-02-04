//
// Created by Psy.C on 2026/2/4.
//
/**
* k：圆形的分数值
r：圆形到原点的距离（半径）
*n：圆形数量
s：初始分数
 *坐标(a,b)
 *
*时间复杂度：O(n log n)，主要是排序的时间
空间复杂度：O(n)，存储圆形信息
 */
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10050
#define inf 1000000
using namespace std;

struct node { int k; double r; } d[N];

int main() {
    fast;
    int n, s; cin >> n >> s;
    for (int i = 0, a, b; i < n; ++i) {
        cin >> a >> b >> d[i].k;
        d[i].r = sqrt(a*a + b*b);
    }
    sort(d, d + n, [](const node x, const node y) {
        return x.r < y.r;
    });
    cout << fixed << setprecision(7);
    for (int i = 0; i < n; ++i) {
        s += d[i].k;
        if (s >= inf) {
            cout << d[i].r;
            return 0;
        }
    }
    cout << -1 << '\n';
    return 0;
}