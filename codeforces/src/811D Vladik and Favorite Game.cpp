//
// Created by Psy.C on 2026/9/20.
//
/**
n,m：迷宫行列。
str[1..n][1..m]：迷宫地图，. 表示可走，* 表示墙，F 表示终点（奶酪/食物）‍。
vis：BFS 访问标记。
pre[x][y][2]：记录 (x,y) 的前驱坐标（BFS 路径记录用）。
dx/dy：上下左右四个方向的增量，顺序是 右、左、下、上。
M = 3e4+5：路径长度上限（足够容纳任意 BFS 最短路
读入 n×m 地图（每行一个字符串，str[i]+1 使下标从 1 开始）。
在第一次读入的字符中，若还没有发现终点 F（s==0 && e==0），则在每行里找 F 的位置，记为 (s,e)——也就是把"终点"坐标暂存在变量 s、e 里
从起点 (1,1) 做 BFS，pre 记录每个可达格子的前驱（由哪个格子到达它的）。
访问到终点 F 即 break（最短路确定）。
pos = 0 这里初始化，但其实真正用途在 init 和主循环
现在 s,e 是终点坐标。从终点沿 pre 一路回跳到起点 (1,1)。
每次把当前坐标 (s,e) 存入 st[pos]，然后跳到前驱。
直到回到 (1,1)，把起点也存入后结束。
结果：st 数组从 pos=0 到 pos=pos 依次存放 终点→…→起点 的逆序路径
在本地 BFS 算出的坐标路径上，先算出"从当前点走到下一站需要往哪个方向"（flg：0右/1左/2下/3上）。
输出对应方向字母 to[flg]，刷新 stdout。
读回系统实际把我们移到的坐标 (x,y)。
判断：
若实际到 (x,y) 正是 BFS 路径的下一站 st[pos-1] → 方向字母正确，pos-- 沿路径前进。
否则 → 说明"方向字母"与"真实方向"的映射不对（被交换了）。
如果冲突发生在水平方向（想走 R 或 L 却走偏）→ 把 to[0],to[1]（'R','L'）互换，即认为"左右两个字母恰好是反的"。
若冲突在垂直方向（想走 D 或 U）→ 交换 to[2],to[3]（'D','U'），即"上下字母相反"。
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105, M = 3e4+5;

struct node { int x, y; } now, nxt;

int vis[N][N], pos, pre[N][N][2], dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0}, n, m;
char str[N][N];
void bfs() {
    memset(vis, 0, sizeof(vis));
    queue<node> q; now.x = 1, now.y = 1; q.push(now);
    vis[1][1] = true; pos = 0; pre[1][1][0] = 1; pre[1][1][1] = 1;
    while (!q.empty()) {
        now = q.front();
        if (str[now.x][now.y] == 'F') break;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            nxt.x = dx[i] + now.x; nxt.y = dy[i] + now.y;
            if (nxt.x >= 1 && nxt.x <= n &&
                nxt.y >= 1 && nxt.y <= m && str[nxt.x][nxt.y] != '*') {
                if (!vis[nxt.x][nxt.y]) {
                    vis[nxt.x][nxt.y] = true;
                    q.push(nxt);
                    pre[nxt.x][nxt.y][0] = now.x;
                    pre[nxt.x][nxt.y][1] = now.y;
                }
            }
        }
    }
}

int st[M][2], s(0), e(0);
void init() {
    pos = 0;
    while (true) {
        st[pos][0] = s; st[pos][1] = e;
        int tx = s, ty = e;
        s = pre[tx][ty][0]; e = pre[tx][ty][1]; pos++;
        if (s == 1 && e == 1) {
            st[pos][0] = s; st[pos][1] = e;
            break;
        }
    }
}

char to[4] = {'R', 'L', 'D', 'U'};
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%s", str[i]+1);
        if (s == 0 && e == 0)
            for (int j = 1; j <= m; ++j)
                if (str[i][j] == 'F') {
                    s = i; e = j;
                }
    }
    bfs(); init();
    while (pos > 0) {
        int flg = -1;
        for (int i = 0; i < 4; ++i) {
            int tx = st[pos][0] + dx[i], ty = st[pos][1] + dy[i];
            if (tx == st[pos-1][0] && ty == st[pos-1][1]) flg = i;
        }
        printf("%c\n", to[flg]); fflush(stdout);
        int x, y; scanf("%d%d", &x, &y);
        if (x == st[pos-1][0] && y == st[pos-1][1]) pos--;
        else {
            if (to[flg] == 'L' || to[flg] == 'R') swap(to[0], to[1]);
            else swap(to[2], to[3]);
        }
    }
    return 0;
}