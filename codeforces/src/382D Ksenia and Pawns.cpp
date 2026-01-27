//
// Created by Psy.C on 2026/1/26.
//
/**
* h：已访问过的格子 已访问状态
vis：当前路径正在访问的格子 当前路径访问状态
dis：距离
col：连通分量编号
tot：连通分量计数器
 */
#include <iostream>
#include <bitset>
#include <stack>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
#define ii pair<int, int>
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    char mp[N][N];
    rep(i,n) rep(j,m) cin >> mp[i][j];
    bitset<N> h[N], vis[N];
    stack<ii> stk;
    int dis[N][N], col[N][N], tot = 0;
    rep(i,n) rep(j,m) {
        if (mp[i][j] == '#' || h[i][j]) continue;//非障碍物且未被访问的格子
        int x = i, y = j;//当前位置为起始点(x,y)
        while (!h[x][y]) {
            stk.emplace(x, y);//将当前位置压入栈中
            h[x][y] = vis[x][y] = true;
            if (mp[x][y] == '^') x--;//沿着方向字符移动，直到遇到已访问节点或边界
            else if (mp[x][y] == 'v') x++;
            else if (mp[x][y] == '<') y--;
            else if (mp[x][y] == '>') y++;
            else {//当前位置不是方向字符（即遇到了边界或其他障碍
                stk.pop(), h[x][y] = vis[x][y] = false;//从栈顶弹出并取消标记
                x = stk.top().first;
                y = stk.top().second;//获取栈顶坐标
                stk.pop(), vis[x][y] = false;// 弹出栈顶并取消vis标记
                dis[x][y] = 1, col[x][y] = ++tot;
                break;
            }
        }
        if (vis[x][y]) return cout << -1, 0;//形成了环，返回-1
        while (!stk.empty()) {//回溯路径，更新距离和连通分量编号
            const int px = stk.top().first, py = stk.top().second;//获取栈顶元素的坐标
            stk.pop();
            vis[px][py] = false;//取消当前路径访问标记
            dis[px][py] = dis[x][y] + 1, col[px][py] = col[x][y];//更新距离和连通分量
            x = px, y = py;//更新当前位置为刚才弹出的坐标
        }
    }
    int x = 0, y = 0;
    rep(i,n) rep(j,m) if (dis[i][j] > dis[x][y]) x = i, y = j;//找到距离最大的点 (x,y)
    if (x == 0 && y == 0) return cout << 0, 0;//没有可达点，返回0
    rep(i,n) rep(j,m) if (dis[i][j] == dis[x][y] && col[i][j] != col[x][y]) {//相同距离但不同连通分量的点
        return cout << (dis[x][y] << 1), 0;
    }
    return cout << ((dis[x][y]<<1)-1), 0;
}