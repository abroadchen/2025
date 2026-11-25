//
// Created by Psy.C on 2026/11/25.
//

/**
真正学会的起点..
st[] / ed[] 分别存起点连通块、终点连通块内的所有格点坐标
欧氏距离的平方（不取根号，用于大小比较，避免浮点误差）
标准四方向 BFS，只走值为 0 的空地。
f==0：从起点扩展，把连通块所有点存进 st；f==1：从终点扩展，存进 ed。
记录连通块内每个格子坐标，供之后枚举
读入网格和起终点坐标。
用两个 BFS 分别收集起、终两块的格子。
双重循环枚举"起点块的一个格 ↔ 终点块的一个格"，取两者欧氏距离平方的最小值，作为最少需改造的墙的代价平方。
输出最小代价
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 3e3, M = 60, inf = 0x7fffffff;

struct node { int x, y; } st[N], ed[N];
inline int dis(int sx, int sy, int ex, int ey) {
    return (sx-ex)*(sx-ex) + (sy-ey)*(sy-ey);
}

bool vis[M][M];
queue<node> q;
int cnt, tot, dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1}, n, m[M][M];
void bfs(bool f, int sx, int sy) {
    vis[sx][sy] = 1; q.push({sx, sy});
    if (f == 0) { cnt++; st[cnt].x = sx, st[cnt].y = sy; }
    else { tot++; ed[tot].x = sx, ed[tot].y = sy; }
    while (!q.empty()) {
        int x = q.front().x, y = q.front().y; q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx > 0 && nx <= n && ny > 0 && ny <= n && !vis[nx][ny] && m[nx][ny] == 0) {
                vis[nx][ny] = 1; q.push({nx, ny});
                if (f == 0) { cnt++; st[cnt].x = nx, st[cnt].y = ny; }
                else { tot++; ed[tot].x = nx, ed[tot].y = ny; }
            }
        }
    }
}
template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}
template<typename T,typename... Args>
void rd(T& t,Args&... args) {
    rd(t); rd(args...);
}

int sx, sy, ex, ey, ans = inf;
int main() {
    fast;
    rd(n, sx, sy, ex, ey);
    rep(i,n) rep(j,n) scanf("%1d",&m[i][j]);
    bfs(0, sx, sy); bfs(1, ex, ey);
    rep(i,cnt) rep(j,tot) ans = min(ans, dis(st[i].x,st[i].y,ed[j].x,ed[j].y));
    cout << ans;
    return 0;
}