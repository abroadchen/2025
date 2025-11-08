//
// Created by Psy.C on 2025/10/26.
//
/*
*定义三个数组，表示在三维空间中的6个方向移动：
dx: x坐标变化量（前后左右上下）
dy: y坐标变化量（前后左右上下）
dh: h坐标（高度）变化量（前后左右上下）
 *
*k: 高度维度大小
n: 行数
m: 列数
x, y: 起始位置坐标
ans: 计数器，初始化为0
 *声明一个三维字符数组，用于存储空间结构
 *
 *访问当前位置，计数器加1
 *标记当前位置已访问，防止重复访问
 *遍历6个可能的移动方向
 *计算移动后的新坐标
 *检查新位置是否在合法范围内且未被访问过（字符为'.'），如果是则递归调用dfs
 *
 *
 */
#include <ios>
#include <iostream>
#define rep(i,n) for(int i=1;i<=(n);++i)
using namespace std;
const int N = 15;
const int dx[6] = { 0, 0, 0, 0, 1, -1 },
dy[6] = { 0, 0, 1, -1, 0, 0 },
dh[6] = { 1, -1, 0, 0, 0, 0 };

int k, n, m, x, y, ans(0);
char a[N][N][N];

void dfs(int h, int x, int y) {
    ans++;
    a[h][x][y] = '#';
    for (int i = 0; i < 6; ++i) {
        int nh = h + dh[i], nx = x + dx[i], ny = y + dy[i];
        if (nh <= k && nh >= 1 && nx >= 1 && nx <= n && ny >= 1 && ny <= m &&
            a[nh][nx][ny] == '.') dfs(nh, nx, ny);
    }
}



int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> k >> n >> m;
    rep(i,k) rep(j,n) rep(v,m) cin >> a[i][j][v];
    cin >> x >> y;
    dfs(1, x, y);
    cout << ans;
    return 0;
}