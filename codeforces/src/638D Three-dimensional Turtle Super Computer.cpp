//
// Created by Psy.C on 2026/3/31.
//
/**
a[N][N][N]：三维字符数组，存储3D网格的状态（'1'表示占用，'0'表示空）
在三维网格中寻找从 cur 到 t 的路径
终止条件：当前位置等于目标位置
扩展方向：每次沿一个维度增加1单位
约束条件：只能移动到值为'1'的位置
结构化绑定：使用 auto [x, y, z] = tmp 解包坐标

n, m, l：三维网格的尺寸
dx[], dy[], dz[]：六个方向的偏移量（前后左右上下）
ans：答案计数器
读入三维网格尺寸
读入每个平面的字符数据
遍历所有值为'1'的位置
收集当前点的6个相邻方向上值也为'1'的点

遍历相邻点对，检查是否存在可移除的点
cnt[p] <= cnt[q]：检查坐标分量的偏序关系
关键逻辑：
临时将中心点设置为'0'
测试相邻两点之间是否仍存在路径
如果路径不存在，则说明当前点是连接这两点的关键点
恢复中心点为'1'
设置 flag = true 表示当前点不能被移除

 */
#include <bits/stdc++.h>
#define ai array<int,3>///三维坐标
using namespace std;
constexpr int N = 105;

char a[N][N][N];
bool dfs(const ai& cur, const ai& t) {
    if (cur == t) return true;
    for (int i = 0; i < 3; ++i)
        if (cur[i] < t[i]) {
            auto tmp = cur; ++tmp[i];
            if (auto [x, y, z] = tmp; a[x][y][z] == '1' && dfs(tmp, t))
                return true;
        }
    return false;
}

int n, m, l, dx[] = {1, 0, -1, 0, 0, 0}, dy[] = {0, 1, 0, -1, 0, 0},
dz[] = {0, 0, 0, 0, 1, -1}, ans;
int main() {
    scanf("%d%d%d", &n, &m, &l);
    int i, j, k, p, q;
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%s", a[i][j]+1);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            for (k = 1; k <= l; ++k) if (a[i][j][k] == '1') {
                vector<ai> cnt; bool flag = false;
                for (p = 0; p < 6; ++p) {
                    int nx = i + dx[p], ny = j + dy[p], nz = k + dz[p];
                    if (nx < 1 || nx > n || ny < 1 || ny > m || nz < 1 || nz > l) continue;
                    if (a[nx][ny][nz] == '1') cnt.push_back({nx, ny, nz});
                }
                for (p = 0; p < cnt.size() && !flag; ++p)
                    for (q = 0; q < cnt.size() && !flag; ++q)
                        if (p != q && cnt[p][0] <= cnt[q][0] && cnt[p][1] <= cnt[q][1] &&
                            cnt[p][2] <= cnt[q][2] && dfs(cnt[p], cnt[q])) {
                            a[i][j][k] = '0';
                            if (!dfs(cnt[p], cnt[q])) flag = true;
                            a[i][j][k] = '1';
                        }
                ans += flag;
            }
    return printf("%d", ans), 0;
}