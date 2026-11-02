//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
数组 a[i] = x 的二进制中 1 的个数
sum 为前缀和，cnt[0/1] 记录之前奇偶前缀和出现次数。
ans += cnt[sum&1]++：统计所有和为偶数的子数组总数（这是"候选总数"，稍后扣除不满足第二大条件的）
对每个左端点 l，只向右扫描 最多 58 个元素（因为 popcount ≤ 60，且条件 2*mx > num 在有大量元素时几乎不会因"最大元素"失效——当区间内非零元素很多时最大 popcount 相对区间和小）。
对每个右端点 r：记 mx = 区间内最大 popcount，num = 区间 popcount 和。
若和为偶数（num%2==0）但最大 popcount 的两倍 > 总和（2*mx > num，即多数 1 都集中在一个元素里，不满足"数值分散"），则该子数组不合要求，从答案中扣除
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 3e5+1;

int n, a[N], cnt[] = {1,0}, sum;
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        ll x; cin >> x;
        a[i] = __builtin_popcountll(x);
    }
    ll ans = 0;
    rep(l,n) {
        ans += cnt[(sum+=a[l])&1]++;
        for (int r = l, mx = 0, num = 0; r <= min(n,l+58); r++)
            mx = max(mx,a[r]), ans -= (num+=a[r])%2 == 0 && 2*mx > num;
    }
    cout << ans;
    return 0;
}