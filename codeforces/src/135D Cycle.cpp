//
// Created by Psy.C on 2025/11/19.
//
/*
 *dx[]和dy[]：四个方向的坐标偏移量（右、下、左、上）
*n, m：网格行数和列数
res：结果
cnt：计数器
id[][]：标记每个点的连通块编号
t：临时计数器
b[][]：存储网格字符的二维数组
f：标志变量
need[][]：标记是否需要处理的布尔数组
 *
 *当前位置(r,c)和颜色标识col
 *更新标志f：如果当前位置在边界上，则设置f为true
 *将当前位置标记为已访问('2')
 *遍历周围8个方向（除了当前位置）
 *计算新位置，如果越界则跳过
 *如果相邻位置是'0'，递归调用DFS
*如果相邻位置是'1'且不属于当前连通块：
标记该位置属于当前连通块
设置need标记为true
计数器cnt增加
 *
 *
 *取消need标记，t计数器增加，tot用于统计相邻相同连通块数量
 *遍历四个基本方向
*如果相邻位置属于同一连通块：
tot计数增加
如果该位置需要处理，递归调用check
 *更新标志f：如果相邻相同连通块数量不等于2，则设置f为true
 *
 *
 *检查是否存在2×2的全'1'方块，如果存在则res设为4
 *
 *
*如果 f == true：由于短路特性，不再计算 tot != 2，直接将 f 设为 true
如果 f == false：计算 tot != 2：
如果 tot == 2：表达式结果为 false，f 被设为 false
如果 tot != 2：表达式结果为 true，f 被设为 true
 */

#include <cstdio>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

const int N = 1005, M = 4,
dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};

int n, m, res, cnt, id[N][N], t;
char b[N][N];
bool f, need[N][N];

void dfs(int r, int c, int col) {
    f = f || r == 0 || r == n - 1 || c == 0 || c == m - 1;
    b[r][c] = '2';
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) if (dr || dc) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (b[nr][nc] == '0') dfs(nr, nc, col);
            else if (b[nr][nc] == '1' && id[nr][nc] != col) {
                id[nr][nc] = col;
                need[nr][nc] = true;
                cnt++;
            }
        }
    }
}

void check(int r, int c) {
    need[r][c] = false; t++; int tot = 0;
    rep(i,M) {
        int nr = r + dy[i], nc = c + dx[i];
        if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
        if (id[nr][nc] == id[r][c]) {
            tot++;
            if (need[nr][nc]) check(nr, nc);
        }
    }
    f = f || tot != 2;
}

int main() {
    scanf("%d %d", &n, &m);
    rep(i,n) rep(j,m) scanf(" %c", &b[i][j]);
    for (int i = 0; i + 2 <= n && !res; ++i) {
        for (int j = 0; j + 2 <= m && !res; ++j) {
            if (b[i][j]=='1'&&b[i][j+1]=='1'&&b[i+1][j]=='1'&&
                b[i+1][j+1]=='1') res=4;
        }
    }
    rep(i,n) rep(j,m) if (b[i][j] == '0') {
        f = false; cnt = 0;
        dfs(i, j, i*m+j);
        if (f || cnt < res) continue;//如果到达边界或计数小于当前结果，则跳过
        f = false; t = 0;//重置标志和计数器
        check(i - 1, j - 1);
        if (!f && t == cnt) res = cnt;//如果没有错误且计数匹配，则更新结果
    }
    printf("%d\n", res);
    return 0;
}