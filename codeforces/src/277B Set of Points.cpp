//
// Created by Psy.C on 2025/12/26.
//
/*
* n：节点数
m：目标路径数
 *当路径数为3且节点数大于4时，无解
 *
*cnt：计数器，表示当前构造的边的权重
ans：累积的答案值
循环m次，输出m条边：
从节点i到节点i的自环，权重为ans
每次ans增加cnt的值，然后cnt自增
 *
*如果m < n，输出一条从节点(m+N)到节点m的边
权重为当前的ans值
节点(m+N)使用了偏移量N来避免与之前的节点冲突
 *
*从节点(m+1)到(n-1)继续构造边
节点编号使用(i+N)避免冲突
权重为(ans - --cnt)，其中：
--cnt先将cnt减1，再参与运算
ans减去递减的cnt值
 *
*这段代码的目的是构造一个图，使得从起点到终点的路径数为m：
前m条边：创建自环或前向边，逐步累积权重
特殊连接：当m < n时，连接到偏移后的节点
后续边：继续构造边，但权重逐渐减少
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    if (m == 3 && n > 4) { cout << "-1\n"; return 0; }
    int cnt = 0, ans = 0;
    for (int i = 0; i < m; ++i) cout << i << ' ' <<
        (ans = ans + cnt++) << '\n';
    if (m < n) cout << m + N << ' ' << ans << '\n';
    for (int i = m + 1; i < n; ++i) cout << i + N << ' ' <<
        (ans = ans - --cnt) << '\n';
    return 0;
}