//
// Created by Psy.C on 2026/9/15.
//
/**
i：已访问区间左端（当前停留在 i）
j：已访问区间右端
s ∈ {0,1}：0 表示当前停在左端 i，1 表示当前停在右端 j（或反过来，取决于实现）
值 = 走到当前状态的最小总路程（消耗的边权和 / 已访问点数相关）
f[2][N][N][2] 用滚动数组（cur 在两维之间异或切换）压缩"访问了几个点"这一维，while(--K) 每轮 DP 增加访问一个点
cc 是邻接代价矩阵，初始化为 INF（memset(…,1,…) 按字节填 1 得到 0x01010101，很大）。
f[0] 全部初始化为 INF。
初态：虚拟左端点 0 和右端点 n+1 视为"起点位置"。对每个真实节点 i：
f[0][0][i][1] = 0：从 0 出发，已访问区间 [0,i] 且停在右端 i，代价 0。
f[0][i][n+1][0] = 0：从 n+1 出发，区间 [i,n+1] 且停在左端 i，代价 0
每轮访问新点 k（k 是尚未访问、被夹在 i 和 j 之间的新节点，i<k<j）：

现有区间 [i,j] 停在端点：
若当前停在右端 j（状态 [1]），去访问 k：f[i][k][1]（新区间 [i,k] 停在右端 k）可来自 f[i][j][1] + cc[j][k]（从 j 走到 k）。
若当前停在左端 i（状态 [0]），访问 k 后停在新区间右端 k：f[i][k][1] 来自 f[i][j][0] + cc[i][k]。
同理，把 k 放在右端形成新区间 [k,j] 且停在左端 k（状态 [0]）也可由两侧端点转移。
本质是一个区间 DP：区间 [i,j] 表示已访问的连续节点，只能向中间"插"新点 k，通过从左右端点之一走过去访问 k，把区间向中间收缩。目标是访问完 K 个点
所有可能的状态取最小值作为最优总路程。
若最优值超过阈值 INF（1<<20，表示不可达），输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 85, inf = 1<<30, INF = 1<<20;
int cc[N][N], n, K, m, u, v, c;
int f[2][N][N][2], cur, ans(inf);
int main() {
    fast;
    memset(cc, 1, sizeof(cc));
    cin >> n >> K >> m;
    while (m--) {
        cin >> u >> v >> c;
        cc[u][v] = min(c, cc[u][v]);
    }
    memset(f[0], 1, sizeof(f[0]));
    for (int i = 1; i <= n; ++i)
        f[0][0][i][1] = f[0][i][n+1][0] = 0;
    while (--K) {
        cur ^= 1;
        memset(f[cur], 1, sizeof(f[cur]));
        for (int i = 0; i <= n-1; ++i)
            for (int j = i+2; j <= n+1; ++j)
                for (int k = i+1; k < j; ++k) {
                    f[cur][i][k][1] = min(f[cur][i][k][1],
                        min(f[!cur][i][j][1]+cc[j][k], f[!cur][i][j][0]+cc[i][k]));
                    f[cur][k][j][0] = min(f[cur][k][j][0],
                        min(f[!cur][i][j][0]+cc[i][k], f[!cur][i][j][1]+cc[j][k]));
                }
    }
    for (int i = 0; i <= n+1; ++i)
        for (int j = 0; j <= n+1; ++j)
            ans = min(ans, min(f[cur][i][j][0], f[cur][i][j][1]));
    if (ans > INF) ans = -1;
    cout << ans << '\n';
    return 0;
}