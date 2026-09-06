//
// Created by Psy.C on 2026/9/5.
//
/**
N = 1e3+5：矩阵行列上限（1000+5）。
M = 3e5+5：查询或操作数量上限（300000+5）。
inf = 1e18：无穷大，用于初始化最小值比较
q[N][N][27]：三维前缀和数组。第3维表示颜色编号（1-26）。
q1[N][N]：单维前缀和数组，用于存储不依赖颜色的额外信息。
q2[N][N][27]：三维差分数组。用于记录每个子矩阵内某种颜色出现的次数变化。
a[N][N]：原始字符矩阵，存储为数字（'a'->1, 'b'->2,...）。
xx, yy, xxx, yyy, c：分别存储第 i 个子矩阵的左上角坐标 (xx[i], yy[i])、右下角坐标 (xxx[i], yyy[i])，以及该子矩阵对应的颜色编号 c[i]

n 和 m 分别是矩阵的行数和列数。
k 是接下来要处理的子矩阵（或查询）的数量。
矩阵 a 使用 1-indexed（从1开始计数），这是为了方便后续的前缀和计算
对于每个子矩阵 (xx,yy)-(xxx,yyy)，我们只需要在四个角落进行增减操作。
最终通过前缀和恢复，就能得到每个位置处，各种颜色子矩阵覆盖的次数

对 q2 数组进行二维前缀和恢复，使得 q2[i][j][p] 表示在位置 (i,j) 处，第 p 种颜色的子矩阵覆盖次数
变量解释：
q2[i][j][p]：表示位置 (i,j) 处，颜色 p 的子矩阵覆盖次数。
summ 与 tot：用于累加计算前缀和，以便快速得到所有颜色小于/大于当前颜色的总和。
双向扫描：
第一次 for (p = 1; p <= 26; ++p)：从小到大累加，计算当前颜色左侧（更小颜色）的贡献。
第二次 for (p = 26; p >= 1; --p)：从大到小累加，计算右侧（更大颜色）的贡献。
代价公式：
abs(a[i][j] - p) 表示将当前位置的原始颜色 a[i][j] 改为目标颜色 p 的代价（通常是字母表距离）。
k-tot 表示没有被任何子矩阵覆盖的次数。
q[i][j][p] 累加了所有可能的代价贡献。
q1[i][j] 记录了与当前位置直接相关的代价（仅考虑一次覆盖）
对 q 和 q1 进行二维前缀和处理，使得它们可以支持 O(1) 查询任意子矩阵的总代价
sum(...)：获取子矩阵 (xx[i], yy[i])-(xxx[i], yyy[i]) 中，颜色为 c[i] 的累计代价。
q1[n][m]：整个矩阵的总代价。
sum2(...)：去掉子矩阵内部的普通代价（因为已经在 sum 中计算过了），防止重复统计。
结果：遍历完所有 k 个子矩阵后，输出最小的总代价 mn
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e3+5, M = 3e5+5;
constexpr ll inf = 1e18;

ll q[N][N][27], q1[N][N];
int q2[N][N][27];
//返回子矩阵 (x,y) 到 (u,v) 在第 种颜色上的累计值
ll sum(int x, int y, int u, int v, int col) {
    return q[u][v][col] - q[u][y-1][col] - q[x-1][v][col] + q[x-1][y-1][col];
}
//返回子矩阵 (x,y) 到 (u,v) 的普通累计值（不区分颜色）
ll sum2(int x, int y, int u, int v) {
    return q1[u][v] - q1[u][y-1] - q1[x-1][v] + q1[x-1][y-1];
}

int a[N][N], xx[M], yy[M], xxx[M], yyy[M], c[M];
int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            char ch; cin >> ch;
            a[i][j] = ch - 'a' + 1;//将字符转为数字 (1~26)
        }
    for (int i = 1; i <= k; ++i) {
        cin >> xx[i] >> yy[i] >> xxx[i] >> yyy[i];
        char ch; cin >> ch;
        c[i] = ch - 'a' + 1;
        q2[xx[i]][yy[i]][c[i]]++;
        q2[xxx[i]+1][yyy[i]+1][c[i]]++;
        q2[xxx[i]+1][yy[i]][c[i]]--;
        q2[xx[i]][yyy[i]+1][c[i]]--;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int p = 1; p <= 26; ++p)
                q2[i][j][p] += q2[i-1][j][p] + q2[i][j-1][p] - q2[i-1][j-1][p];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            ll summ = 0, tot = 0;
            for (int p = 1; p <= 26; ++p) {
                q[i][j][p] += summ;
                summ += q2[i][j][p] + tot;
                tot += q2[i][j][p];
            }
            summ = 0, tot = 0;
            for (int p = 26; p >= 1; --p) {
                q[i][j][p] += summ;
                summ += q2[i][j][p] + tot;
                tot += q2[i][j][p];
            }
            for (int p = 1; p <= 26; ++p) {
                q[i][j][p] += (k-tot)*abs(a[i][j]-p);
                q1[i][j] += q2[i][j][p]*abs(a[i][j]-p);
            }
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            for (int p = 1; p <= 26; ++p)
                q[i][j][p] += q[i-1][j][p] + q[i][j-1][p] - q[i-1][j-1][p];
            q1[i][j] += q1[i-1][j] + q1[i][j-1] - q1[i-1][j-1];
        }
    ll mn = inf, y = 0;
    for (int i = 1; i <= k; ++i) {
        ll h = sum(xx[i], yy[i], xxx[i], yyy[i], c[i]) +
            q1[n][m] - sum2(xx[i], yy[i], xxx[i], yyy[i]);
        if (mn > h) { mn = h; y = i; }
    }
    cout << mn;
    return 0;
}