//
// Created by Psy.C on 2026/11/12.
//

/**
真正学会的起点..
N=105：最多点数上界。
M=1005：最多边数上界。
inf=1e9：作为 ans 初始值，用于给孤立点产生的一个从 1e9 倒数的假边号
a[N][M]：a[i][j] 存点 i 的第 j 条边的边号（顶点 i 的邻接边编号表）。
cnt[M]：cnt[i] 存点 i 的当前边数（度数计数器）。
w：全局边号计数器（从 0 递增），给每条边分配唯一编号
读 n、m。
循环 m 次，每次读一条边的两端 x、y。
++cnt[x] 与 ++cnt[y]：分别把 x、y 的边数各加 1。
++w：全局边号自增，得到这条新边的编号。
a[x][++cnt[x]] = a[y][++cnt[y]] = ++w：把这条边编号同时写进 x、y 的邻接边表（两端的该条边号都记为 w）。执行顺序：++w（拿到编号）→ 赋给 a[x][新cnt] → 赋给 a[y][新cnt]。
效果：每条无向边 (x,y) 被分配全局唯一编号 w，并记录在两端点的边表中。
ans = inf：初始 1e9。
遍历每个点 i（1..n）：
孤立点分支 if (!cnt[i])：该点没有任何边。
输出一行 1（表示该点输出 1 条"边"）、换行。
再输出 i <空格> ans-- 并换行：给孤立点配一个假边号 ans（从 1e9 开始每次递减）。
continue 跳到下一点。
有边分支：
先输出 cnt[i]（该点的度数）换行。
再循环 j=1..cnt[i]，逐条输出 i <空格> a[i][j] << '\n'：即"该点编号 + 该条边的编号"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 105, M = 1005, inf = 1e9;

int n, m, a[N][M], cnt[M], w;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, a[x][++cnt[x]] = a[y][++cnt[y]] = ++w;
    int ans = inf;
    for (int i = 1; i <= n; i++) {
        if (!cnt[i]) {
            cout << "1\n" << i << ' ' << ans-- << '\n';
            continue;
        }
        cout << cnt[i] << '\n';
        for (int j = 1; j <= cnt[i]; j++)
            cout << i << ' ' << a[i][j] << '\n';
    }
    return 0;
}