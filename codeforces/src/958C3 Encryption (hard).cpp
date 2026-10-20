//
// Created by Psy.C on 2026/10/20.
//
/**
sum[i] 为前 i 个元素和模 p。区间 [l+1, j] 的和模 p 为 (sum[j]-sum[l]+p)%p
dp[j] = 将"当前处理到的前缀"分成 j 段的最优（最小）成本
注意这里 dp 是一维滚动数组，每次读入新元素 s[i] 后就更新一次分段数
分成 j 段时，考虑最后一段的起点（上一个切分点 l）：

dp[j] = min over l<j of  ( 前 l 个分成 j-1 段的最优值  +  最后一段的代价 )
最后一段是 [l+1, i]，其和模 p = (s[i] - s[l] + p) % p。

这个模值 (s[i]-s[l]+p)%p 与 s[l] 的相对大小有关，分成两种情况：

当 s[l] ≤ s[i] 时：(s[i]-s[l]+p)%p = s[i]-s[l]（因为差值非负且小于 p）

转移：dp_prev[l] + (s[i]-s[l])
即 (dp_prev[l] - s[l]) + s[i]
当 s[l] > s[i] 时：需要 +p 借位

(s[i]-s[l]+p)%p = s[i]-s[l]+p
转移：dp_prev[l] + (s[i]-s[l]+p) = (dp_prev[l]-s[l]+p) + s[i]
由于要快速查询"满足 s[l] 在某范围的 dp_prev[l] - s[l]（±p）最小值"，引入两棵二维树状数组：

c[0]（第一棵）‍：维护条件 s[l] ≤ x 的最小值，槽位按 s[l] 值放：

更新 update(0, j, s[i], dp[j]-s[i])：把 dp[j]-s[i] 按 s[i] 值存入第 j 棵 BIT
查询 query(0, j-1, s[i])：找所有 s[l] ≤ s[i] 的分成 j-1 段的最优 dp-s[l]
c[1]（第二棵）‍：维护 s[l] > x 的情况，用 p-s[i] 倒置索引：

更新 update(1, j, p-s[i], dp[j]-s[i]+p)：按 p-s[l] 值存入
查询 query(1, j-1, p-s[i])：找所有 s[l] > s[i] 的分成 j-1 段的最优 dp-s[l]+p
dp[j] = min( query(0, j-1, s[i]),   // s[l] <= s[i] 的情形
             query(1, j-1, p-s[i])  // s[l] >  s[i] 的情形
           ) + s[i];
最后统一加上 s[i]（对应前面推导中的尾部 +s[i]）

计算 dp[j]（当前用 s[i] 作为新元素结尾）时，切分点 l 必须满足 l < i，即不能把 i 自己当切分点。如果边算边更新，当前 i 的 s[i] 会被当作可用切分点，导致错误（最后一段为空）。所以先全部查询算出 dp[j]，再统一把 s[i] 作为新切分点更新 BIT，供下一轮（下一元素）‍使用。
update(0, 0, p+1, 0);   // 分成0段时，切分点 l=0（s[0]=0），
                        // 这里按 p+1 处放0？实际上是起点标记
update(1, 0, 0, 0);
初始状态 dp[0]=0（0 个元素分成 0 段），切分点 s[0]=0。为了能在第一分段时正确转移，把"前缀和=0 且分段 0 的 dp=0"放入 BIT。第二行的 p-s[i]=p-0=p 也撮合第一段从 l=0 开始的转移（s[0]=0 ≤ s[i] 或 > s[i] 两种都可能，因此两棵都初始化）。

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 110, M = 5e5+10, inf = 0x3f3f3f3f;

int p, c[2][N][N];
void update(int f, int t, int x, int w) {
    for (int i = x+1; i <= p+1; i+= i&-i)
        c[f][t][i] = min(c[f][t][i], w);
}
int query(int f, int t, int x) {
    int res = inf;
    for (int i = x+1; i; i-= i&-i)
        res = min(c[f][t][i], res);
    return res;
}

int n, k, dp[N], s[M];
int main() {
    fast;
    while (cin >> n >> k >> p) {
        memset(dp, inf, sizeof dp);
        for (int i = 1; i <= n; ++i) {
            cin >> s[i];
            s[i] = (s[i-1] + s[i]) % p;
        }
        for (int i = 0; i <= k; ++i)
            for (int j = 0; j <= p+1; ++j)
                c[0][i][j] = c[1][i][j] = inf;
        update(0, 0, p+1, 0); update(1, 0, 0, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= min(i,k); ++j)
                dp[j] = min(query(0,j-1,s[i]), query(1,j-1,p-s[i])) + s[i];
            for (int j = 1; j <= min(i,k); ++j) {
                if (dp[j] == inf) continue;
                update(0, j, s[i], dp[j]-s[i]);
                update(1, j, p-s[i], dp[j]-s[i]+p);
            }
        }
        cout << dp[k] << '\n';
    }
    return 0;
}