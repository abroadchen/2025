//
// Created by Psy.C on 2026/2/2.
//
/**
* N：最大行数（20010）
M：最大查询数（200010）
 *n（行数）、m（列数）、k（操作次数）
*mat[N][12]：矩阵，大小为 N×12，存储矩阵元素
ans[M]：结果数组，存储每行的答案
l[12]：列权重数组，大小为12
a, b：临时变量，用于读取操作参数 a（行号）和 b（列号）
*--ans[a]：对应行的结果减1
++l[b]：对应列的权重加1
 *
 *时间复杂度：O(n×m + k)，适合处理稀疏矩阵或列数较小的情况
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 20010
#define M 200010
using namespace std;


int main() {
    fast;
    int n, m, k, i, j; cin >> n >> m >> k;
    int mat[N][12], a, b, ans[M], l[12];
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j) cin >> mat[i][j];
    for (i = 1; i <= k; ++i) {
        cin >> a >> b;
        --ans[a]; ++l[b];
    }
    for (i = 1; i <= n; ++i) for (j = 1; j <= m; ++j)
        if (mat[i][j]) ans[i] += l[j];
    cout << ans[1];
    for (i = 2; i <= n; ++i) cout << ' ' << ans[i];
    cout << '\n';
    return 0;
}