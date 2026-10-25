//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
a：总长度/站位
n：需要覆盖的区间个数
m：设备种类数（M=2010，m≤2000）
dis[]：差分数组，用于标记哪些位置处于"需要设备"的状态
w[i]：第 i 种设备的价格
pos[i]：第 i 种设备所在的购买位置
u[x]：位置 x 上最便宜的设备编号
v[i][j]：DP表
差分数组构建：对每个区间 [l+1, r+1]，做差分 dis[l]++、dis[r]--。这样后面累加 sum += dis[i] 就能知道位置 i 是否在所有区间覆盖内（sum>0 表示处于某个需要设备的区间中）
每种设备 i 在位置 x（自增1）出售，价格 p。
pos[i] = 购买位置，w[i] = 价格。
u[x]：记录位置x上价格最低设备的下标。若新设备比当前位置记录的最低价还低，则更新 u[x]。
u[x] 的作用：在 DP 中，若在位置 i 需要"买一个设备"，会优先考虑位置 i 上最便宜的那个
状态定义： v[i][j] = 走到位置 i，并且当前正在使用设备 j（或 j=0 表示没在使用任何设备）时的最小花费。

转移分析（对每个位置 i）：

转移1 v[i-1][j] + w[j]：继续使用当前的设备 j 到达 i（花费 w[j]，因为是"按长度计费"的——这里 w[j] 相当于"每走一步的续费"或"设备 j 的单价"，每到一个位置都要付一次）。

等等，这里 w[j] 相加了 a 次，说明 w[j] 是每个位置单位长度需要的成本，总成本 = 使用距离 × w[j]。这与"伞/灯的租赁是按使用长度计费"一致。

转移2 if (!sum)：当前位置 i 不在任何需要覆盖的区间内（sum==0），那么可以不用任何设备，从上一步的任何状态 j 转过来（状态变为0，表示没设备）。

如果 sum>0（处于需要覆盖的区间），就不能"不用设备"，所以不能转移到状态0（除了保持原设备或新买设备）。

转移3 if (u[i])：当前位置 i 能买到设备（u[i] 是该位置最便宜的设备），则可以在 i 处新买设备 u[i]，从任意上一步状态 j 转过来，花费 w[u[i]]（购买/启动成本）。

注意：转移1和转移3的区别——转移1是"延续已有设备"（每走一步付 w[j]），转移3是"在位置 i 新买设备 u[i]"（付一次 w[u[i]] 当作这一路段的成本）。实际上这里 w 的含义是"单位长度价格"，所以买设备后每走一个位置都要付，转移1就在做这个；转移3表示从 i 起改用新设备。
从终点位置 a 的所有可能"当前设备"状态中取最小值。若仍为 inf → 无法完成覆盖 → 输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5, M = 2010, inf = 0x3f3f3f3f;

int a, n, m, dis[N], w[M], u[M], pos[M], v[M][M];
int main() {
    fast;
    cin >> a >> n >> m; a++;
    for (int i = 0, l, r; i < n; i++) {
        cin >> l >> r; l++, r++;
        dis[l]++, dis[r]--;
    }
    memset(w, inf, sizeof(w));
    for (int i = 1, x, p; i <= m; i++) {
        cin >> x >> p; x++;
        pos[i] = x; w[i] = p;
        if (p < w[u[x]]) u[x] = i;
    }
    memset(v, inf, sizeof(v)); v[0][0] = 0;
    int sum = 0;
    for (int i = 1; i <= a; i++) {
        sum += dis[i];
        for (int j = 0; j <= m; j++) {
            if (pos[j] > i) continue;
            if (j) v[i][j] = min(v[i][j], v[i-1][j]+w[j]);
            if (!sum) v[i][0] = min(v[i][0], v[i-1][j]);
            if (u[i]) v[i][u[i]] = min(v[i][u[i]], v[i-1][j]+w[u[i]]);
        }
    }
    int ans = inf;
    for (int i = 0; i <= m; i++) ans = min(ans, v[a][i]);
    if (ans == inf) cout << "-1\n"; else cout << ans << '\n';
    return 0;
}