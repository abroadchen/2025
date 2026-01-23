//
// Created by Psy.C on 2026/1/23.
//

#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(I, A, B) for (int I = (A); I <= (B); ++I)
using namespace std;

template <typename T>
void read(T& t) {
    int f = 0, c = getchar(); t = 0;
    while (!isdigit(c)) f |= c == '-', c = getchar();
    while (isdigit(c)) t = t * 10 + c - 48, c = getchar();
    if (f) t = -t;
}

template<typename T>
bool maxx(T& x, const T& y) { return x < y ? (x = y, true) : false; }

constexpr int inf = 2e6 + 207;
int dp[30][30][1 << 10];//到达位置(x,y)且状态为S时的最短路径
constexpr int dx[4] = {0, 0, 1, -1};//方向数组x偏移量（右、左、下、上）
constexpr int dy[4] = {1, -1, 0, 0};
int gx[30], gy[30], val[30];//特殊点坐标和价值
int sum[1 << 10];//子集S的总价值
char G[30][30];//地图字符
int n, m, t;//地图尺寸和特殊点数量
int sx, sy;//起始位置坐标

struct State {
    int x, y, S;//坐标(x,y)和状态S（已收集物品的状态）
    State(const int xx, const int yy, const int s)
        : x(xx), y(yy), S(s) {}
    State() : x(0), y(0), S(0) {}
};

//移动过程中是否会经过第i个特殊点
///从(x,y)移动到(nx,ny)时，检查是否穿越了特殊点(gx[i],gy[i])
inline bool in(const int x, const int y, const int nx, const int ny, const int i) {
    if (nx == gx[i] && ny < gy[i]) if (x < nx) return true;
    if (x == gx[i] && y < gy[i]) if (x > nx) return true;
    return false;
}

inline int bfs() {
    queue<State> q; q.emplace(sx, sy, 0);//初始状态加入队列
    int ans = 0;
    rep(i, 1, n) rep(j, 1, m) rep(S, 0, (1 << t)) dp[i][j][S] = -1;//未访问状态
    dp[sx][sy][0] = 0;//起始状态距离为0
    while (!q.empty()) {
        const auto curr = q.front(); q.pop();
        const int x = curr.x, y = curr.y, S = curr.S;
        if (x == sx && y == sy)//回到起点时，更新最大收益：价值总和-路径长度
            maxx(ans, sum[S] - dp[x][y][S]);
        rep(i, 0, 3) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 1 || nx > n || ny < 1 || ny > m || (G[nx][ny] != '.' && G[nx][ny] != 'S')) continue;
            int ns = S;//穿越了特殊点j，则切换其状态位
            rep(j, 1, t) if (in(x, y, nx, ny, j)) ns ^= 1 << (j - 1);
            if (dp[nx][ny][ns] == -1) {//新状态未访问过，更新距离并入队
                dp[nx][ny][ns] = dp[x][y][S] + 1;
                q.emplace(nx, ny, ns);
            }
        }
    }
    return ans;
}

int main() {
    read(n); read(m);
    rep(i, 1, n) scanf("%s", G[i] + 1);
    rep(i, 1, n) rep(j, 1, m) {
        if (const char c = G[i][j]; c == 'S') {//起点'S'的位置
            sx = i;
            sy = j;
        } else if (c != '#' && c != '.' && c != 'B') {//特殊点（数字字符）的位置
            gx[c - 48] = i;
            gy[c - 48] = j;
            ++t;
        }
    }
    rep(i, 1, t) read(val[i]);//每个特殊点的价值
    rep(i, 1, n) rep(j, 1, m) {
        if (const char c = G[i][j]; c == 'B') {//处理'B'点（陷阱），设置负无穷价值
            gx[++t] = i;
            gy[t] = j;
            val[t] = -inf;
        }
    }
    for (int S = 1; S < 1 << t; ++S) {
        rep(i, 1, t) if (1 << (i - 1) & S)//每个状态掩码对应的价值总和
            sum[S] += val[i];
    }
    const int ans = bfs();
    printf("%d\n", ans);
    return 0;
}