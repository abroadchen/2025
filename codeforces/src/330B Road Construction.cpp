//
// Created by Psy.C on 2026/1/9.
//
///时间：O(m + n)，其中 m 是输入边数，n 是节点数
///空间：O(n)，用于布尔标志数组
///
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, a, b; cin >> n >> m;
    bool flag[1001] = {};
    while (m--) {
        cin >> a >> b;
        flag[a] = true; flag[b] = true;//标记在边中出现的节点
    }
    int x = 1; while (flag[x]) x++;//找到最小的未使用节点编号
    cout << n - 1 << '\n';//输出边的总数
    for (int i = 1; i < x; ++i) cout << i << ' ' << x << '\n';//将x之前的所有节点连接到节点x
    for (int i = x + 1; i <= n; ++i) cout << x << ' ' << i << '\n';//将x之后的所有节点连接到节点x
    return 0;
}