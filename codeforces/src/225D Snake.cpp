//
// Created by Psy.C on 2025/12/9.
//
/*
*n, m: 网格的行数和列数
mx: 最大数字标记
p: 字符网格
b: 位掩码
*x, y: 当前坐标
sta: 状态编码（用于记录路径信息）
 *方向数组rev，表示上、下、左、右四个方向
 *
*遍历整个网格：
如果不是墙('#')也不是终点('@')
如果数字比当前最大值大，则更新最大值和坐标
如果是'1'，则设置为起始位置
 *计算位掩码b，用于状态压缩
*初始化起始状态sta：
从最大数字开始，反向追踪到'1'
记录路径信息到状态编码中
 *
*u,v是目标位置
s是当前状态
解码状态sta，检查路径上的所有位置
如果目标位置与身体某部分重合，返回false
 *
 *
*使用位掩码 b 清除多余的高位
只保留有效的状态位
 *使用按位或运算将新方向 i 添加到最低2位
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for(int i=0;i<n;++i)
#define N 20
using namespace std;

int n, m, mx;
char p[N][N];
ll b;
struct node {
    int x, y, sta;
    node() : x(0), y(0), sta(0) {}
} st;

int rev[4][2] = {
    {-1,0}, {1,0}, {0,-1}, {0,1}
};

bool ok(const int x, const int y) { return x >= 0 && x < n && y >= 0 && y < m; }
void init() {
    mx = 0;
    int x = 0, y = 0;
    rep(i,n) rep(j,m) if (p[i][j] != '#' && p[i][j] != '@') {
        if (p[i][j] - '0' > mx) {
            x = i; y = j;
            mx = p[i][j] - '0';
        }
        if (p[i][j] == '1') st.x = i, st.y = j;
    }
    b = (1<<((mx-1)*2)) - 1;
    int& t = st.sta; t = 0;//现有变量的别名
    while (p[x][y] != '1') {
        rep(i,4) {
            const int dx = x + rev[i][0], dy = y + rev[i][1];
            if (ok(dx, dy) && p[dx][dy] == p[x][y] - 1) {//目标位置的数字正好比当前位置的数字小1
                t <<= 2;//为新方向腾出2位空间
                t |= i;//将新方向编码存储到最低2位
                x = dx, y = dy;
                break;
            }
        }
    }
}

int dir[4][2] = {
    {1,0},{-1,0},{0,1},{0,-1}
};
bool ok(const int u, const int v, node s) {
    int& t = s.sta;
    int x = s.x, y = s.y;
    if (x == u && y == v) return false;
    for (int i = 1; i < mx - 1; ++i) {
        x += dir[t&3][0], y += dir[t&3][1];//提取 t 的最低2位
        t >>= 2;//右移2位，准备提取下一个方向
        if (x == u && y == v) return false;
    }
    return true;
}

bool vis[15][15][65536];
int bfs() {
    queue<pair<node, int>> q;
    q.emplace(st, 0);
    vis[st.x][st.y][st.sta] = true;
    while (!q.empty()) {
        const node t = q.front().first;
        const int step = q.front().second;
        if (p[t.x][t.y] == '@') return step; q.pop();//如果到达终点'@'，返回步数
        rep(i,4) {
            const int dx = t.x + rev[i][0], dy = t.y + rev[i][1];
            if (ok(dx, dy) && p[dx][dy] != '#' && ok(dx, dy, t)) {
                node nxt;//创建新状态，更新状态编码
                nxt.x = dx; nxt.y = dy;
                nxt.sta = static_cast<int>(((t.sta<<2)&b)|i);// 新状态 = (旧状态左移2位 & 掩码) | 新方向
                if (!vis[dx][dy][nxt.sta]) {
                    vis[dx][dy][nxt.sta] = true;
                    q.emplace(nxt, step+1);
                }
            }
        }
    }
    return -1;
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> p[i]; init();
    cout << bfs() << '\n';
    return 0;
}