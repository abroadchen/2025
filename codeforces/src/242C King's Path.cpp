//
// Created by Psy.C on 2025/12/15.
//
/*
*p：map容器，存储从起点到每个可达点的步数距离
mp：map容器，标记哪些点是可达的（在允许移动的区域内）
*dx, dy：目标点坐标
fx[], fy[]：8个方向的偏移量数组，表示可以移动的8个方向
*(-1,-1) (-1,0) (-1,1)
( 0,-1)        ( 0,1)
( 1,-1) ( 1,0) ( 1,1)
 *
*遍历8个可能的移动方向
计算新位置(tx, ty)
检查合法性：
tx > 0 且 ty > 0：坐标为正数
mp.count({tx, ty})：该点在允许移动的区域内
!p.count({tx, ty})：该点尚未被访问过
如果合法，更新距离并加入队列
 *
 *读取起始点坐标(sx, sy)、目标点坐标(dx, dy)和区域数量n
*读取可移动区域信息：
循环n次读取每条水平线段的信息
x：水平线的行坐标
[l, r]：该行上可移动的列范围
将该线段上的所有点标记为可达
 *调用BFS函数计算最短距离并输出结果
 *
*时间复杂度：O(V + E)，其中V是可达点数，E是边数
空间复杂度：O(V)，用于存储队列和访问标记
 */
#include <iostream>
#include <map>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;


map<ii, int> p;
map<ii, bool> mp;
int dx, dy, fx[] = {
    -1,-1,-1,0,0,1,1,1
}, fy[] = {
    -1,0,1,-1,1,-1,0,1
};
int bfs(int sx, int sy) {
    queue<ii> q; q.emplace(sx, sy);//起始点(sx, sy)加入队列
    while(!q.empty()) {
        ii cur = q.front(); q.pop();
        const int x = cur.first, y = cur.second;//提取当前点的x和y坐标
        if (cur.first == dx && cur.second == dy) return p[cur];//如果当前点就是目标点(dx, dy)返回从起点到当前点的距离p[cur]
        for (int i = 0; i < 8; ++i) {
            int tx = x + fx[i], ty = y + fy[i];
            if (tx > 0 && ty > 0 && mp.count({tx, ty}) &&
                !p.count({tx, ty})) {
                p[{tx, ty}] = p[cur] + 1;
                q.emplace(tx, ty);
            }
        }
    }
    return -1;
}


int main() {
    fast;
    int sx, sy, n; cin >> sx >> sy >> dx >> dy >> n;
    for (int i = 1, x, l, r; i <= n; ++i) {
        cin >> x >> l >> r;
        for (int j = l; j <= r; ++j) mp[{x,j}] = true;
    }
    cout << bfs(sx, sy) << '\n';
    return 0;
}