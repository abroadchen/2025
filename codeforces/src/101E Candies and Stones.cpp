//
// Created by Psy.C on 2025/11/12.
//
/*
*n, m：两个序列的长度
p：模数
x[N], y[N]：两个输入序列
pos[N]：记录路径位置
ans：最终路径字符串
f, g：两个辅助数组，用于动态规划
 *
*分治递归函数：
(sx, sy)：起始点坐标
(tx, ty)：终点坐标
如果起始点和终点在同一行，记录路径位置并返回
 *
*前向DP：从起始区域到中间行：
对于每一行i从sx到mid
对于每一列j从sy到ty
f[j]表示到达位置(i,j)的最大值
状态转移：从上方或左方转移，加上当前位置的权重
*后向DP：从终点区域到中间行：
对于每一行i从tx到mid+1（逆序）
对于每一列j从ty到sy（逆序）
g[j]表示从位置(i,j)到终点的最大值
状态转移：从下方或右方转移，加上当前位置的权重
*遍历中间行的所有列
找到使f[i] + g[i]最大的位置
这个位置就是从起点到终点的必经之路
*分治处理两个子区域
第一个子问题：从(sx,sy)到(mid,p)
第二个子问题：从(mid+1,p)到(tx,ty)
 *
*路径构造：
如果只有一行，全部是'S'
否则使用分治算法找到最优路径
根据pos数组构造路径字符串：
'S'表示向右移动
'C'表示向下移动
 *
 *
 *O(n×m×log n)：分治层数为log n，每层需要O(n×m)时间
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 2e4+5;
int n, m, p, x[N], y[N], pos[N];
string ans;
array<int, N> f, g;

int add(int x, int y) { return x + y >= p ? x + y - p : x + y; }//避免结果超过p
void dfs(int sx, int sy, int tx, int ty) {
    if (sx == tx) { pos[tx] = ty; return; }
    int mid = (sx + tx) / 2;
    f.fill(0), g.fill(0);
    for (int i = sx; i <= mid; ++i) {
        for (int j = sy; j <= ty; ++j) {
            f[j] = max(f[j], f[j - 1]) + add(x[i], y[j]);
        }
    }
    for (int i = tx; i > mid; --i) {
        for (int j = ty; j >= sy; --j) {
            g[j] = max(g[j], g[j + 1]) + add(x[i], y[j]);
        }
    }
    int mx(-1), p(0);
    for (int i = sy; i <= ty; ++i) {
        if (f[i] + g[i] > mx) mx = f[i] + g[i], p = i;
    }
    dfs(sx, sy, mid, p);
    dfs(mid + 1, p, tx, ty);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    for (int i = 0; i < n; ++i) cin >> x[i], x[i] %= p;
    for (int i = 0; i < m; ++i) cin >> y[i], y[i] %= p;
    if (n == 1) ans.resize(m - 1, 'S');
    else {
        pos[0] = 0, pos[n - 1] = m - 1;
        dfs(0, 0, n - 1, m - 1);
        int t = 0;
        for (int i = 0; i < n; ++i) {
            while (t < pos[i]) ans += 'S', ++t;
            if (i != n - 1) ans += 'C';
        }
    }
    int res = add(x[0], y[0]), X(0), Y(0);
    for (auto c : ans) {
        if (c == 'C') ++X;
        if (c == 'S') ++Y;
        res += add(x[X], y[Y]);
    }
    cout << res << '\n' << ans << '\n';
    return 0;
}