//
// Created by Psy.C on 2026/1/8.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 18000005
using namespace std;

int fa[N], dep[N];//用于按秩合并优化
void init(const int n) {
    for (int i = 0; i < n; ++i) {
        fa[i] = i; dep[i] = 0;
    }
}

int n, m, dx[] = {
    -1, -1, -1, 0, 0, 1, 1, 1//上左、上、上右、左、右、下左、下、下右
}, dy[] = {
    -1, 0, 1, -1, 1, -1, 0, 1
};
bool ok(const int x, const int y) {
    return x >= 1 && x <= n && y >= 1 && y <= 2 * m;
}

int find(const int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool same(const int x, const int y) { return find(x) == find(y); }//两个节点是否在同一集合 两节点的根节点是否相同
int idx(const int x, const int y) { return (x - 1) * 2 * m + y; }

bool vis[3005][6005];
int solve(const int x, const int y) {//在位置(x,y)放置元素是否合法
    const int x2 = x, y2 = y + m;//镜像位置
    for (int i = 0; i < 8; ++i) {//检查8个相邻位置
        const int x1 = x + dx[i]; int y1 = y + dy[i];//相邻位置
        if (y1 < 1) y1 += 2 * m; else if (y1 > 2 * m) y1 -= 2 * m;//处理边界环绕（圆柱面）
        if (ok(x1, y1) && vis[x1][y1]) {//相邻位置有效且已访问
            for (int j = 0; j < 8; ++j) {//检查镜像位置的8个相邻位置
                if (const int x3 = x2 + dx[j], y3 = y2 + dy[j]; ok(x3, y3) && vis[x3][y3]) {
                    if (same(idx(x3, y3), idx(x1, y1))) return 0;//发现冲突
                }
            }
        }
    }
    return 1;
}

void unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (dep[x] < dep[y]) fa[x] = y; else {
        fa[y] = x;
        if (dep[x] == dep[y]) dep[x]++;//合并后深度+1
    }
}

int main() {
    fast;
    int q, ans = 0; cin >> n >> m >> q;
    if (m == 1) return cout << "0\n", 0;
    init(2 * n * m + 3);
    const int mx = 2 * m;//最大列数
    while (q--) {
        int x, y; cin >> x >> y;
        if (solve(x, y)) {//如果位置合法
            vis[x][y] = vis[x][y+m] = true;//标记位置及其镜像位置
            ++ans;
            for (int i = 0; i < 8; ++i) {//遍历8个相邻方向
                const int x1 = x + dx[i]; int y1 = y + dy[i];//计算相邻位置
                if (y1 <= 0) y1 += mx; else if (y1 > mx) y1 -= mx;
                if (ok(x1, y1) && vis[x1][y1]) unite(idx(x, y), idx(x1, y1));//连接原位置 合并它们
                y1 += m;//镜像位置的y坐标
                if (y1 <= 0) y1 += mx; else if (y1 > mx) y1 -= mx;
                if (ok(x1, y1) && vis[x1][y1]) unite(idx(x, y+m), idx(x1, y1));//连接镜像位置
            }
        }
    }
    cout << ans << '\n';
    return 0;
}