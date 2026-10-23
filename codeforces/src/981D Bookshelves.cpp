//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
n, k：n 个数、要划分成 k 段
读入 sum[i]（原始数组值），然后 sum[i] += sum[i-1] 变成前缀和。
之后区间 (j+1..i) 的和 = sum[i] - sum[j]
能否把前 n 个数划分成恰好 k 段，使得每一段的和按位与上 x 后仍为 x（即每段和都包含 x 的每一位，val & x == x）。

d[i][h]（bool 语义）：是否存在一种划分，把前 i 个数分成恰好 h 段，且每段的和都满足 (段和 & x) == x。
初始化（第一段）：
if ((sum[i]&x)==x) d[i][1]=1;
若前缀和 sum[i]（即第 1 段 = 整个 [1..i]）包含 x，则可作为 1 段。
转移：
枚举上一段结束位置 j（j < i）。
sum[i]-sum[j] 是段 (j+1..i) 的和；若 ((sum[i]-sum[j])&x) != x（这一段不包含 x 的全部位），则跳过。
否则，d[i][h] |= d[j][h-1]：前 j 个数分成 h-1 段可行，则前 i 个数可分成 h 段。
返回 d[n][k]：能否分成恰好 k 段。
本质：这是一个"可行性 DP"，判断某个候选位模式 x 是否可作为"每一段和的按位与的超集"被实现
ans 从 0 开始，从最高位 bit60 到 bit0 逐一尝试。
对每一位 i：尝试把这一位加到 ans 上（ans | (1ll<<i)），调用 check 判断是否可行。
若可行，就把它保留（ans |= 1ll<<i）；否则跳过这一位。
最终 ans 就是所有段的按位与所能达到的最大值（贪心构造最大可行掩码）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 51;

ll d[N][N], sum[N];
int n, k;
ll check(ll x) {
    memset(d, 0, sizeof(d));
    int i, j;
    rep(i,n) {
        if ((sum[i]&x) == x) d[i][1] = 1;
        rep(j,i-1) {
            if (((sum[i]-sum[j])&x) != x) continue;
            for (int h = 2; h <= min(k, i); h++)
                d[i][h] |= d[j][h-1];
        }
    }
    return d[n][k];
}



int main() {
    fast;
    cin >> n >> k;
    int i;
    rep(i,n) cin >> sum[i], sum[i] += sum[i-1];
    ll ans = 0;
    for (i = 60; i >= 0; i--)
        if (check(ans|(1ll<<i))) ans |= 1ll<<i;
    cout << ans << '\n';
    return 0;
}