//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
n：数组长度。
k：读入但未使用。
a[N]：原数组。
f[i]：以 i 结尾的"相邻不同连续段"长度。
ans：全局最大值
读入 n、k，以及数组 a。
所有 f[i] 初始化为 1（每个元素自身构成长度 1 的段）
对每个 i：
若 a[i] != a[i-1]（与前一元素不同），则 f[i] = f[i-1] + 1，把前面连续不同的段延长一位；
否则 a[i] == a[i-1]，保持 f[i]=1（新开一段，因为出现相同就中断）。
每次更新 ans = max(ans, f[i]) 保留最大段长。
这就是一维 DP：f[i] 只依赖 f[i-1]，转移条件是相邻元素不同
输出最长"相邻元素均不同"的连续段长度
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e5+5;

int n, k, a[N], f[N], ans;
int main() {
    fast;
    cin >> n >> k;
    rep(i,n) { cin >> a[i]; f[i] = 1; }
    rep(i,n) {
        if (a[i] != a[i-1]) f[i] = f[i-1] + 1;
        ans = max(ans, f[i]);
    }
    cout << ans;
    return 0;
}