//
// Created by Psy.C on 2026/9/17.
//
/**
n 个位置，p 次启动机会，K 每次覆盖长度
读 A 集合（a[y]=1）和 B 集合（b[y]=1）的位置
若 p*K >= 2n（总覆盖长度足够覆盖每个位置两次），则每个位置都能被两条覆盖扫到，答案 = 每个位置 a[i]|b[i] 之和（即位置属于 A 或 B 就得分，且只算一次
dp 初始化为极小负值（-inf），边界状态 dp[0][0][0][0]=0（还没开始，剩余都 0）。
用 i&1 做滚动数组，节省内存。每轮把当前行重置为 -inf
这 8 种转移表示在位置 i 上，A 和 B 两条覆盖各自可能的状态：
k：A 覆盖在位置 i 是否正在有效（k>0 表示 A 当前覆盖到本格），加上后消耗 1 格。
l：同理 B。
每条覆盖在本格有三种选择：已在进行中（k/l 直接减1）‍、新启动（j+1，并把剩余设为 K-1）‍、不做（剩余减1但不加分）‍。
得分规则：
只有 A 覆盖 → 加 a[i]。
只有 B 覆盖 → 加 b[i]。
两条都覆盖 → 加 a[i]|b[i]（合并，因为两条覆盖同一个格子，奖励……其实是 a[i]与b[i]取或）。
每次"新启动"消耗一次 p 机会（j+1 或 j+2）。
约束：位置 i 上 A 和 B 各自最多只能有一个覆盖（所以不会出现"A既用旧又新开"两条同时占本格）
遍历最后一个位置的所有状态（剩余覆盖可在任意值），取最大值输出
*/
#include <bits/stdc++.h>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}
void upd(int& x, int y) { if (x < y) x = y; }//取最大值更新

constexpr int N = 1010, M = 60;
int a[N], b[N], dp[2][N][M][M];
int main() {
    int n = rd(), p = rd(), K = rd();
    int x = rd();
    for (int i = 1; i <= x; ++i){
        int y = rd(); a[y] = 1;
    }
    x = rd();
    for (int i = 1; i <= x; ++i){
        int y = rd(); b[y] = 1;
    }
    if (p * K >= (n << 1)){
        int ans = 0;
        for (int i = 1; i <= n; ++i) ans += a[i] | b[i];
        return printf("%d\n", ans), 0;
    }
    memset(dp, -0x3f, sizeof(dp)); dp[0][0][0][0] = 0;
    for (int i = 1; i <= n; ++i){
        int now = i & 1, pre = now ^ 1;
        memset(dp[now], -0x3f, sizeof(dp[now]));
        for (int j = 0; j <= p; ++j)
            for (int k = 0; k <= K; ++k)
                for (int l = 0; l <= K; ++l){
                    int tmp = dp[pre][j][k][l];
                    upd(dp[now][j][max(k - 1, 0)][max(l - 1, 0)], tmp);
                    if (k) upd(dp[now][j][k - 1][max(l - 1, 0)], tmp + a[i]);
                    upd(dp[now][j + 1][K - 1][max(l - 1, 0)], tmp + a[i]);
                    if (l) upd(dp[now][j][max(k - 1, 0)][l - 1], tmp + b[i]);
                    upd(dp[now][j + 1][max(k - 1, 0)][K - 1], tmp + b[i]);
                    if (k && l) upd(dp[now][j][k - 1][l - 1], tmp + (a[i] | b[i]));
                    if (k) upd(dp[now][j + 1][k - 1][K - 1], tmp + (a[i] | b[i]));
                    if (l) upd(dp[now][j + 1][K - 1][l - 1], tmp + (a[i] | b[i]));
                    upd(dp[now][j + 2][K - 1][K - 1], tmp + (a[i] | b[i]));
                }
    }
    int ans = 0;
    for (int j = 0; j <= p; ++j)
        for (int k = 0; k <= K; ++k)
            for (int l = 0; l <= K; ++l) upd(ans, dp[n & 1][j][k][l]);
    printf("%d\n", ans);
    return 0;
}