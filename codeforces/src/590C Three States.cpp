//
// Created by Psy.C on 2026/3/18.
//
/**
n, m: 地图的行数和列数
d[5][N][N]: 三维距离数组，d[type][x][y]表示类型type到点(x,y)的距离
dx[], dy[]: 四个方向的偏移量（右、左、下、上）
s[N][N]: 地图字符数组
bfs(id): 从类型id的所有点开始的BFS
使用双端队列实现0-1 BFS
将地图中所有值为id的点加入队列，距离设为0
遍历四个方向
检查边界和障碍物('#')
flag: 判断下一个位置是否为空地('.')
如果通过当前点能获得更短距离，更新距离
如果下一位置是空地(代价为1)，加入队尾
如果下一位置是数字(代价为0)，加入队首
这是0-1 BFS的标准实现

对类型1,2,3分别进行BFS，计算到所有点的距离
遍历所有点，寻找三点汇合的最优位置
如果某点无法到达三种类型之一，跳过
如果该点是空地('.')，由于重复计算了两次空地的代价，需要减2
否则直接相加三类距离
时间复杂度：O(3×n×m)，空间复杂度：O(n×m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005, inf = 0x3f3f3f3f;

struct node { int x, y; };

int n, m, d[5][N][N], dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};
char s[N][N];
void bfs(int id) {
    deque<node> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (s[i][j] - '0' == id) {
                d[id][i][j] = 0;
                q.push_back({i, j});
            }
    while (!q.empty()) {
        node u = q.front(); q.pop_front();
        for (int i = 0; i < 4; ++i) {
            int tx = u.x + dx[i], ty = u.y + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m || s[tx][ty] == '#')
                continue;
            int flag = s[tx][ty] == '.';
            if (d[id][tx][ty] > d[id][u.x][u.y] + flag) {
                d[id][tx][ty] = d[id][u.x][u.y] + flag;
                flag ? q.push_back({tx, ty}) : q.push_front({tx, ty});
            }
        }
    }
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> s[i];
    memset(d, inf, sizeof d);
    for (int i = 1; i <= 3; ++i) bfs(i);
    int ans = inf;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (d[1][i][j] == inf || d[2][i][j] == inf || d[3][i][j] == inf)
                continue;
            if (s[i][j] == '.')
                ans = min(ans, d[1][i][j]+d[2][i][j]+d[3][i][j]-2);
            else
                ans = min(ans, d[1][i][j]+d[2][i][j]+d[3][i][j]);
        }
    if (ans == inf) ans = -1;
    cout << ans << '\n';
    return 0;
}