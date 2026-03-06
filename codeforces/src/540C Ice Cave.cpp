//
// Created by Psy.C on 2026/3/6.
//
/**
h, d: 当前节点和下一节点
ex, ey: 目标坐标
检查坐标(x,y)是否为目标点且被标记为'X'
to[][2]: 四个方向数组，分别是上(-1,0)、左(0,-1)、右(0,1)、下(1,0)
sx, sy: 起始坐标
n, m: 地图尺寸
flag: 标志变量，表示是否到达目标
将起始点减1后入队（注意这里有坐标偏移）
检查当前位置的四个邻居是否为目标点
如果找到目标，设置flag=1并返回
否则扩展当前节点的四个方向邻居
跳过越界或已访问('X')的位置
将新位置标记为'X'并入队


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 501;

struct node { int x, y; } h, d;
queue<node> q;
char mp[N][N];
int ex, ey;
int ok(const int x, const int y) {
    if (x == ex && y == ey && mp[x][y] == 'X')
        return 1;
    return 0;
}

int sx, sy, to[][2] = {
    -1, 0, 0, -1, 0, 1, 1, 0
}, n, m, flag;
void bfs() {
    flag = 0; h.x = sx - 1, h.y = sy - 1;
    q.push(h);
    while (!q.empty()) {
        h = q.front(); q.pop();
        if (ok(h.x-1, h.y) || ok(h.x+1, h.y) ||
            ok(h.x, h.y-1) || ok(h.x, h.y+1)) {
            flag = 1; return ;
        }
        for (const auto& i : to) {
            d.x = h.x + i[0]; d.y = h.y + i[1];
            if (d.x < 0 || d.y < 0 || d.x >= n || d.y >= m ||
                mp[d.x][d.y] == 'X') continue;
            mp[d.x][d.y] = 'X';
            q.push(d);
        }
    }
}


int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> mp[i];
    cin >> sx >> sy >> ex >> ey; ex--, ey--;
    bfs();
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}