//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
f[i][x][s]、g[i][x][s]：两套 DP 数组，i 是处理到前 i 项，x 是"已选取的数量"，s 是一个 0/1 状态位。
inf 极大值，把无意义状态标成不可达
读入 n 个三元组 (A[i], B[i], C[i])，并把 A[i] 原地减去 B[i]（变成 A[i]-B[i]，之后 A 表示"净差值/超额"）。这暗示 A、B 原本是两种数值，我们关心它们的差。
追加一个哨兵元素：A[++n]=inf，并 C[n]=A[n]=inf（哨兵拥有极大容量/极大值）。
前缀和：
ha[i] = ha[i-1] + A[i]：A 序列前缀和（净差值累计）。
hb[i] = hb[i-1] + B[i]：B 序列前缀和。
这两个前缀和会大量参与转移里的公式
三重循环遍历所有状态 (i, x, s)。
边界：i==0（没处理任何物品）时，f 和 g 都初始化为 0（空状态无花费）。
其他情况先都置 inf（未可达）

第一段转移（主转移：枚举前一个"被占用"位置 y）
枚举"上一步结束时处于状态 (i, y, s) 的分量 g[i][y][s]"，然后尝试加进 x-y-1 个新东西来填到 x。逐行：

t = g[i][y][s]：取出 g 的候选值。
z = ha[i]*s + hb[i]*(y+1) - t*K：
这是某种 "资源总量 - 已消耗×K" 的剩余资源计算。
具体是：ha[i]*s（A 前缀和 × 状态位）+ hb[i]*(y+1)（B 前缀和 × (y+1)）再减去 t*K（已花费的 K 倍）。
ms = C[i] - (x-y)*B[i]：
(x-y)*B[i] 是"新增的 x-y 个都算 B[i] 量"的总和，用 C[i]（容量）减掉得剩余可用上限 ms。
c = (z - ms + (K-1)) / K；if(c<0) c=0;
向上取整除法：(z-ms+K-1)/K，即需要用多少个"单位 K"来补足 z 到不低于 ms。
若算出来是负的，说明不用补，c=0。
if (z - c*K >= 0)：
条件：补完 c 个 K 之后资源仍 ≥0（不越界）。
满足则更新 f[i][x][s]：
t = t + c + f[i-1][x-y-1][0]：本步花费 c，再加上子问题 f[i-1][x-y-1][0]（前 i-1 项里用 x-y-1 个、状态位 0 的最小花费）。
取最小更新 f。
ss：子问题 f 值。
tt = (hb[i-1]*(x-y)-ss*K + K-1)/K：又一个向上取整，计算子问题里需要补的 K 单位数。
t = g[i][y][s] + c + ss + tt：总花费 = g 原值 + 本步c + 子问题花费 + 子问题补足。
条件：ha[i]*s + hb[i]*(x+1) - t*K >= 0（资源足够）才更新 g

第二段转移（直接继承 / "不切分"的情况）
条件 A[i]*s + B[i]*(x+1) <= C[i]：
当前这一项在状态 s、填 x+1 个时的总需求不超过容量 C[i]，说明不必分块，可以"整项放入，不额外产生新块"。
继承：t = f[i-1][x][s]，若更小则更新 f[i][x][s]（这不额外分段、直接把第 i 项接进上一段）。
补足计算：tt = (向上取整) 算出需要的补充分量，t += tt。
条件满足则更新 g[i][x][s]
最终答案取 f[n][m][1]：处理完全部 n 个（含哨兵）、恰好选了 m 个、状态位 s=1 的最小花费。
状态位 s=1 通常表示"最后这一段处于开启/活跃状态"（比如"当前这一段已被选中/占用"）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ll long long
using namespace std;

constexpr ll N = 220, inf = 1e17-1;

int n, m, K;
ll A[N], B[N], C[N], ha[N], hb[N], f[N][N][2], g[N][N][2];
int main() {
    fast;
    cin >> n >> m >> K;
    rep(i,1,n) cin >> A[i] >> B[i] >> C[i], A[i] -= B[i];
    A[++n] = inf; C[n] = A[n];
    rep(i,1,n) ha[i] = ha[i-1] + A[i], hb[i] = hb[i-1] + B[i];
    rep(i,0,n) rep(x,0,m) rep(s,0,1) {
        if (i == 0) { f[i][x][s] = g[i][x][s] = 0; continue; }
        f[i][x][s] = g[i][x][s] = inf;
        rep(y,0,x-1) {
            ll t = g[i][y][s];
            if (t >= inf) continue;
            ll z = ha[i]*s + hb[i]*(y+1) - t*K;
            ll ms = C[i] - (x-y)*B[i], c = (z-ms+(K-1))/K;
            if (c < 0) c = 0;
            if (z-c*K >= 0) {
                t = t + c + f[i-1][x-y-1][0];
                if (t < f[i][x][s]) f[i][x][s] = t;
                ll ss = f[i-1][x-y-1][0];
                if (ss >= inf) continue;
                ll tt = hb[i-1]*(x-y)-ss*K; tt = (tt + (K-1))/K;
                if (tt < 0) tt = 0;
                t = g[i][y][s] + c + ss + tt;
                if (ha[i]*s + hb[i]*(x+1) - t*K >= 0 && t < g[i][x][s]) g[i][x][s] = t;
            }
        }
        if (A[i]*s+B[i]*(x+1) <= C[i]) {
            ll t = f[i-1][x][s];
            if (t < f[i][x][s]) f[i][x][s] = t;
            if (t >= inf) continue;
            ll tt = ha[i-1]*s+hb[i-1]*(x+1)-t*K; tt = (tt + (K-1))/K;
            if (tt < 0) tt = 0;
            t += tt;
            if (t*K <= ha[i]*s+hb[i]*(x+1) && t < g[i][x][s]) g[i][x][s] = t;
        }
    }
    ll ans = f[n][m][1];
    cout << ans << '\n';
    return 0;
}