//
// Created by Psy.C on 2026/9/28.
//
/**
constexpr int N = 255：地图最大 255×255。
struct node { int x, y, v; }：表示一个状态/格子：x,y 是坐标，v 是音量。
vector<node> s：存放所有声源的列表。
dp[N][N]：dp[x][y] 累加该格子收到的所有声源声音总和（答案统计的核心）。
dir[][2]：四个方向数组（上、右、下、左）{0,1},{1,0},{0,-1},{-1,0}，用于 BFS 扩展。
n, m：地图行数、列数。
mp[N][N]：地图本身。mp[i][j] 为 * 表示障碍（不可经过），为英文字母表示声源，其他如 . 表示普通空格。
vis[N][N]：BFS 访问标记，防止重复入队（每个声源 BFS 前重置）
输入 (x, y) 是声源坐标，v 是声源初始音量。
用队列 q 做 BFS，初始把源点 (x,y,v) 入队。
取队首 now。
把当前音量 now.v 累加到 dp[now.x][now.y]：表示这个格子收到了可视音量贡献。
q.pop() 弹出。
遍历四个方向 i，算出相邻格子 nxt。
nxt.v = now.v / 2：音量每走一格减半（整型除法，向下取整不到 1 就为 0）。
入队条件（全部满足才扩展）：
0 <= nxt.x < n 且 0 <= nxt.y < m：不越界。
mp[nxt.x][nxt.y] != '*'：目标格不是障碍（* 不能进入）。
vis[nxt.x][nxt.y] == false：还没访问过，防重（每个格子在这个声源的 BFS 中只算一次，避免同一格子从不同路径重复贡献——因为规则中一个声源对某格的声音只算一次）。
nxt.v != 0：音量还没衰减到 0（音量变 0 就不再传播）。
满足则标 vis = true 并入队。
注意：dp 累加发生在弹出时，而 vis 标记在入队时，保证每个格子对该声源只会累计一次音量 nxt.v

q：每个字母的最小音量系数（声源强度 = (字母序号)*q）。
p：音量判断阈值。
读入 n 行地图字符串到 mp
遍历每个格子，若 mp[i][j] 是英文字母（isalpha 判断），则它是一个声源：
坐标 (i,j) 存入。
v = (mp[i][j] - 'A' + 1) * q：字母转成音量。'A'→1，'B'→2，…，字母越大音量越大，再乘以系数 q。
所有声源收集进 s
对每一个声源：
先把源点标记 vis = true（源点本身作为已访问）。
bfs(...) 从该声源扩散声音，把各格音量累加到 dp。
memset(vis, false, ...)：重置访问标记，为下一个声源的独立 BFS 做准备（每个声源都是独立传播）。
关键：dp 不重置，跨声源累加；vis 每次 BFS 前重置，保证每轮 BFS 内部格子不重复
res 计数。
遍历所有格子，若该格收到的声音总量 dp[i][j] 大于阈值 p，则 res++。
输出 res（"嘈杂"格子数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 255;
struct node { int x, y, v; };
vector<node> s;

ll dp[N][N];
int dir[][2] = {0, 1, 1, 0, 0, -1, -1, 0}, n, m;
char mp[N][N];
bool vis[N][N];
void bfs(int x, int y, int v) {
    node now{}, nxt{};
    queue<node> q; now.x = x; now.y = y; now.v = v; q.push(now);
    while (!q.empty()) {
        now = q.front(); dp[now.x][now.y] += now.v; q.pop();
        for (auto& i : dir) {
            nxt.x = now.x + i[0]; nxt.y = now.y + i[1]; nxt.v = now.v/2;
            if (0 <= nxt.x && nxt.x < n && 0 <= nxt.y && nxt.y < m &&
                mp[nxt.x][nxt.y] != '*' && vis[nxt.x][nxt.y] == false && nxt.v != 0) {
                vis[nxt.x][nxt.y] = true;
                q.push(nxt);
            }
        }
    }
}

int q, p, i, j;
int main() {
    fast;
    cin >> n >> m >> q >> p;
    for (i = 0; i < n; ++i) cin >> mp[i];
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (isalpha(mp[i][j]))
                s.push_back({.x = i, .y = j, .v = (mp[i][j]-'A'+1)*q});
    for (i = 0; i < s.size(); ++i) {
        vis[s[i].x][s[i].y] = true;
        bfs(s[i].x, s[i].y, s[i].v);
        memset(vis, false, sizeof vis);
    }
    int res = 0;
    for (i = 0; i < n; ++i)
        for (j = 0; j < m; ++j)
            if (dp[i][j] > p) res++;
    cout << res << '\n';
    return 0;
}