//
// Created by Psy.C on 2026/11/14.
//

/**
真正学会的起点..
mp 记录每个值出现次数。
把所有不同的频次存入数组 t[]（长度为 m），并升序排序
t[m] 是最大频次。
作为初始下界
对每个 i（从 1 到最大频次）：

k 初始为 min(17, m)（因为 2^17 = 131072 > 2e5，最多 17 位）。
x = m 从频次最大端开始。
内层 while：用二分式缩放——while (i*(1<<k) > t[x]) k--，即找到使得 i·2^k ≤ t[x] 的最大 k。
然后 x--, k--, sum++：消耗一个频次 t[x] 和一个 2 的幂 2^k（作为"一组"），计数 sum 加 1。
循环直到总共消耗了 min(17, m) 个频次（k 归零）或 x 用完。
然后更新答案：ans = max(ans, i * ((1<<sum) - 1))
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

int n, a[N], t[N], m, ans;
map<int, int> mp;
signed main() {
    fast;
    cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) mp[a[i]]++;
    for (auto val : mp | views::values) t[++m] = val;
    sort(t+1, t+m+1); ans = t[m];
    rep(i,t[m]) {
        int k = min(17ll,m), x = m, sum = 0;
        while (x >= 1 && k >= 0) {
            while (i*(1<<k) > t[x]) k--;
            if (x >= 1 && k >= 0) x--, k--, sum++;
        }
        ans = max(ans, i*((1<<sum)-1));
    }
    cout << ans;
    return 0;
}