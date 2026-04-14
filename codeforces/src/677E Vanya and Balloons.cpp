//
// Created by Psy.C on 2026/4/14.
//
/**
a, b: 两个网格数组
row, col: 前缀和数组，统计2和3的个数
L, R, U, D: 每个位置到最近障碍物的距离
vis: 访问标记
lg2, lg3: 2和3的自然对数
cmp: 比较函数，用于比较2^a.fi * 3^a.se 和 2^b.fi * 3^b.se
查询行区间[l,r]中op类型的数字个数
查询列区间[l,r]中op类型的数字个数

构建L,U数组：向左/向上最近障碍物的位置
构建前缀和数组：统计2和3的个数
向右/向下最近障碍物的位置
对每个有效位置(i,j)：
d: 以(i,j)为中心能扩展的最大距离
计算菱形区域内2和3的个数
减去中心点的贡献
更新最优解

读入n×n网格
检查是否全为0
将原始坐标(i,j)变换为(i-j+n, i+j+n)
这相当于将网格旋转45度
计算菱形边界
将超出菱形的区域设为0
比较两种情况的结果
输出最优解对应的数值

 */
#include <bits/stdc++.h>
#define ii pair<int, int>
#define ld long double
#define fi first
#define se second
#define mk make_pair
using namespace std;
constexpr int N = 3e3+5, mod = 1e9+7;

int power(int a, int b) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = 1LL * ans * a % mod;
        a = 1LL * a * a % mod; b >>= 1;
    }
    return ans;
}

int n, a[N][N], b[N][N];
short row[N][N][2], col[N][N][2];
short L[N][N], R[N][N], U[N][N], D[N][N];
bool vis[N][N];

ld lg2 = logl(2), lg3 = logl(3);

bool cmp(const ii& a, const ii& b) {
    return a.fi * lg2 + a.se * lg3 < b.fi * lg2 + b.se * lg3;
}

inline int calcRow(int i, int l, int r, int op) {
    return row[i][r][op] - row[i][l][op];
}
inline int calcCol(int j, int l, int r, int op) {
    return col[j][r][op] - col[j][l][op];
}

ii calc(int a[N][N], int n) {
    ii ans = mk(0, 0);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!a[i][j]) L[i][j] = j, U[i][j] = i;
            else L[i][j] = L[i][j - 1], U[i][j] = U[i - 1][j];
            row[i][j][0] = row[i][j - 1][0] + (a[i][j] == 2);
            row[i][j][1] = row[i][j - 1][1] + (a[i][j] == 3);
            col[j][i][0] = col[j][i - 1][0] + (a[i][j] == 2);
            col[j][i][1] = col[j][i - 1][1] + (a[i][j] == 3);
        }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = n; j >= 1; j--) {
            if(!a[i][j]) R[i][j] = j, D[i][j] = i;
            else {
                if(j == n) R[i][j] = j + 1;
                else R[i][j] = R[i][j + 1];
                if(i == n) D[i][j] = i + 1;
                else D[i][j] = D[i + 1][j];
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!a[i][j] || !vis[i][j]) continue;
            int d = min({i - U[i][j], D[i][j] - i, j - L[i][j], R[i][j] - j});
            ii tmp = mk(0, 0);
            tmp.fi += calcRow(i, j - d, j + d - 1, 0);
            tmp.fi += calcCol(j, i - d, i + d - 1, 0);
            tmp.se += calcRow(i, j - d, j + d - 1, 1);
            tmp.se += calcCol(j, i - d, i + d - 1, 1);
            if(a[i][j] == 2) tmp.fi--;
            else if(a[i][j] == 3) tmp.se--;
            if(cmp(ans, tmp)) {
                ans = tmp;
            }
        }
    }
    return ans;
}

int main() {
    int mask = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            scanf("%1d", &a[i][j]), vis[i][j] = true, mask |= a[i][j];
    if(!mask) return puts("0"), 0;
    ii ret1 = calc(a, n);
    for(int i = 1; i <= 3 * n; i++)
        for(int j = 1; j <= 3 * n; j++)
            b[i][j] = 1, vis[i][j] = false;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            b[i - j + n][i + j + n] = a[i][j], vis[i - j + n][i + j + n] = true;
    int lx = 1 - 1 + n, ly = 1 + 1 + n;
    int rx = n - n + n, ry = n + n + n;
    int x = (lx + rx) / 2, y = (ly + ry) / 2;
    int d = abs(x - lx) + abs(y - ry);
    for(int i = 1; i <= 3 * n; i++)
        for(int j = 1; j <= 3 * n; j++)
            if(abs(i - x) + abs(j - y) > d)
                b[i][j] = 0;
    ii ret2 = calc(b, 3 * n);
    if(cmp(ret1, ret2)) {
        printf("%d\n", 1LL * power(2, ret2.fi) * power(3, ret2.se) % mod);
    } else {
        printf("%d\n", 1LL * power(2, ret1.fi) * power(3, ret1.se) % mod);
    }
    return 0;
}