//
// Created by Psy.C on 2025/9/25.
//
/*
*常量：N = 105（行数），M = 11（列数）
dp[N][N][M]：动态规划数组，存储状态
a[N][N]：存储输入数据的二维数组
pth和pth2：用于路径回溯的数组
 *
*初始化最后一行（第n行）的dp值
状态：在位置(n,j)，余数为a[n][j]%s时，最大和为a[n][j]
记录路径信息
 *
*从第n行向上进行动态规划
对于每个位置(i,j)和余数k：
可以向左下方移动到(i-1,j-1)（如果不是第一列）
可以向右下方移动到(i-1,j+1)（如果不是最后一列）
更新相应的dp值和路径信息
 *
 *
*在第一行中找余数为0的最大值
如果找不到有效解，输出-1
否则输出最大和
 *
 *
*回溯路径，构造移动方向字符串
'L'表示向左移动，'R'表示向右移动
输出起始列和移动路径
 *
 *
 *dp[i][j][k]表示在位置(i,j)且当前和模s余k时的最大和
 *
 */
#include <cstring>
#include <cstdio>
#include <string>
using namespace std;

typedef long long ll;
const int N = 105, M = 11;
int dp[N][N][M], a[N][N];
int pth[N][N][M], pth2[N][N][M];

inline ll read() {
    ll s(0), w(1);
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (isdigit(ch)) s = s * 10 + ch - '0', ch = getchar();
    return w * s;
}

inline void write(ll x) {//快速输出整数的函数
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x/10);
    putchar(x % 10 + '0');
}

int main() {
    int n = read(), m = read(), s = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            char ch; scanf(" %c", &ch);
            a[i][j] = ch - '0';//读入一个n×m的数字矩阵，存储在数组a中
        }
    ++s;
    memset(dp, -0x3f, sizeof(dp));
    for (int j = 1; j <= m; ++j) {
        dp[n][j][a[n][j] % s] = a[n][j];
        pth[n][j][a[n][j] % s] = j;
        pth2[n][j][a[n][j] % s] = a[n][j];
    }

    for (int i = n; i > 1; --i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 0; k < s; ++k) {
                int x;
                if (j != 1) {
                    x = a[i - 1][j - 1];
                    if (dp[i - 1][j - 1][(k + x) % s] < dp[i][j][k] + x) {
                        dp[i - 1][j - 1][(k + x) % s] = dp[i][j][k] + x;
                        pth[i - 1][j - 1][(k + x) % s] = j;
                        pth2[i - 1][j - 1][(k + x) % s] = k;
                    }
                }
                if (j != m) {
                    x = a[i - 1][j + 1];
                    if (dp[i - 1][j + 1][(k + x) % s] < dp[i][j][k] + x) {
                        dp[i - 1][j + 1][(k + x) % s] = dp[i][j][k] + x;
                        pth[i - 1][j + 1][(k + x) % s] = j;
                        pth2[i - 1][j + 1][(k + x) % s] = k;
                    }
                }
            }
        }
    }

    int ans(-1), id;
    for (int j = 1; j <= m; ++j) {
        if (ans < dp[1][j][0])
            ans = dp[1][j][0], id = j;
    }
    if (ans == -1) {
        write(ans);
        return 0;
    }
    write(ans); putchar('\n');

    int i(1), k(0);
    string path("");
    while (i < n) {
        if (pth[i][id][k] > id) path += 'L';
        else path += 'R';
        int tmp(id);
        id = pth[i][tmp][k];
        k = pth2[i][tmp][k];
        ++i;
    }
    write(id); putchar('\n');

    for (int i = path.size() - 1; i >= 0; --i) putchar(path[i]);
    return 0;
}