//
// Created by Psy.C on 2026/1/6.
//
/**
* dx[]: 方向移动数组，dx[0]=0(左), dx[1]=0(右), dx[2]=-1(下), dx[3]=1(上)
dy[]: 方向移动数组，dy[0]=-1(左), dy[1]=1(右), dy[2]=0(下), dy[3]=0(上)
 *in函数：检查坐标(x,y)是否在合法范围内[5,440]×[5,440]
*flag[N][N]: 二维标记数组，用于BFS搜索和路径记录
vis[N][N]: 二维标记数组，标记障碍物位置
 *ok函数：检查从坐标(x,y)开始是否可以到达边界
 *
*遍历四个方向
计算新坐标(tx,ty)
如果新坐标超出边界，返回false（表示可达边界）
如果是障碍物，跳过
如果已访问，跳过
标记新坐标为已访问，加入队列
 *返回true（表示不可达边界）
 *
 *no 检查坐标(x,y)是否在合法范围内且被障碍物占据
*如果超出范围返回false
否则返回vis[x][y]的值
 *
*run函数：执行一次移动操作
从参数a中提取两个坐标点：a.first为人物坐标，a.second为箱子坐标
*检查人物移动目标是否为障碍物，如果是则程序异常退出
人物按dir方向移动
*如果箱子目标位置无障碍，则箱子也移动
输出移动方向字符
如果人物和箱子重合，程序正常结束
返回更新后的两个坐标点
 *
 *vx,vy(人物初始位置)，sx,sy(箱子初始位置)，m(障碍物数量)
*如果没有障碍物
如果人物已在箱子位置，直接返回
否则输出-1
*将所有坐标平移到正数范围（加上偏移量M）
交换人物和箱子的x、y坐标（可能是坐标系转换）
读取所有障碍物坐标，平移后标记到vis数组
 *
 *
*根据箱子和人物的相对位置执行不同的策略
找到最左边的障碍物
通过移动使人物和箱子重合
进入无限循环继续移动
 *
 *
 *
 */
#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 450
#define M 210
#define ii pair<int, int>
#define pp pair<ii, ii>
#define L 0
#define R 1
#define D 2
#define U 3
#define vvx cur.first.first
#define vvy cur.first.second
#define ssx cur.second.first
#define ssy cur.second.second
#define inf 0x3f3f3f3f
using namespace std;

constexpr int dx[] = {
    0, 0, -1, 1
}, dy[] = {
    -1, 1, 0, 0
};

bool in(const int x, const int y) {
    return x >= 5 && x <= 440 && y >= 5 && y <= 440;
}

int flag[N][N], vis[N][N];
bool ok(int x, int y) {
    memset(flag, 0, sizeof(flag));
    queue<ii> q; q.emplace(x, y); flag[x][y] = 1;
    while (!q.empty()) {
        auto [u, v] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = u + dx[i], ty = v + dy[i];
            if (!in(tx, ty)) return false;
            if (vis[tx][ty]) continue;
            if (flag[tx][ty]) continue;
            flag[tx][ty] = 1;
            q.emplace(tx, ty);
        }
    }
    return true;
}

bool no(const int x, const int y) {
    if (!in(x, y)) return false;
    return vis[x][y];
}

constexpr char ch[] = {
    'L', 'R', 'D', 'U'
};
pp run(pp a, const int dir) {
    auto [x, y] = a.first;
    auto [u, v] = a.second;
    if (no(x + dx[dir], y + dy[dir])) exit(-1);
    x += dx[dir], y += dy[dir];
    if (!no(u + dx[dir], v + dy[dir])) u += dx[dir], v += dy[dir];
    cout << ch[dir];
    if (x == u && y == v) exit(0);
    return {{x, y}, {u, v}};
}


pp run(pp a, const int dir, int tim) {//连续执行tim次相同方向的移动操作
    while (tim--) a = run(a, dir);
    return a;
}

pp cur;
void dfs(const int x, const int y) {//重构路径
    if (flag[x][y] != -10) {
        const int dir = flag[x][y] ^ 1;//方向取反（L↔R, U↔D)
        dfs(x + dx[dir], y + dy[dir]);//递归访问前一个位置
    } else return;
    cur = run(cur, flag[x][y]);//执行当前移动操作
}

