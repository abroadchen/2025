//
// Created by Psy.C on 2026/10/12.
//
/**
now：当前考虑的质数下标，f：当前累计乘积。
从 now=1（奇数）或 now=2（偶数）开始，步长为 2，即把质数按下标奇偶分成两组。
当 now > n 时，把当前乘积 f 放入对应组：now&1 ? vl : vr。注意此时 now 已经等于 n+1 或 n+2，用 now&1 判断奇偶。
循环：for (i=1; f <= inf/i; i *= p[now])：
对当前质数取幂次 i = 1, p, p², …（i 是 p[now] 的幂），累乘进 f，递归到 now+2。
f <= inf/i 是防溢出的剪枝：保证 f*i <= inf。
结果：vl 是下标为奇数的那组质数的所有幂次乘积，vr 是偶数那组的。
对每个 vl[i]，用双指针 r 找 vr 中满足 vl[i] * vr[j] <= now 的最大下标。
条件用除法写成 vl[i] <= now / vr[j] 避免溢出。
当 r 递减时，因为 vl 已排序递增，vl[i] 增大 → 满足条件的 r 只会更小而不会增大，所以 r 单调左移，整体 O(组大小) 线性。
sum += r+1：累加当前 vl[i] 对应的可行 vr 数量。
返回 sum >= k（组合数是否达到 k）
读入质数，dfs(1,1) 生成奇数下标组，dfs(2,1) 生成偶数下标组，排序。
二分答案：值域 [1, inf]。
若 check(mid)（乘积 ≤ mid 的组合数 ≥ k），说明第 k 小 ≤ mid，缩小上界。
否则增大下界。
最终 ans 即第 k 小的乘积
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr ll inf = 1e18;
ll n, p[20];
vector<ll> vl, vr;
void dfs(int now, ll f) {
    if (now > n) { (now&1 ? vl : vr).push_back(f); return; }
    for (ll i = 1; f <= inf/i; i *= p[now]) dfs(now+2, f*i);
}

ll k;
bool check(ll now) {
    ll sum = 0;
    for (int i = 0, r = vr.size()-1; i < vl.size(); ++i) {
        while (r >= 0 && vl[i] > now/vr[r]) r--;
        sum += r + 1;
    }
    return sum >= k;
}

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> p[i];
    cin >> k; dfs(1, 1ll), dfs(2, 1ll);
    ranges::sort(vl); ranges::sort(vr);
    ll l = 1, r = inf, ans = 0;
    while (l <= r) {
        ll mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans;
    return 0;
}