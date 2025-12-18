//
// Created by Psy.C on 2025/12/18.
//
/*
 *坐标对向量r(存储机器人位置)和t(存储候选位置)，定义二维数组p记录机器人编号，清空r向量
 *
 *访问标记数组flag和集合数组s，用于存储每个候选点能到达的机器人编号
 *
 *对每个候选点进行BFS搜索，初始化队列和标记数组
 *如果当前位置是机器人，则将该机器人编号加入当前候选点的集合；如果达到最大距离则跳过
 *向四个方向扩展，如果新位置合法且未访问，则标记并加入队列
 *
 *寻找两个候选点，使得它们能够覆盖所有机器人，如果找到则输出这两个点的坐标(从1开始计数)
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

int w[4][2] = {0,1,0,-1,1,0,-1,0};//右(0,1)、左(0,-1)、下(1,0)、上(-1,0)

char str[N][N];//存储地图
int row, col, d;
bool ok(const int x, const int y) {//坐标在范围内且不是障碍物
    if (x >= 0 && y >= 0 && x < row && y < col && str[x][y] != 'X')
        return true;
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    cin >> row >> col >> d;
    vector<pair<int, int>> r, t; int p[N][N] = {-1}; r.clear();
    rep(i,row) {
        cin >> str[i];
        rep(j,col) if (str[i][j] == 'R') {//如果发现机器人'R'，将其坐标加入r向量，并在p数组中标记其编号
            r.emplace_back(i, j);
            p[i][j] = static_cast<int>(r.size());
        }
    }
    int x = d + 1;
    if (r.size() > 2 * (2 * x * x - 2 * x + 1)) { cout << "-1"; return 0; }
    for (const auto & i : r) for (int j = -d; j <= d; ++j) for (int k = -d; k <= d; ++k) {
        if (abs(j) + abs(k) > d) continue;//在曼哈顿距离d范围内生成所有可达点，添加到t向量中
        int u = i.first + j, v = i.second + k;
        if (ok(u, v)) t.emplace_back(u, v);
    }
    sort(t.begin(), t.end());//唯一候选点数量
    const int siz = static_cast<int>(unique(t.begin(), t.end()) - t.begin());
    x *= 2;
    if (siz > 2 * (2 * x * x - 2 * x + 1)) { cout << "-1"; return 0; }
    bool flag[N][N]; set<int> s[N];
    rep(i,siz) {
        queue<pair<pair<int, int>, int>> q;
        while (!q.empty()) q.pop();
        memset(flag, false, sizeof(flag));
        flag[t[i].first][t[i].second] = true;
        q.push({{t[i].first, t[i].second}, 0});
        while (!q.empty()) {
            pair<pair<int, int>, int> u = q.front(), v; q.pop();
            if (str[u.first.first][u.first.second] == 'R')
                s[i].insert(p[u.first.first][u.first.second]);
            if (u.second >= d) continue;
            for (const auto & j : w) {
                v = u;
                v.first.first += j[0];
                v.first.second += j[1];
                v.second += 1;
                if (ok(v.first.first, v.first.second) &&
                    !flag[v.first.first][v.first.second]) {
                    flag[v.first.first][v.first.second] = true;
                    q.push(v);
                }
            }
        }
    }
    bool ans = false;
    for (int i = 0; i < siz && !ans; ++i) for (int j = i + 1; j < siz && !ans; ++j) {
        if (s[i].size() + s[j].size() < r.size()) continue;
        set<int> tmp(s[i]);
        for (int it : s[j]) { tmp.insert(it); }
        if (tmp.size() == r.size()) {
            ans = true;
            cout << t[i].first + 1 << ' ' << t[i].second + 1 << ' ' <<
                t[j].first + 1 << ' ' << t[j].second + 1 << '\n';
        }
    }
    if (!ans) cout << "-1";
    rep(i,siz) s[i].clear();
    return 0;
}