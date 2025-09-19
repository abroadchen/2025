//
// Created by Psy.C on 2025/9/18.
//
/*
*n: 节点数
m: 边数
v: 特殊节点
 *
*(n-1)*(n-2)/2 是n-1个节点的完全图的边数
加1是因为还要连接特殊节点v
这是能构造出满足条件的图的最大边数
n-1: 最小边数（形成连通图的最少边数）
只有当m在这个范围内才可能构造出满足条件的图
 *
*tk: 已添加的边数计数器，初始为1（因为先添加一条边）
mark: 与特殊节点v连接的另一个节点
如果v == n，则mark = n-1
否则mark = n
 *
*双重循环枚举所有可能的节点对(i,j)，其中i<j
跳过与mark节点相关的边（避免重复或冲突）
输出边并增加计数器
当达到要求的边数m时停止

 *
 *
 *
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll n, m, v;
    while (cin >> n >> m >> v) {
        ll tmp = (n - 1) * (n - 2) / 2 + 1;
        if (m >= (n - 1) && m <= tmp) {
            int tk = 1, mark = (v == n ? n - 1 : n);

            cout << v << " " << mark << endl;

            for (int i = 1; i < n && tk != m; ++i)
                for (int j = i + 1; j <= n; ++j) {
                    if (j == mark) continue;
                    cout << i << " " << j << endl;
                    tk++;
                    if (tk == m) break;
                }
        } else printf("-1\n");
    }
    
    return 0;
}