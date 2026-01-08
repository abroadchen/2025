//
// Created by Psy.C on 2026/1/8.
//
/**
* w函数：计算矩形区域[r1,c1]到[r2,c2]的元素和
使用二维前缀和公式计算矩形区域和
a[r2][c2]：右下角前缀和
- a[r2][c1-1] - a[r1-1][c2]：减去多余部分
+ a[r1-1][c1-1]：加上被减去两次的部分
 *
 *矩阵大小n、操作次数k、DP数组f
 *
*状态转移：f[i][j]表示用i次操作处理前j个元素的最小代价
复杂度优化：从O(kn²)优化到O(kn log n)
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 4005
using namespace std;
//如果a > b，则将a更新为b并返回true，否则返回false
template<typename T> bool minn(T& a, const T& b) { return a > b ? a = b, true : false; }

int a[N][N];//存储前缀和
int w(const int r1, const int c1, const int r2, const int c2) {
    return a[r2][c2] - a[r2][c1-1] - a[r1-1][c2] + a[r1-1][c1-1];
}
//计算从l到r的区间和 矩形[l,l]到[r,r]，即对角线上的区间
int w(const int l, const int r) { return w(l, l, r, r) >> 1; }

/**
 *
 * @param h 当前层的DP数组
 * @param g 上一层的DP数组
 * @param L 当前处理区间的左右边界
 * @param R
 * @param l 决策的左右边界
 * @param r
 */
void dfs(int *h, const int *g, const int L, const int R, const int l, const int r) {
    const int mid = (L + R) >> 1; int k = l;//记录最优决策点
    h[mid] = g[k-1] + w(k, mid);
    for (int i = l + 1; i <= min(r, mid); ++i)//尝试其他决策点
        if (minn(h[mid], g[i-1] + w(i, mid))) k = i;//更新最优决策点k
    if (L < mid) dfs(h, g, L, mid - 1, l, k);//递归处理左半部分
    if (R > mid) dfs(h, g, mid + 1, R, k, r);
}


int main() {
    fast;
    int n, k, f[N][N]; cin >> n >> k;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
        a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    }
    for (int i = 0; i <= k; ++i) memset(f[i], 0x3f, (n+1) * sizeof(int));//每行有n+1个元素
    f[0][0] = 0;//0次操作处理0个元素的代价为0
    for (int i = 1; i <= k; ++i) dfs(f[i], f[i-1], 1, n, 1, n);
    cout << f[k][n] << '\n';
    return 0;
}