//
// Created by Psy.C on 2026/1/19.
//
/**
* n（数组b长度）、m（数组p长度）、a（预算）
读入数组b和p（从索引1开始存储）
 *
*计算前mid个最大价格和最小预算的差值
p[mid - i]：p中前mid个最大的值（因为已排序）
b[n - i]：b中前mid个最大的值
如果 p[mid-i] > b[n-i]，说明需要额外资金
if (sum <= a)：如果所需资金不超过预算，更新答案并扩大搜索范围
 *
*p[mid - i] (i从0到mid-1)：p[mid], p[mid-1], ..., p[1] (最便宜的mid个中的一个)
b[n - i] (i从0到mid-1)：b[n], b[n-1], ..., b[n-mid+1] (最富有的mid个中的一个)
 *
* 排序：O(n log n + m log m)
二分搜索：O(log(min(n,m)) × min(n,m))
总体：O(n log n + m log m)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100100
using namespace std;


int main() {
    fast;
    int n, m, b[N], p[N]; ll a;
    cin >> n >> m >> a;
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= m; ++i) cin >> p[i];
    sort(b + 1, b + n + 1);
    sort(p + 1, p + m + 1);
    int l = 0, r = min(n, m), ans = 0;//购买数量
    while (l <= r) {
        const int mid = (l + r) >> 1;
        ll sum = 0;
        for (int i = 0; i < mid; ++i) if (p[mid - i] > b[n - i]) {
            sum += p[mid - i] - b[n - i];//累计所有缺口金额
        }
        if (sum <= a) ans = mid, l = mid + 1; else r = mid - 1;
    }
    ll sum = 0;
    for (int i = 1; i <= ans; ++i) sum += p[i];//前ans个最小价格的总和
    sum = max(0ll, sum - a);//超出预算的部分
    cout << ans << ' ' << sum << '\n';
    return 0;
}