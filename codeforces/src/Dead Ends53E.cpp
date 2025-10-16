//
// Created by Psy.C on 2025/10/15.
//
/*
*n: 节点数
m: 边数
k: 目标参数
h[N]: 邻接表，h[i]表示与节点i相连的节点集合（用位掩码表示）
f[1<<N][1<<N]: 状态转移数组，f[mask][subset]表示某种状态下的方案数
p[1<<N]: 每个位掩码中1的个数（popcount）
 *
*读取m条边，构建邻接表：
读取边的两个端点u和v（转换为0-based索引）
在邻接表中记录连接关系（双向图）
初始化f数组：对于每条边构成的集合，设置初始状态值为2
 *
*预处理计算每个位掩码中1的个数（汉明重量）：
p[i] = p[i>>1] + (i&1) 表示i的1的个数等于i右移一位后的1的个数加上最低位的值
 *
 *遍历所有可能的节点集合（用位掩码表示）
*遍历i的所有子集（Gosper's Hack算法的变种）：
j从i开始，每次迭代j变为(i-1)&i，这样可以遍历i的所有子集
 *
*计算新状态cur，并更新状态转移方程
cur表示在子集中移除v节点并添加k节点后的新子集
将当前方案数累加到新状态中
 *
*计算最终答案：
遍历所有可能的子集i
如果子集i中1的个数等于k，则将对应的状态方案数加到答案中
 */
#include <ios>
#include <iostream>
using namespace std;

typedef long long ll;
const int N = 10;
int n, m, k, h[N], f[1<<N][1<<N], p[1<<N];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m >> k;
    while (m--) {
        int u, v; cin >> u >> v; u--, v--;
        h[u] |= 1 << v, h[v] |= 1 << u;
        f[1 << u | 1 << v][1 << u | 1 << v] = 2;
    }
    for (int i = 1; i < 1 << n; ++i) p[i] = p[i>>1] + (i&1);
    for (int i = 1; i < 1 << n; ++i) {
        for (int j = i; j; j = (j - 1) & i) {
            if (!f[i][j]) continue;//如果当前状态没有方案数，则跳过
            f[i][j] /= p[j];//对方案数进行某种归一化处理
            for (int k = 0; k < n; ++k) {
                if (i >> k & 1) continue;//如果节点k已经在当前集合i中，则跳过
                int msk = h[k] & i;//计算节点k与当前集合i中节点的连接情况
                for (int v = 0; v < n; ++v) {
                    if (!(msk >> v & 1)) continue;//如果节点v不在msk中（即节点k与节点v不相连），则跳过
                    int cur = j ^ (j & 1 << v) ^ 1 << k;
                    f[i | 1 << k][cur] += f[i][j];
                }
            }
        }
    }
    ll ans(0);
    for (int i = 0; i < 1 << n; ++i) {
        if (p[i] == k) ans += f[(1 << n) - 1][i];
    }
    cout << ans << "\n";
    return 0;
}