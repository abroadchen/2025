//
// Created by Psy.C on 2025/12/23.
//

#include <iostream>
#include <cstring>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

struct node { int x, y, c, dir; };//坐标(x,y)、转弯次数(c)和方向(dir)
int dx[] = {-1,0,0,1}, dy[] = {0,-1,1,0};//上(-1,0)、左(0,-1)、右(0,1)、下(1,0)

int main() {
    fast;
    int n, m, cnt = 0; cin >> n >> m; char a[N][N];//网格大小n和m，定义计数器cnt，定义字符网格a
    rep(i,n) {
        cin >> a[i];
        rep(j,m) if (a[i][j] == 'B') cnt++;//统计'B'字符的数量
    }
    int vis[N][N];
    rep(i,n) rep(j,m) if (a[i][j] == 'B') {//对每个'B'位置执行BFS
        int ans = 0;
        memset(vis, -1, sizeof(vis));
        queue<node> q; node p = {i, j, 0, -1}; q.push(p);//从当前位置开始，初始转弯次数为0，初始方向为-1
        vis[i][j] = 0;//标记起始位置已访问
        while (!q.empty()) {
            const node u = q.front(); q.pop();
            rep(k,4) {
                const int x = u.x + dx[k], y = u.y + dy[k];//计算新坐标
                if ((vis[x][y] == -1 || vis[x][y] >= u.c) && a[x][y] == 'B') {//如果新位置未访问或当前路径的转弯次数更少，且位置是'B'
                    if (u.dir == -1 || k == u.dir) {//如果是初始状态或方向相同，保持转弯次数
                        node v = {x, y, u.c, k};
                        q.push(v);
                        vis[x][y] = u.c;
                    } else if (u.c < 1) {//如果转弯次数小于1，增加转弯次数
                        node v = {x, y, u.c + 1, k};
                        q.push(v);
                        vis[x][y] = u.c + 1;
                    }
                }
            }
        }
        rep(o,n) rep(l,m) if (vis[o][l] != -1) ans++;//统计从当前'B'可达的'B'数量
        if (cnt != ans) { cout << "NO\n"; return 0; }//可达数量不等于总'B'数量
    }
    cout << "YES\n";
    return 0;
}