//
// Created by Psy.C on 2026/2/28.
//
/**
索引 i | dx[i] | dy[i] | 新位置          | 方向
------|-------|-------|----------------|-------
0     |   0   |   0   | (x+0, y+0)     | 当前位置（原地）
1     |   1   |   0   | (x+1, y+0)     | 向右
2     |  -1   |   0   | (x-1, y+0)     | 向左
3     |   0   |  -1   | (x+0, y-1)     | 向上
4     |   0   |   1   | (x+0, y+1)     | 向下
5     |  -1   |  -1   | (x-1, y-1)     | 左上对角
6     |  -1   |   1   | (x-1, y+1)     | 左下对角
7     |   1   |  -1   | (x+1, y-1)     | 右上对角
8     |   1   |   1   | (x+1, y+1)     | 右下对角


dx[], dy[]：方向数组，前5个元素表示上下左右四个方向
deg[N][N]：每个位置的度数（相邻可通行格子数量）
vis[N][N]：访问标记数组
q：BFS队列

减少相邻位置的度数
如果相邻位置仍有访问标记且度数变为1，将其加入队列

读入网格，'.'表示可通行，其他字符表示障碍
设置访问标记，统计障碍物数量
对每个可通行位置，计算相邻可通行位置的数量（度数）
如果度数为1，加入队列（叶节点）
BFS处理度数为1的节点（类似拓扑排序）
找到相邻的可通行节点，建立配对关系
根据方向设置箭头字符（'^','v','>','<'配对）
将配对的两个位置标记为已访问（false）
更新相邻节点的度数
cnt += 2：处理了两个格子

如果处理的格子数等于总格子数，输出修改后的网格
否则输出"Not unique"（表示无法唯一配对）
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e3+100;
struct node { int x, y; };

int dx[] = {0,1,-1,0,0,-1,-1,1,1}, dy[] = {0,0,0,-1,1,-1,1,-1,1};
int deg[N][N];
bool vis[N][N];
queue<node> q;
void get(const int x, const int y) {
    for (int i = 1; i <= 4; ++i) {
        const int x1 = x + dx[i], y1 = y + dy[i];
        deg[x1][y1]--;
        if (vis[x1][y1] && deg[x1][y1] == 1)
            q.push({x1, y1});
    }
}

int n, m;
char s[N][N];
int main() {
    scanf("%d", &n), scanf("%d", &m);
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= m; ++j) {
            if (s[i][j] == '.') vis[i][j] = true;
            else vis[i][j] = false, cnt++;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) if (vis[i][j]) {
            int num = 0;
            for (int k = 1; k <= 4; ++k)
                num += vis[i+dx[k]][j+dy[k]];
            deg[i][j] = num;
            if (deg[i][j] == 1) q.push({i, j});
        }
    while (!q.empty()) {
        const int x0 = q.front().x, y0 = q.front().y; q.pop();
        for (int i = 1; i <= 4; ++i) {
            if (int x = x0 + dx[i], y = y0 + dy[i]; vis[x][y]) {
                if (i == 1) s[x0][y0] = '^', s[x][y] = 'v';
                if (i == 2) s[x0][y0] = 'v', s[x][y] = '^';
                if (i == 3) s[x0][y0] = '>', s[x][y] = '<';
                if (i == 4) s[x0][y0] = '<', s[x][y] = '>';
                vis[x][y] = vis[x0][y0] = false;
                get(x, y), get(x0, y0);
                cnt += 2;
                break;
            }
        }
    }
    if (cnt == n*m) {
        for (int i = 1; i <= n; ++i)
            puts(s[i] + 1);
    } else puts("Not unique");
    return 0;
}