//
// Created by Psy.C on 2026/3/2.
//
/**
N = 26：数组大小上限
mid：分割点，将数组分成两部分
k：操作次数限制
mp[N]：哈希表数组，mp[i]存储使用i次操作的方案数
a[N]：输入数组
S：目标和
fac[N]：阶乘数组

x当前位置，cnt已使用操作次数，sum当前和
边界条件：if (x > mid)到达前半部分边界，记录结果
三种选择：
不选择也不操作：dfs(x + 1, cnt, sum)
选择原值：dfs(x + 1, cnt, sum + a[x])
选择阶乘：dfs(x + 1, cnt + 1, sum + fac[a[x]])（消耗一次操作）

边界条件：if (x > n)到达数组末尾，查找匹配
匹配逻辑：for (int i = 0; i <= k-cnt; ++i) ans += mp[i][S-sum]
在前半部分找和为S-sum，操作次数为i的方案

时间复杂度：O(3^(n/2))，比暴力的O(3^n)有所优化
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 26;

int mid, k;
unordered_map<ll, int> mp[N];
ll a[N], S, fac[N];
void dfs(const int x, const int cnt, const ll sum) {
    if (x > mid) {
        mp[cnt][sum]++;
        return;
    }
    dfs(x + 1, cnt, sum);
    if (sum + a[x] <= S) dfs(x + 1, cnt, sum + a[x]);
    if (cnt < k && a[x] < 20 && sum + fac[a[x]] <= S)
        dfs(x + 1, cnt + 1, sum + fac[a[x]]);
}

int n;
ll ans;
void dfs2(const int x, const int cnt, const ll sum) {
    if (x > n) {
        for (int i = 0; i <= k-cnt; ++i) ans += mp[i][S-sum];
        return;
    }
    dfs2(x + 1, cnt, sum);
    if (sum + a[x] <= S) dfs2(x + 1, cnt, sum + a[x]);
    if (cnt < k && a[x] < 20 && sum + fac[a[x]] <= S)
        dfs2(x + 1, cnt + 1, sum + fac[a[x]]);
}

int main() {
    fast;
    cin >> n >> k >> S; fac[0] = 1ll;
    for (int i = 1; i < 20; ++i) fac[i] = 1ll*i*fac[i-1];
    for (int i = 1; i <= n; ++i) cin >> a[i];
    mid = n>>1; dfs(1, 0, 0); dfs2(mid+1, 0, 0);
    cout << ans << '\n';
    return 0;
}