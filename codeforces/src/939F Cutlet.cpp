//
// Created by Psy.C on 2026/10/17.
//
/**
N：坐标/长度上限 2e5；M：天数/物品数上限 105；inf=0x3f3f3f3f：极大值（用于表示不可达）。
f[M][N]：DP 表，f[i][j] 表示处理完第 i 个区间后、位置/状态为 j 的最小代价。
q[N]：单调队列（存下标）
初始化 f[0] 全为 inf，f[0][0]=0（第 0 个区间，状态 0 代价 0，其余不可达）。

外层循环读入 m 个区间 [l, r]：

先把 f[i][j] = f[i-1][j]（不做任何变换的转移，即"从第 i-1 层原样继承"），作为该层初始值。
第一段单调队列（正向）‍：j 从 0 到 min(r,n)，维护 f[i-1][q[]] 的最小值单调队列：
入队前弹掉队尾中值比 f[i-1][j] 大的（保持队列值单调递增，队首即最小值）；
把 j 入队；
弹掉队首中下标 q[L] 小于 j-(r-l) 的（保证窗口有效范围）；
f[i][j] = min(f[i][j], f[i-1][q[L]]+2)：用队列里的最小值 +2 来松弛。
第二段单调队列（反向）‍：j 从 r 递减到 0，同理维护最小队列，这次下标映射是 r-j（把 r-j 入队），窗口下限 l-j；f[i][j] = min(f[i][j], f[i-1][q[L]]+1)：用最小值 +1 松弛。
最后 printf(f[m][n] >= inf ? "Hungry" : "Full\n%d", f[m][n])：

若 f[m][n] 仍是 inf（不可达），输出 "Hungry"；
否则输出 "Full" 换行再输出最小代价 f[m][n]。


有 m 个「操作/区间」，每个能让你从某个位置跳到某个范围，代价分 +1 和 +2 两种。
f[i][j] = 用前 i 个操作，能否/最少代价到达位置 j。
第一段正向队列：对 j∈[0,min(r,n)]，从 i-1 层的某个状态（在窗口内）加 2 转移来——对应一种移动代价 2 的转移。
第二段反向队列：从 r 递减扫描，用映射 r-j 入队，窗口下限 l-j，加 1 转移——对应代价 1 的另一类移动。
两段都用单调队列优化，把原本 O(n) 的区间取 min 降到均摊 O(1)。
单调队列优化点：形如 f[i][j] = min_{k∈[j-w, j]} f[i-1][k] + C（滑动窗口最小值）的转移，用递减下标的单调队列 O(1) 取区间最小值，从而整层 O(n)，总 O(n·m)。


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 2e5+5, M = 105, inf = 0x3f3f3f3f;

int n, m, f[M][N], q[N];
int main() {
    fast;
    cin >> n >> m;
    memset(f[0], 0x3f, sizeof f[0]); f[0][0] = 0;
    for (int i = 1, l, r, L, R; i <= m; i++) {
        for (int j = 0; j <= n; j++) f[i][j] = f[i-1][j];
        cin >> l >> r; L = 1, R = 0;
        for (int j = 0; j <= min(r, n); j++) {
            while (L <= R && f[i-1][q[R]] > f[i-1][j]) R--;
            q[++R] = j;
            while (L <= R && q[L] < j-(r-l)) L++;
            f[i][j] = min(f[i][j], f[i-1][q[L]]+2);
        }
        L = 1, R = 0;
        for (int j = r; ~j; j--) {
            while (L <= R && f[i-1][q[R]] > f[i-1][r-j]) R--;
            q[++R] = r-j;
            while (L <= R && q[L] < l-j) L++;
            f[i][j] = min(f[i][j], f[i-1][q[L]]+1);
        }
    }
    printf(f[m][n] >= inf ? "Hungry" : "Full\n%d", f[m][n]);
    return 0;
}