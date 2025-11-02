//
// Created by Psy.C on 2025/11/2.
//
/*
*N = 200: 坐标偏移量，用于将坐标从负数范围映射到正数范围
M = 401: 状态空间大小，用于dp数组的维度
 *
*n: 移动向量的数量
d: 最大移动距离限制
dp[M][M][2][2][2]: 记忆化搜索的状态数组，维度分别为x坐标、y坐标、f1标志、f2标志、玩家轮次
r: 存储可选的移动向量列表
 *
*x, y: 当前坐标位置
f1, f2: 两位玩家是否已使用交换操作的标志位
p: 当前玩家轮次（0表示Anton，1表示Dasha）
 *
 *初始化结果为0（代表当前玩家必败）
*如果是Anton的回合(p=0)且还没使用交换操作(!f1)，可以选择交换坐标
如果是Dasha的回合(p=1)且还没使用交换操作(!f2)，可以选择交换坐标
p^1表示切换玩家轮次，res |= !...表示只要有一种走法能让对手处于必败态，当前玩家就能获胜
 *
*遍历所有可选的移动向量
x1 = x + r[i].first - N, y1 = y + r[i].second - N: 计算实际移动后的坐标（考虑了坐标偏移）
if (x1 * x1 + y1 * y1 > d * d) continue;: 检查移动距离是否超过限制d
res |= !dfs(...): 尝试这种移动，如果能让对手处于必败态，则当前玩家能获胜
 *将计算结果保存到dp数组中并返回
 *
 *将坐标加上偏移量N，避免负数坐标
 *初始化dp数组为-1，表示未访问状态
 *
 */
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

const int N = 2e2, M = 4e2+1;
int n, d, dp[M][M][2][2][2];
vector<pair<int,int> > r;

int dfs(int x, int y, int f1, int f2, int p) {
    if (x < 0 || x >= M || y < 0 || y >= M) return 0;
    if (dp[x][y][f1][f2][p] != -1) return dp[x][y][f1][f2][p];
    int res(0);
    if (!p && !f1) res |= !dfs(y, x, 1, f2, p^1);
    else if (p && !f2) res |= !dfs(y, x, f1, 1, p^1);
    for (int i = 0; i < n; ++i) {
        int x1 = x + r[i].first - N, y1 = y + r[i].second - N;
        if (x1 * x1 + y1 * y1 > d * d) continue;
        res |= !dfs(x1 + N, y1 + N, f1, f2, p^1);
    }
    dp[x][y][f1][f2][p] = res;
    return res;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int x, y; cin >> x >> y >> n >> d;
    x += N; y += N;
    r.resize(n);
    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < n; ++i) cin >> r[i].first >> r[i].second;
    if (dfs(x, y, 0, 0, 0)) cout << "Anton\n";
    else cout << "Dasha\n";
    return 0;
}