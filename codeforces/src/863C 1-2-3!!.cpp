//
// Created by Psy.C on 2026/10/3.
//
/**
N = 62：因为 k ≤ 1e18 < 2^60，所以倍增表只需 60+ 层（62 够了）。
f[i][s]：从状态 s 走 2^i 步后到达的状态。
sum[i][s]、sum2[i][s]：从状态 s 走 2^i 步中，第一种 / 第二种得分的累计。
9 种状态：(x,y) 用 (x-1)*3 + y 编码为 0..8。
读入 k（步数）和初始 x,y，再读两张 3×3 转移表 a、b
对每种状态 s=(i,j)：
一步后状态变为 (u,v) = (a[i][j], b[i][j])，编码 (u-1)*3+v 存入 f[0][s]（走 2⁰=1 步）。
得分判断：这三组 (i,j) ∈ {(1,3),(2,1),(3,2)} 是"第一种赢"（石头剪刀布的胜负关系：1 胜 3，2 胜 1，3 胜 2），此时 sum[0][s]=1（给 x 方 +1）。
反之 (j,i) 的那三组是"第二种赢"，sum2[0][s]=1（给 y 方 +1）。
平局则都为 0。
这证实了这是石头剪刀布式的胜负判定：1>3, 2>1, 3>2 的循环克关系
标准的二进制倍增：
走 2^i 步 = 先走 2^(i-1) 步到 mid，再走 2^(i-1) 步。
f[i][s] = f[i-1][mid]：最终状态。
sum[i][s] = sum[i-1][s] + sum[i-1][mid]：前一半得分 + 后一半得分（得分总和）。
同理 sum2
初始状态 cur。
按 k 的二进制位从低到高：若第 i 位为 1，则"应用"这一段的转移——累加 sum/sum2，并把当前状态推进到 f[i][cur]。
最终 a1、a2 分别是走 k 步后两方的总得分。
复杂度 O(N × 9) = O(60×9)，极快，适用于 k 极大（1e18）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define rep(i,n) for (int i = 1; i <= n; ++i)
using namespace std;
constexpr int N = 62;
int a[4][4], b[4][4], f[N][10];
ll sum[N][10], sum2[N][10];
int main() {
    fast;
    ll k; int x, y; cin >> k >> x >> y;
    rep(i,3) rep(j,3) cin >> a[i][j];
    rep(i,3) rep(j,3) cin >> b[i][j];
    rep(i,3) rep(j,3) {
        int s = (i-1)*3 + j, u = a[i][j], v = b[i][j];
        f[0][s] = (u-1)*3 + v;
        if ((i==1&&j==3) || (i==2&&j==1) || (i==3&&j==2))
            sum[0][s] = 1, sum2[0][s] = 0;
        else if ((j==1&&i==3) || (j==2&&i==1) || (j==3&&i==2))
            sum[0][s] = 0, sum2[0][s] = 1;
        else sum[0][s] = 0, sum2[0][s] = 0;
    }
    for (int i = 1; i < N; ++i) rep(s,9) {
        int mid = f[i-1][s];
        f[i][s] = f[i-1][mid];
        sum[i][s] = sum[i-1][s] + sum[i-1][mid];
        sum2[i][s] = sum2[i-1][s] + sum2[i-1][mid];
    }
    int cur = (x-1)*3 + y;
    ll a1 = 0, a2 = 0;
    for (int i = 0; i < N; ++i) {
        if (k&(1ll<<i)) {
            a1 += sum[i][cur]; a2 += sum2[i][cur];
            cur = f[i][cur];
        }
    }
    cout << a1 << ' ' << a2;
    return 0;
}