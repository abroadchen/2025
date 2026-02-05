//
// Created by Psy.C on 2026/2/5.
//
/**
* id: 节点的标识符
col: 颜色（0或1）
i: 原始位置索引
 *
*如果i是奇数，i&1 = 1，分配颜色1
如果i是偶数，i&1 = 0，分配颜色0
实现了交替分配颜色的效果
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

struct node {
    int id, col, i;
    bool operator<(const node x) const {
        return id < x.id;
    }
} a[N];

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i].id, a[i].i = i;
    for (int i = 1, c; i <= m; ++i) cin >> c >> c;
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) a[i].col = i&1;
    sort(a + 1, a + n + 1, [](const node x, const node y) {
        return x.i < y.i;//恢复到输入时的顺序 但保持颜色分配
    });
    for (int i = 1; i <= n; ++i) {
        if (i != 1) cout << ' ';//第一个元素前不输出空格
        cout << a[i].col;//输出每个位置的颜色
    }
    cout << '\n';
    return 0;
}