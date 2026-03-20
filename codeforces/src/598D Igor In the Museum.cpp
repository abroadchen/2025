//
// Created by Psy.C on 2026/3/20.
//
/**
f[N][N]：标记数组，记录每个位置属于哪个连通块
cnt：连通块编号计数器
ans：当前连通块的周长
dir[][2]：四个方向的偏移量（右、左、下、上）
num[N*N]：存储每个连通块的周长
s[N][N]：网格地图

初始化：将起点加入队列，标记为当前连通块编号
周长计算：每个格子初始贡献4条边
遍历四个方向：
如果相邻位置在边界内且是空地('.')：
ans--：减少一条边（与相邻空地共享）
如果未访问过，加入队列继续BFS
如果相邻位置在边界外：
ans--：减少一条边（边界也算周长）

x--, y--：转换为0-indexed坐标
if (f[x][y] == 0)：如果该位置未访问过
cnt++：创建新连通块编号
bfs(x, y)：计算该连通块的周长
else：如果已访问过，直接输出保存的周长
时间复杂度：O(nmk)（每个查询最多遍历整个连通块一次） 空间复杂度：O(nm)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
struct node { int x, y; } t, a;

int f[N][N], cnt, ans, dir[][2] = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}
}, n, m, num[N*N];
char s[N][N];
void bfs(int x, int y) {
    queue<node> q; a.x = x, a.y = y; q.push(a);
    f[x][y] = cnt; ans = 0;
    while (!q.empty()) {
        a = q.front(); q.pop(); ans += 4;
        for (auto &i : dir) {
            t.x = a.x + i[0], t.y = a.y + i[1];
            if (t.x >= 0 && t.x < n && t.y >= 0 && t.y < m) {
                if (s[t.x][t.y] == '.') {
                    ans--;
                    if (f[t.x][t.y] == 0) {
                        q.push(t);
                        f[t.x][t.y] = cnt;
                    }
                }
            } else ans--;
        }
    }
    num[cnt] = ans;
    cout << ans << '\n';
}

int k, x, y;
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> s[i];
    memset(num, -1, sizeof(num));
    memset(f, 0, sizeof(f)); cnt = 0;
    while (k--) {
        cin >> x >> y; x--, y--;
        if (f[x][y] == 0) { cnt++; bfs(x, y); }
        else cout << num[f[x][y]] << '\n';
    }
    return 0;
}