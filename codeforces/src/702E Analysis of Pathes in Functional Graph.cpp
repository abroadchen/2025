//
// Created by Psy.C on 2026/4/18.
//
/**
x: 查询的跳跃步数
sum[i][j]: 从节点i开始，跳跃2^(j-1)步的权值和
g2[i][j]: 从节点i开始，跳跃2^(j-1)步后到达的节点

从位置pos开始，跳跃x步后的权值和
使用二进制分解：将x分解为2的幂次之和
g = x: 当前待处理的步数
c = 1: 当前处理的倍增层数
s = 0: 累积权值和
if (g%2): 如果当前位是1，则加上对应的权值和并跳跃
g >>= 1: 右移一位，处理下一位
返回跳跃过程中经过节点的最小权值

n: 节点数
f[i]: 节点i的下一步目标
w[i]: 节点i的权值
f[i]++: 将索引调整为从1开始
g2[i][0] = i: 跳跃2^0=1步到达自己
g2[i][1] = f[i]: 跳跃2^1=2步到达f[i]
倍增预处理：跳跃2^i步 = 先跳跃2^(i-1)步，再从那里跳跃2^(i-1)步
g2[j][i] = g2[g2[j][i-1]][i-1]
sum[i][1] = w[i]: 跳跃2^0=1步的权值和就是w[i]
sum[j][i] = sum[j][i-1] + sum[g2[j][i-1]][i-1]:
跳跃2^i步的权值和 = 前半段跳跃的权值和 + 后半段跳跃的权值和
类似权值和预处理，但计算最小值
对每个起始点，输出跳跃x步的权值和和最小权值
预处理：O(n log x)
单次查询：O(log x)
总时间复杂度：O(n log x)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5, M = 45;

ll x, sum[N][M], g2[N][M];
ll get(int pos) {
    ll g = x, c = 1, s = 0;
    while (g) {
        if (g%2) {
            s += sum[pos][c];
            pos = g2[pos][c];
        }
        c++;
        g >>= 1;
    }
    return s;
}

ll mn2[N][M];
ll get_mn(int pos) {
    ll g = x, c = 1, mn = LONG_MAX;
    while (g) {
        if (g%2) {
            mn = min(mn, mn2[pos][c]);
            pos = g2[pos][c];
        }
        c++;
        g >>= 1;
    }
    return mn;
}

int n, f[N];
ll w[N];
int main() {
    fast;
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> f[i], f[i]++;
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 1; i <= n; ++i) g2[i][0] = i, g2[i][1] = f[i];
    for (int i = 2; i <= 40; ++i)
        for (int j = 1; j <= n; ++j)
            g2[j][i] = g2[g2[j][i-1]][i-1];
    for (int i = 1; i <= n; ++i) sum[i][1] = w[i];
    for (int i = 2; i <= 40; ++i)
        for (int j = 1; j <= n; ++j)
            sum[j][i] = sum[j][i-1] + sum[g2[j][i-1]][i-1];
    for (int i = 1; i <= n; ++i) mn2[i][1] = w[i];
    for (int i = 2; i <= 40; ++i)
        for (int j = 1; j <= n; ++j)
            mn2[j][i] = min(mn2[j][i-1], mn2[g2[j][i-1]][i-1]);
    for (int i = 1; i <= n; ++i)
        cout << get(i) << ' ' << get_mn(i) << '\n';
    return 0;
}