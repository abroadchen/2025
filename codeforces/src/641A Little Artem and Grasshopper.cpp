//
// Created by Psy.C on 2026/3/31.
//
/**
0=未访问，1=已访问
读入每个位置的操作符：
< 对应 -1（向左移动）
其他（可能是>）对应 +1（向右移动）
读入每个位置的移动步长 x

起始位置：now = 1，从位置1开始
循环条件：b[now] != 1，直到访问到已访问过的节点
计算下一位置：t = now + a[now].op*a[now].x
如果 op = -1（<）：向左移动 x 步
如果 op = 1（>）：向右移动 x 步
边界检查：t >= 1 && t <= n
如果越界，输出 "FINITE" 并结束
如果不越界，标记当前位置已访问，移动到新位置
循环检测：如果访问到已访问的节点，输出 "INFINITE"

最好情况：O(1) - 立即越界
最坏情况：O(n) - 访问完所有节点后进入循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
struct node { int op, x; } a[N];
int n, b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        char c; cin >> c;
        if (c == '<') a[i].op = -1;
        else a[i].op = 1;
    }
    for (int i = 1; i <= n; ++i) cin >> a[i].x;
    int now = 1;
    while (b[now] != 1) {
        int t = now + a[now].op*a[now].x;
        if (t >= 1 && t <= n) {
            b[now] = 1;
            now = t;
        } else {
            cout << "FINITE\n";
            return 0;
        }
    }
    cout << "INFINITE\n";
    return 0;
}