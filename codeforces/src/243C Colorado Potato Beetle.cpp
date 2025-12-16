//
// Created by Psy.C on 2025/12/15.
//
/*
*ax[], ay[]: 存储所有关键点的x坐标和y坐标
cx, cy: 当前位置坐标
px[], py[]: 存储每一步的位置坐标
c[][]: 二维网格状态数组
 *
*将点(x,y)及其相邻的8个点的坐标添加到坐标数组中
ax[0]和ay[0]作为计数器使用，记录已存储坐标的数量
每个坐标点都会存储它本身以及前后左右的坐标值
 *
*在排序后的ax数组中查找值x应该插入的位置，返回其离散化后的索引
使用二分查找优化查找效率
 *
*标记外部区域
如果越界或者当前位置已被访问，则返回
将当前位置标记为2（表示外部区域）
递归访问四个方向的相邻格子
 *
 *将初始位置(0,0)附近的点加入坐标集合
*循环处理n次移动指令
根据字符(R/L/U/D)更新当前坐标
记录每步到达的位置
将新位置附近的点加入坐标集合
*对x坐标和y坐标分别进行排序和去重
实现坐标离散化，减少后续处理的数据规模
 *
*遍历每一条线段，在离散化后的网格中标记路径
如果是垂直线段(sx==ex)，则标记对应列的一段
如果是水平线段(sy==ey)，则标记对应行的一段
标记值1表示路径上的点
 *
 *从(1,1)开始深度优先搜索，标记所有外部区域为2
*计算被围住区域的面积
遍历所有网格点，如果该点不是外部区域(c[i][j]^2为真)
则累加该网格的实际面积：(ax[i]-ax[i-1])*(ay[j]-ay[j-1])
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 3010
using namespace std;

int ax[N], ay[N], cx, cy, px[N], py[N], c[N][N];
void add(const int x, const int y) {
    ax[++ax[0]] = x - 1; ax[++ax[0]] = x + 1; ax[++ax[0]] = x;
    ay[++ay[0]] = y - 1; ay[++ay[0]] = y + 1; ay[++ay[0]] = y;
}
int fx(const int x) {
    return static_cast<int>(lower_bound(ax + 1, ax + ax[0] + 1, x) - ax + 1);
}
int fy(const int y) {
    return static_cast<int>(lower_bound(ay + 1, ay + ay[0] + 1, y) - ay + 1);
}

void dfs(const int x, const int y) {
    if (x < 1 || x > ax[0] + 1 || y < 1 || y > ay[0] + 1 || c[x][y]) return;
    c[x][y] = 2;
    dfs(x + 1, y); dfs(x, y + 1); dfs(x - 1, y); dfs(x, y - 1);
}

int main() {
    fast;
    int n; cin >> n;
    add(cx, cy);
    for (int i = 1, len; i <= n; ++i) {
        char ch; cin >> ch >> len;
        if (ch == 'R') cy += len;
        if (ch == 'L') cy -= len;
        if (ch == 'U') cx += len;
        if (ch == 'D') cx -= len;
        px[i] = cx; py[i] = cy;
        add(cx, cy);
    }
    sort(ax + 1, ax + ax[0] + 1);
    ax[0] = static_cast<int>(unique(ax + 1, ax + ax[0] + 1) - ax - 1);
    sort(ay + 1, ay + ay[0] + 1);
    ay[0] = static_cast<int>(unique(ay + 1, ay + ay[0] + 1) - ay - 1);
    for (int i = 1; i <= n; ++i) {
        int sx = fx(px[i-1]), sy = fy(py[i-1]), ex = fx(px[i]), ey = fy(py[i]);
        if (sx == ex) {
            for (int j = min(sy, ey); j <= max(sy, ey); ++j)
                c[sx][j] = 1;
        }
        if (sy == ey) {
            for (int j = min(sx, ex); j <= max(sx, ex); ++j)
                c[j][sy] = 1;
        }
    }
    dfs(1, 1);
    ll ans = 0;
    for (int i = 1; i <= ax[0]; ++i) for (int j = 1; j <= ay[0]; ++j) {
        if (c[i][j] ^ 2) ans += 1ll * (ax[i] - ax[i-1]) * (ay[j] - ay[j-1]);
    }
    cout << ans << '\n';
    return 0;
}