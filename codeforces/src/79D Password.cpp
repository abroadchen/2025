//
// Created by Psy.C on 2025/11/6.
//
/*
*N = 40010: 最大位置数
M = (1<<20)|10: 状态数（约100万）
K = 30: 最大关键点数
inf = 1e9: 无穷大值
*n, k, m: 位置数、关键点对数、跳跃方式数
a[N]: 标记关键点的数组
l[N]: 跳跃长度数组
val[K][K]: 关键点间最短距离矩阵
d[N]: BFS距离数组
f[M]: DP状态数组
sz[M]: 每个状态中1的个数
lb[N]: 每个状态最低位的位置
 *
*初始化距离数组，起点距离为0
对每个位置u，可以向前或向后跳跃l[i]步
计算从x到所有可达位置的最短距离
 *
*处理k个关键点对：对每个位置x，在a[x]和a[x+1]处进行异或操作
这样标记出需要配对的关键点
*统计标记为1的位置数量tot
将这些关键点重新编号存储在a数组中
 *
*计算所有关键点对之间的最短距离：
t = 1<<tot: 总的状态数
对每个关键点i，运行BFS计算到其他点的最短距离
存储在val矩阵中
 *
 *预处理每个状态的1的个数和最低位位置
*状态压缩DP：
从后往前遍历所有状态
对于每个有效状态i，找到最低位x
尝试将x与状态中的其他点j配对
更新新状态i^(1<<(x-1))^(1<<(j-1))的最小值
 *
*奇数的1的个数 = i>>1（即i/2）的1的个数 + 1
因为奇数最低位是1，右移后会丢失这个1，所以要加回来
*奇数的二进制表示最低位是1
所以最低位的1就在第1位
因此 lb[i] = 1
*偶数的最低位是0，所以最低位的1在更高位
右移一位后，原来的位置会增加1
所以 lb[i] = lb[i>>1] + 1
 *
*检查状态i的第j位是否为1
如果是1，说明第j个元素在当前未匹配集合中
如果是0，说明第j个元素已经匹配过了，跳过
 *
*将第x个和第j个元素配对
从状态i转移到新状态（去除x和j位）
 *
*BFS预处理：O(k × n)
DP：O(k² × 2^k)
总体：O(k × n + k² × 2^k)
 */
#include <cstdio>
#include <queue>
#define rep(i,n) for (int i = 1; i <= (n); ++i)
using namespace std;


const int N = 40010, M = (1<<20)|10, K = 30, inf = 1e9;
int n, k, m, a[N], l[N], val[K][K],
d[N], f[M], sz[M], lb[N];

void bfs(int x) {
    rep(i,n + 1) d[i] = inf;
    d[x] = 0;
    queue<int> q;
    while (!q.empty()) q.pop();
    q.push(x);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        rep(i,m) {
            int v = u + l[i];
            if (v <= n + 1 && d[v] == inf) {
                d[v] = d[u] + 1;
                q.push(v);
            }
            v = u - l[i];
            if (v > 0 && d[v] == inf) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

void minn(int& x, int y) { if (x > y) x = y; }
int main() {
    scanf("%d%d%d", &n, &k, &m);
    for (int i = 1, x; i <= k; ++i) {
        scanf("%d", &x);
        a[x] ^= 1;
        a[x + 1] ^= 1;
    }
    int tot(0);
    rep(i,n + 1) if (a[i]) a[++tot] = i;
    rep(i,m) scanf("%d", &l[i]);
    int t = 1<<tot;
    rep(i,tot) {
        val[i][i] = inf;
        bfs(a[i]);
        for (int j = i + 1; j <= tot; ++j) {
            val[j][i] = val[i][j] = d[a[j]];
        }
    }
    for (int i = 0; i < t - 1; ++i) f[i] = inf;
    for (int i = 1; i < t; ++i) {
        if (i & 1) sz[i] = sz[i>>1] + 1, lb[i] = 1;
        else sz[i] = sz[i>>1], lb[i] = lb[i>>1]+1;
    }
    for (int i = t - 1; i >= 0; --i) {
        if (f[i] == inf) continue;
        int x = lb[i];
        rep(j,tot) {
            if (x == j) continue;//不能自己和自己配对
            if (i >> j-1 & 1); else continue;//状态i的第j位是否为1
            minn(f[i^(1 << x-1)^(1 << j-1)], f[i] + val[x][j]);
        }
    }
    printf("%d\n", f[0] == inf ? -1 : f[0]);
    return 0;
}