int main() {
    fast;
    int vx, vy, sx, sy, m, x[N], y[N];
    cin >> vx >> vy >> sx >> sy >> m;
    if (!m) {
        if (vx == sx && vy == sy) return 0;
        return cout << "-1\n", 0;
    }
    vx += M, vy += M, sx += M, sy += M;
    swap(vx, vy); swap(sx, sy);
    for (int i = 1; i <= m; ++i) {
        cin >> y[i] >> x[i];
        x[i] += M; y[i] += M;
        vis[x[i]][y[i]] = 1;
    }
    const bool v = ok(vx, vy), s = ok(sx, sy);//检查人物和箱子是否在同一连通区域
    if (v^s) return cout << "-1\n", 0;
    if (v && s) {//人物和箱子都在同一连通区域 使用BFS检查人物是否能到达箱子位置 如果能到达，跳转到loop标签
        {
            memset(flag, 0, sizeof(flag));
            queue<ii> q; q.emplace(vx, vy); flag[vx][vy] = 0;
            while (!q.empty()) {
                auto [x1, y1] = q.front(); q.pop();
                for (int i = 0; i < 4; ++i) {
                    int tx = x1 + dx[i], ty = y1 + dy[i];
                    if (vis[tx][ty]) continue;
                    if (flag[tx][ty]) continue;
                    if (tx == sx && ty == sy) goto loop;
                    flag[tx][ty] = 1;
                    q.emplace(tx, ty);
                }
            }
        }
        return cout << "-1\n", 0;
        loop:;
        for (;;) {//无限循环直到人物和箱子重合 使用BFS找到到达箱子的最短路径
            memset(flag, 0xff, sizeof(flag));
            flag[vx][vy] = -10;
            queue<ii> q; q.emplace(vx, vy);
            while (!q.empty()) {
                auto [x1, y1] = q.front(); q.pop();
                for (int i = 0; i < 4; ++i) {
                    int tx = x1 + dx[i], ty = y1 + dy[i];
                    if (vis[tx][ty]) continue;
                    if (flag[tx][ty] != -1) continue;
                    flag[tx][ty] = i;
                    if (tx == sx && ty == sy) goto out;
                    q.emplace(tx, ty);
                }
            }
            out:;
            cur = {{vx, vy}, {sx, sy}};
            dfs(sx, sy);//重构路径并执行移动 更新人物和箱子的新位置
            vx = cur.first.first; vy = cur.first.second;
            sx = cur.second.first; sy = cur.second.second;
            if (vx == sx && vy == sy) return 0;
        }
    }
    //人物和箱子不在同一连通区域
    memset(flag, 0xff, sizeof(flag));
    int ex = 0, ey = 0; flag[vx][vy] = -10;//BFS找到人物可达的边界点(ex,ey)
    queue<ii> q; q.emplace(vx, vy);
    while (!q.empty()) {
        auto [x1, y1] = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int tx = x1 + dx[i], ty = y1 + dy[i];
            if (vis[tx][ty]) continue;
            if (flag[tx][ty] != -1) continue;
            flag[tx][ty] = i;
            if (!in(tx, ty)) {
                ex = tx; ey = ty;
                goto out2;
            }
            q.emplace(tx, ty);
        }
    }
    out2:;
    cur = {{vx, vy}, {sx, sy}};
    dfs(ex, ey);//重构路径到边界点
    if (ex == 441) cur = run(cur, L, 500),
        cur = run(cur, D, 500); else {
        cur = run(cur, D, 500),
        cur = run(cur, L, 500);
    }//将箱子移动到安全区域
    cur = run(cur, D, 500), cur = run(cur, L, 500);
    sx = cur.second.first; sy = cur.second.second;//根据边界点位置选择不同的移动策略
    if (in(sx, sy)) {//如果箱子仍在合法范围内，重新寻找边界点
        int ex1 = 0, ey1 = 0;
        memset(flag, 0xff, sizeof(flag));
        flag[sx][sy] = -10;
        while (!q.empty()) q.pop(); q.emplace(sx, sy);
        while (!q.empty()) {
            auto [x1, y1] = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int tx = x1 + dx[i], ty = y1 + dy[i];
                if (vis[tx][ty]) continue;
                if (flag[tx][ty] != -1) continue;
                flag[tx][ty] = i;
                if (!in(tx, ty)) {
                    ex1 = tx; ey1 = ty;
                    goto out3;
                }
                q.emplace(tx, ty);
            }
        }
        out3:;
        dfs(ex1, ey1);
        //将箱子再次移出，确保安全
        if (ex1 == 441) cur = run(cur, L, 500),
            cur = run(cur, D, 500); else {
            cur = run(cur, D, 500), cur = run(cur, L, 500);
        }
    }
    if (ssx >= vvx && ssy >= vvy) {
        int mn = inf;
        for (int i = 1; i <= m; ++i) mn = min(mn, x[i]);
        while (ssx != mn) cur = run(cur, U);
        while (!no(ssx + dx[R], ssy + dy[R])) cur = run(cur, R);
        while (vvy != ssy) cur = run(cur, R);
        cur = run(cur, D); cur = run(cur, R);
        while (true) cur = run(cur, U);
    }
    if (ssx >= vvx && ssy <= vvy) {
        while (ssy <= 440) cur = run(cur, R);
        int mn = inf;
        for (int i = 1; i <= m; ++i) mn = min(mn, x[i]);
        while (ssx != mn) cur = run(cur, U);
        while (!no(ssx + dx[L], ssy + dy[L])) cur = run(cur, L);
        while (vvy != ssy) cur = run(cur, L);
        cur = run(cur, D); cur = run(cur, L);
        while (true) cur = run(cur, U);
    }
    if (ssx <= vvx && ssy <= vvy) {
        while (ssy <= 440) cur = run(cur, R);
        int mx = -inf;
        for (int i = 1; i <= m; ++i) mx = max(mx, x[i]);
        while (ssx != mx) cur = run(cur, U);
        while (!no(ssx + dx[L], ssy + dy[L])) cur = run(cur, L);
        while (vvy != ssy) cur = run(cur, L);
        cur = run(cur, U); cur = run(cur, L);
        while (true) cur = run(cur, D);
    }
    if (ssx <= vvx && ssy >= vvy) {
        int mx = -inf;
        for (int i = 1; i <= m; ++i) mx = max(mx, x[i]);
        while (ssx != mx) cur = run(cur, U);
        while (!no(ssx + dx[R], ssy + dy[R])) cur = run(cur, R);
        while (vvy != ssy) cur = run(cur, R);
        cur = run(cur, U); cur = run(cur, R);
        while (true) cur = run(cur, D);
    }
    return 0;
}