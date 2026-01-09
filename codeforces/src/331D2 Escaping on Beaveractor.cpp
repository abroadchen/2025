//
// Created by Psy.C on 2026/1/9.
//
/**
* dx[]: x 方向移动量数组，索引 0-4 对应：不动、右、左、下、上
dy[]: y 方向移动量数组，索引 0-4 对应：不动、上、下、不动、不动
实际方向为：dx[1]=0,dy[1]=1（右），dx[2]=0,dy[2]=-1（左），dx[3]=1,dy[3]=0（下），dx[4]=-1,dy[4]=0（上）
 *
 *f[2][5][N][N]: 4维数组，用于倍增算法，[奇偶层][方向][x坐标][y坐标]
 *
 *位置、方向和时间
*n: 线段数量
b: 网格边界
m: 查询数量
a[N][N]: 网格数组，存储特殊方向信息
mp[256]: 字符到方向的映射数组
 *
*循环处理 n 条线段
x, y, X, Y: 线段起点和终点坐标
如果是水平线段 (x == X)：
y < Y: 从左到右，设置方向 1 (右)
否则从右到左，设置方向 2 (左)
如果是垂直线段：
x < X: 从上到下，设置方向 3 (下)
否则从下到上，设置方向 4 (上)
*双重循环遍历所有网格位置 (i,j)
内层循环遍历所有方向 k
计算从位置 (i,j) 沿方向 k 移动一步后的新位置 (nx, ny)
边界检查，确保新位置在 [0,b] 范围内
nd: 新方向，如果新位置有特殊方向则使用，否则保持原方向
存储到 f[0][k][i][j] 中
 *
 *
*遍历所有查询
定义常量 x, y, d, t 从当前查询
检查时间的最低位是否对应当前 2^s
如果是，则执行一次跳跃操作
从倍增表获取跳跃结果
更新查询的位置、方向和时间
 *
*如果不是最后一层，构建下一层倍增表
四重循环遍历所有 (方向, x坐标, y坐标) 组合
先走一步：f[s&1][k][i][j]
再走一步：f[s&1][nd][nx][ny]
结果存入下一层：f[(s+1)&1][k][i][j]
 *
*遍历所有查询
输出每个查询的最终位置坐标
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1005
using namespace std;

ll low_bit(const ll x) { return x & (-x); }

constexpr int dx[] = {0, 0, 0, 1, -1}, dy[] = {0, 1, -1, 0, 0};
struct node { int x, y, d; } f[2][5][N][N];
struct node2 { int x, y, d; ll t; } q[N*100];

int main() {
    fast;
    int n, b, m, a[N][N], mp[256]; cin >> n >> b;
    mp['U'] = 1, mp['D'] = 2, mp['R'] = 3, mp['L'] = 4;
    for (int i = 1, x, y, X, Y; i <= n; ++i) {
        cin >> x >> y >> X >> Y;
        if (x == X) {
            if (y < Y) for (int j = y; j <= Y; ++j) a[x][j] = 1;
            else for (int j = Y; j <= y; ++j) a[x][j] = 2;
        } else {
            if (x < X) for (int j = x; j <= X; ++j) a[j][y] = 3;
            else for (int j = X; j <= x; ++j) a[j][y] = 4;
        }
    }
    for (int i = 0; i <= b; ++i) for (int j = 0; j <= b; ++j) {
        for (int k = 1; k <= 4; ++k) {
            int nx = i + dx[k], ny = j + dy[k], nd;
            nx = max(nx, 0); nx = min(nx, b);
            ny = max(ny, 0); ny = min(ny, b);
            if (a[nx][ny]) nd = a[nx][ny]; else nd = k;
            f[0][k][i][j] = {nx, ny, nd};
        }
    }
    cin >> m; ll t;
    for (int i = 1, x, y; i <= m; ++i) {
        char c;
        cin >> x >> y >> c;
        int d = mp[c];
        if (a[x][y]) d = a[x][y];
        cin >> t;
        q[i] = {x, y, d, t};
    }
    for (int s = 0; s <= 50; ++s) {
        for (int i = 1; i <= m; ++i) {
            if (const int x = q[i].x, y = q[i].y, d = q[i].d;
                low_bit(q[i].t) == 1ll << s) {
                auto [x1, y1, d1] = f[s&1][d][x][y];
                q[i].x = x1; q[i].y = y1; q[i].d = d1;
                q[i].t -= low_bit(q[i].t);
            }
        }
        if (s != 50) {
            for (int k = 1; k <= 4; ++k) {
                for (int i = 0; i <= b; ++i) {
                    for (int j = 0; j <= b; ++j) {
                        auto tmp = f[s&1][k][i][j];
                        const int nx = tmp.x, ny = tmp.y, nd = tmp.d;
                        tmp = f[s&1][nd][nx][ny];
                        f[(s+1)&1][k][i][j] = tmp;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= m; ++i) cout << q[i].x << ' ' << q[i].y << '\n';
    return 0;
}