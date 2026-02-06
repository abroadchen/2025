//
// Created by Psy.C on 2026/2/6.
//
/**
第一个条件：(dx[w] == 0 || f[xq][yq][w] > (xp-xq)/dx[w])
检查x轴方向的可行性：

dx[w] == 0: 如果w方向在x轴上没有分量（垂直移动）
f[xq][yq][w] > (xp-xq)/dx[w]: 从Q点沿w方向到障碍物的距离 > Q到P在x轴上的投影距离
第二个条件：(dy[w] == 0 || f[xq][yq][w] > (yp-yq)/dy[w])
检查y轴方向的可行性：

dy[w] == 0: 如果w方向在y轴上没有分量（水平移动）
f[xq][yq][w] > (yp-yq)/dy[w]: 从Q点沿w方向到障碍物的距离 > Q到P在y轴上的投影距离
几何意义
这两个条件一起验证：从Q点(xq,yq)沿w方向移动到P点(xp,yp)的路径是否畅通无阻

dx[w] == 0 保护：当w方向在x轴上无分量时，跳过除法运算
dy[w] == 0 保护：当w方向在y轴上无分量时，跳过除法运算

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 405
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

int dx[] = {
    0, -1, -1, -1, 0, 1, 1, 1
}, dy[] = {
    -1, -1, 0, 1, 1, 1, 0, -1
};

int main() {
    fast;
    //从每个位置沿8个方向到障碍物的距离
    int n, m, i, j, a[N][N]{}, f[N][N][8]{}, ans = 0; cin >> n >> m;
    char ch;
    rep(i,n) rep(j,m) {
        cin >> ch;
        a[i][j] = ch - '0';
    }
    //从每个位置(i,j)沿前4个方向(k=0,1,2,3)到第一个障碍物(值为1)的距离
    rep(i,n) rep(j,m) for (int k = 0; k < 4; ++k) {
        int x = i, y = j;
        while (x > 0 && x <= n && y > 0 && y <= m && a[x][y] == 0)
            x += dx[k], y += dy[k];
        f[i][j][k] = i - x != 0 ? i - x : j - y;
    }
    rep(i,n) rep(j,m) if (a[i][j] == 0) {//只处理值为0的位置
        for (int k = 0; k < 8; ++k) {
            const int l = (k+2)%8, w = (k+3)%4;
            for (int t = 1; t < min(n, m); ++t) {//枚举距离t
                ///从(i,j)沿k方向移动t步后的位置P
                ///从(i,j)沿l方向移动t步后的位置Q
                const int xp = i + t*dx[k], yp = j + t*dy[k],
                xq = i + t*dx[l], yq = j + t*dy[l];
                if (xp<=0||xp>n||yp<=0||yp>m||xq<=0||xq>n||yq<=0||yq>m)
                    break;
                if (a[xp][yp] == 1 || a[xq][yq] == 1) break;//是障碍物
                if (k >= 1 && k <= 4) {
                    //在w方向上是否有足够的空间
                    ///dx[w] == 0，表示w方向是垂直方向（上下移动，x坐标不变）
                    ///f[xq][yq][w]: 从位置(xq,yq)沿w方向到最近障碍物的距离
                    ///(xp-xq)/dx[w]: 计算从Q点到P点在w方向上所需的距离
                    if ((dx[w] == 0 || f[xq][yq][w] > (xp-xq)/dx[w]) &&
                        (dy[w] == 0 || f[xq][yq][w] > (yp-yq)/dy[w]))
                        ans++;
                } else {
                    if ((dx[w] == 0 || f[xp][yp][w] > (xq-xp)/dx[w]) &&
                        (dy[w] == 0 || f[xp][yp][w] > (yq-yp)/dy[w]))
                        ans++;
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}