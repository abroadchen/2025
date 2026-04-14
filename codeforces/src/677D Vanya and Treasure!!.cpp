//
// Created by Psy.C on 2026/4/13.
//
/**
c[N][N]: 树状数组存储的值
h[N][N]: 时间戳，用于标记是否被更新过
在位置(x,y)更新最小值mi，时间戳为hi
二维树状数组的更新操作
如果时间戳不匹配，初始化该位置
二维树状数组的查询操作
查询矩形[1,1]到[x,y]的最小值
bt[4]: 4个二维树状数组，用于处理4个方向
dp[x][y]表示到达位置(x,y)的最小代价

将位置(x,y)的信息更新到4个树状数组中
每个树状数组对应不同的曼哈顿距离变换
从4个方向查询到达(x,y)的最小代价
利用曼哈顿距离的性质，通过4个方向的变换来快速计算

g[val]存储值为val的位置
初始化所有树状数组
处理值为1的位置，初始代价为到(1,1)的曼哈顿距离
按数值从小到大处理
对每个值d，先查询到达该值位置的最小代价
再更新该值位置的信息到树状数组
输出到达值为p的位置的最小代价

时间复杂度：O(p·n·m·log²(n·m))

res和dp[x][y]指向内存中的同一个位置
任何对res的修改都会直接修改dp[x][y]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define low_bit(i) (i&-i)
using namespace std;
constexpr int N = 305, inf = 1<<30;
struct bit {
    int c[N][N], h[N][N];
    void init() { memset(h, 0, sizeof h); }
    void update(int hi, int x, int y, int mi) {
        for (int i = x; i <= N; i += low_bit(i))
            for (int j = y; j <= N; j += low_bit(j)) {
                if (h[i][j] != hi) h[i][j] = hi, c[i][j] = inf;
                c[i][j] = min(c[i][j], mi);
            }
    }
    int query(int hi, int x, int y) {
        int res = inf;
        for (int i = x; i >= 1; i -= low_bit(i))
            for (int j = y; j >= 1; j -= low_bit(j))
                if (h[i][j] == hi)
                    res = min(res, c[i][j]);
        return res;
    }
} bt[4];

int dp[N][N], n, m;
void upd(int d, int x, int y) {
    bt[0].update(d, x, y, dp[x][y] - x - y);
    bt[1].update(d, x, m-y+1, dp[x][y] - x + y);
    bt[2].update(d, n-x+1, m-y+1, dp[x][y] + x + y);
    bt[3].update(d, n-x+1, y, dp[x][y] + x - y);
}
void qry(int d, int x, int y) {
    int& res = dp[x][y]; res = inf;
    res = min(res, bt[0].query(d-1, x, y) + x + y);
    res = min(res, bt[1].query(d-1, x, m-y+1) + x - y);
    res = min(res, bt[2].query(d-1, n-x+1, m-y+1) - x - y);
    res = min(res, bt[3].query(d-1, n-x+1, y) - x + y);
}

struct node { int x, y; };
vector<node> g[N*N];

int p;
int main() {
    fast;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i)
        for (int j = 1, x; j <= m; ++j) {
            cin >> x; g[x].push_back({i, j});
        }
    for (auto &i : bt) i.init();
    for (auto [x, y] : g[1]) {
        dp[x][y] = x - 1 + y - 1;
        upd(1, x, y);
    }
    for (int d = 2; d <= p; ++d) {
        for (auto [x, y] : g[d]) {
            qry(d, x, y);
        }
        for (auto [x, y] : g[d]) {
            upd(d, x, y);
        }
    }
    int x = g[p][0].x, y = g[p][0].y;
    cout << dp[x][y] << '\n';
    return 0;
}