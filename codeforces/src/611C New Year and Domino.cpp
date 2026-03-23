//
// Created by Psy.C on 2026/3/23.
//
/**
h, w：网格的高度和宽度
a[N][N]：转换后的网格（1表示'.'，0表示其他字符）
b[N][N]：存储竖直相邻对的前缀和
c[N][N]：存储水平相邻对的前缀和
q：查询数量
将字符网格转换为数字网格：'.'记为1，其他记为0
b[i][j]：从(1,1)到(i,j)矩形区域内，竖直方向相邻的白格子对数
c[i][j]：从(1,1)到(i,j)矩形区域内，水平方向相邻的白格子对数
如果当前位置和上方都是白格子，则b[i][j]++
如果当前位置和左侧都是白格子，则c[i][j]++

使用二维前缀和查询矩形区域内的相邻对数量：
第一部分：b[xb][yb] + b[xa][ya-1] - b[xa][yb] - b[xb][ya-1] - 竖直相邻对
第二部分：c[xb][yb] + c[xa-1][ya] - c[xb][ya] - c[xa-1][yb] - 水平相邻对

时间复杂度：
预处理：O(hw)
查询：O(q)
总体：O(hw + q)
空间复杂度：
O(hw)，用于存储多个二维数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;
constexpr int N = 505;
int h, w, a[N][N], b[N][N], c[N][N], q, xa, ya, xb, yb;
char s[N][N];
int main() {
    fast;
    cin >> h >> w;
    rep(i,h) rep(j,w) cin >> s[i][j];
    rep(i,h) rep(j,w) {
        if (s[i][j] == '.') a[i][j] = 1;
        else a[i][j] = 0;
    }
    rep(i,h) rep(j,w) {
        b[i][j] = b[i][j-1] + b[i-1][j] - b[i-1][j-1];
        c[i][j] = c[i][j-1] + c[i-1][j] - c[i-1][j-1];
        if (a[i][j]) {
            if (a[i-1][j]) b[i][j]++;
            if (a[i][j-1]) c[i][j]++;
        }
    }
    cin >> q;
    while (q--) {
        cin >> xa >> ya >> xb >> yb;
        cout << b[xb][yb] + b[xa][ya-1] - b[xa][yb] - b[xb][ya-1] +
            c[xb][yb] + c[xa-1][ya] - c[xb][ya] - c[xa-1][yb] << '\n';
    }
    return 0;
}