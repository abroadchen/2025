//
// Created by Psy.C on 2025/12/9.
//
/*
*a[N]: 存储输入的数据
sum[N]: 前缀和数组
dp[N]: 记忆化数组，存储已计算的结果
ans[N]: 存储每次查询的答案
 *
 *计算前缀和：sum[i] = a[1] + a[2] + ... + a[i]
 *
 *如果dp[k]已经计算过（不为0），则直接使用缓存结果并继续下一次查询
 *
*初始化变量：r=n-1（右边界），t=1（当前层大小），s=0（累计大小）
无限循环（通过break退出）：
t *= k：当前层的理论大小是前一层的k倍
s += t：累计已处理的元素数量
l = max(n-s, 1)：计算当前层的左边界
ans[cnt] += (sum[r] - sum[l-1]) * i：累加当前层的贡献
r = l - 1：更新右边界为下一层的右边界
如果左边界到达1，则退出循环
 *将当前计算结果缓存到dp[k]中
 *
*预处理：O(n log n)（排序）
每次查询：O(log_k n)
总体：O(n log n + q log n)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500005
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;


signed main() {
    fast;
    ll n; cin>>n;
    ll a[N], sum[N], dp[N], ans[N];
    rep(i,n) cin >> a[i];
    sort(a + 1,a + n + 1);
    rep(i,n) sum[i] = sum[i-1] + a[i];
    int q, cnt = 0, k; cin>>q; const int m = q;
    while(q--) {
        cnt++;
        cin>>k;
        if (k > n) k = static_cast<int>(n);
        if (dp[k] != 0) { ans[cnt] = dp[k]; continue; }
        ll r = n - 1, t = 1, s = 0;
        for (ll i = 1; ; ++i) {
            t *= k;
            s += t;
            const ll l = max(n - s, 1ll);
            ans[cnt] += (sum[r] - sum[l - 1]) * i;
            r = l - 1;
            if (l == 1) break;
        }
        dp[k] = ans[cnt];
    }
    rep(i,m) {
        if (n == 1) cout << "0 ";
        else cout << ans[i] << ' ';
    }
    return 0;
}