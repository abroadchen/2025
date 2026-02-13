//
// Created by Psy.C on 2026/2/13.
//
/**
cnt[i] = cnt[i+1];

继承下一位置的计数（从i+1到末尾满足sum[j]=x*2的个数）
if (sum[i] == x) ans += cnt[i];

如果当前位置的前缀和等于x（第一段结束位置）
加上从i+1到末尾满足sum[j]=x*2的个数（第三段开始位置的选择数）
if (sum[i] == x*2) cnt[i]++;

如果当前位置的前缀和等于2*x（第二段结束位置）
更新cnt[i]（当前位置可以作为第三段的开始）

时间复杂度： O(n) 空间复杂度： O(n)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500005
using namespace std;

int n;
ll a[N], sum[N], cnt[N];

int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    ll ans = 0;
    if (sum[n] % 3 == 0) {
        const ll x = sum[n] / 3;//每份的目标值
        for (int i = n - 1; i; --i) {
            cnt[i] = cnt[i+1];//继承下一位置的计数
            if (sum[i] == x) ans += cnt[i];
            if (sum[i] == x*2) cnt[i]++;
        }
    }
    cout << ans << '\n';
    return 0;
}