//
// Created by Psy.C on 2026/11/22.
//

/**
真正学会的起点..
把所有 dp 初始化为极小值（-0x3f3f3f3f 使非法状态不可达）。
dp[0][0][0] = 0：基准状态（还没处理任何值、尚未"借用"多余数字）
遍历每个值 i。
枚举 a、b、c ∈ {0,1,2}（因为三元组最多从每个值借 2 个出去）。
合法性：cnt[i]-a-b-c >= 0，即当前值 i 拥有的个数足以覆盖 a+b+c 的预留
dp[i-1][a][b]：上一值 i-1 的状态，其中"预留 a 个给 i"（即跨阶段三元组用到 i），"预留 b 个给 i+1"。
当前值 i 处理时：a 个已经和 i-1 组成连续三元组（跨阶段），剩下可支配的是 cnt[i] - a。
再从 i 中取 b 个预留给 i+1（下个连续三元组），取 c 个用来和 i-1、i、i+1 的 i 位置组成。实际标准是：剩下的 cnt[i]-a-b-c 个每 3 个组成同值三元组（三个相同数），所以 (cnt[i]-a-b-c)/3。
加上的 c：表示用 c 个和前面 a（i-1侧）、以及预留 b 一起凑连续三元组后 i 贡献的组数（这里 c 大概是"i 中用于组连续三元组的数量"计入 1 组）。
状态各维度含义细讲（以题目为准）：

a：值 i-1 借给 i 和 i+1 用（构成 x-1,x,x+1）的数量。
b：值 i 借给 i+1、i+2 用（构成 x,x+1,x+2）的数量。
c：值 i 与 i、i+1 构成 (x-1,x,x+1) 里 i 的贡献数。
每次转移里 + c 记下 i-1, i, i+1 这个连续三元组的一整组的收益。
因为每个值的一侧连续三元组最多用到前后各 2 个，所以 a,b,c 都只需枚举 0,1,2（3 种取值）。
输出处理完所有 m 个值后，没有向 m+1 预留任何数字（dp[m][0][0]，即 b=0, c=0）时的最大答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;

constexpr int N = 1e6+5;
int n, m, cnt[N], dp[N][3][3];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x; i <= n; i++) { cin >> x; cnt[x]++; }
    memset(dp, -0x3f, sizeof dp); dp[0][0][0] = 0;
    for (int i = 1; i <= m; i++) {
        rep(a,3) rep(b,3) rep(c,3)
            if (cnt[i]-a-b-c >= 0)
                dp[i][b][c] = max(dp[i][b][c],
                    dp[i-1][a][b]+(cnt[i]-a-b-c)/3+c);
    }
    cout << dp[m][0][0];
    return 0;
}