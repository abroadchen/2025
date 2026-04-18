//
// Created by Psy.C on 2026/4/17.
//
/**
n: 事件总数
k: 必须恰好发生的事件数
p[i]: 第i个事件发生的概率
dp[mask]: 状态mask下的概率（mask的二进制表示哪些事件发生了）
ans[i]: 第i个事件在恰好k个事件发生时的条件概率

当前状态是i（某些事件已发生）
要让第j个事件发生，转移到新状态 i|(1<<j)
从状态i转移到i|(1<<j)的概率是 p[j]/(1-sum)
这里的 1-sum 是剩余未发生事件的总概率
在当前状态下，已经有某些事件发生，它们的概率和是 sum
剩余未发生事件的概率和是 1-sum
为了确保在k次选择中恰好发生k个事件，需要进行概率归一化

时间复杂度：O(n × 2^n)
空间复杂度：O(2^n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1<<21;
int n, k;
double p[21], dp[N], ans[21];
int main() {
    fast;
    cin >> n >> k;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        if (p[i] > 0) cnt++;
    }
    k = min(k, cnt); //要求的k大于非零概率事件数，取较小值
    dp[0] = 1.;//没有任何事件发生概率为1
    for (int i = 0; i < 1<<n; ++i) {//遍历所有可能的状态
        cnt = 0;
        double sum = 0;
        for (int j = 0; j < n; ++j)
            if (i>>j&1) cnt++, sum += p[j];//当前状态中已发生事件数及概率和
        for (int j = 0; j < n; ++j)
            if (!(i>>j&1))//第j个事件还未发生
                dp[i|(1<<j)] += dp[i]*p[j]/(1.-sum);//转移到新状态
        if (cnt == k) {//恰好有k个事件发生
            for (int j = 0; j < n; ++j)
                if (i>>j&1) ans[j] += dp[i];//累加第j个事件的概率
        }
    }
    for (int i = 0; i < n; ++i)
        printf("%.10lf ", ans[i]);
    cout << '\n';
    return 0;
}