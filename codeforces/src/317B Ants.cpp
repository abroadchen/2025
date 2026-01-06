//
// Created by Psy.C on 2026/1/6.
//

#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2000
#define M 4010
using namespace std;


int main() {
    fast;
    int n, t; cin >> n >> t;
    int mp[M][M]; mp[N][N] = n;//在中心位置(N,N)放置初始值n（相当于坐标(0,0)）
    queue<pair<int,int>> q; q.emplace(0,0);
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (mp[x+N][y+N] >= 4) {
            const int k = mp[x+N][y+N]>>2;//要分发的数量
            mp[x-1+N][y+N] += k;//向四个相邻方向（左、右、上、下）各分发k个单位
            mp[x+1+N][y+N] += k;
            mp[x+N][y-1+N] += k;
            mp[x+N][y+1+N] += k;
            mp[x+N][y+N] &= 3;//相当于对4取模，保留当前位置的余数
            q.emplace(x, y - 1);//将四个相邻位置加入队列，以便后续处理
            q.emplace(x, y + 1);
            q.emplace(x + 1, y);
            q.emplace(x - 1, y);
        }
    }
    while (t--) {
        int x, y; cin >> x >> y;
        if (x >= N || y >= N || x <= -N || y <= -N) {
            cout << 0 << '\n';
            continue;
        }
        cout << mp[x+N][y+N] << '\n';//数组索引不能为负数，所以加上N进行偏移
    }
    return 0;
}