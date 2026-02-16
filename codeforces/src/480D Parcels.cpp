//
// Created by Psy.C on 2026/2/16.
//
/**
in: 进入时间
out: 离开时间
w: 需要的资源量
s: 可用资源量
v: 价值
n: 节点数量
s: 总资源量
f[N*2+5]: 辅助数组，用于状态转移
dp[i][w]表示考虑前i个节点且使用w资源时的最大价值

f[p[j].in]：在节点j开始时间点的状态值
dp[j][y]：处理节点j并分配y资源时获得的价值
f[p[j].in] + dp[j][y]：选择执行节点j时能达到的总价值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 500;

struct node {
    int in, out, w, s, v;
    void read() { cin >> in >> out >> w >> s >> v; }
} p[N];

int n, s, f[N*2+5], dp[N+5][N*2+5];
int main() {
    fast;
    cin >> n >> s;
    p[0] = {0, N<<1, 0, s, 0};//虚拟节点
    for (int i = 1; i <= n; ++i) p[i].read();
    sort(p, p + n + 1, [](const node &a, const node &b) {
        return a.out < b.out || (a.out == b.out && a.in > b.in);//后进先出
    });
    for (int i = 0; i <= n; ++i) {//遍历每个节点i（包括虚拟节点）
        for (int w = p[i].w; w <= s; ++w) {//遍历所有可能的资源分配量w（从当前节点所需资源到总资源量）
            int x = p[i].in;//当前时间点设为节点i的进入时间
            const int y = min(p[i].s, w - p[i].w);//可分配给之前节点的资源量
            f[x] = 0;
            ///检查所有之前处理过的节点j
            for (int j = 0; j < i; ++j) if (p[j].in >= p[i].in) {//进入时间不早于当前节点的节点
                while (x < p[j].out) {
                    x++;
                    f[x] = f[x-1];//将前一个时间点的状态值延续到当前时间点
                }
                f[x] = max(f[x], f[p[j].in] + dp[j][y]);
            }
            dp[i][w] = f[x] + p[i].v;//当前节点的价值加上之前最优解
        }
    }
    cout << dp[n][s] << '\n';//所有节点且使用全部资源时的最大价值
    return 0;
}