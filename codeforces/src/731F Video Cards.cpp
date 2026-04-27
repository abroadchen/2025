//
// Created by Psy.C on 2026/4/26.
//
/**
N: 数组最大长度
n: 输入序列长度
a[N]: 输入数组
cnt[N]: 计数数组，cnt[i]表示值为i的元素个数
used[N]: 标记数组，避免重复计算相同的数字

读入数据
t记录数组中的最大值
统计每个数值出现的次数到cnt数组
排序原数组（虽然后面没用到排序后的结果）
计算cnt数组的前缀和，此时cnt[i]表示小于等于i的元素总数
遍历数组中的每个元素
如果当前元素的值还没有被处理过（!used[a[i]]）
对于当前值a[i]，计算其所有倍数相关的贡献：
x从a[i]开始，每次增加a[i]（即遍历a[i]的所有倍数）
(cnt[min(x+a[i]-1, t)]-cnt[x-1])*x计算在区间[x, min(x+a[i]-1, t)]内有多少个数，乘以当前倍数值x
这实际上是计算所有等于x的元素的贡献（个数×倍数值）
used[a[i]] = true标记已处理，避免重复计算
时间复杂度约为O(n log(max_value))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;
int n, a[N];
ll cnt[N];
bool used[N];
int main() {
    fast;
    cin >> n;
    int t = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        t = max(t, a[i]);
        cnt[a[i]]++;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= t; ++i) cnt[i] += cnt[i-1];
    ll ans = 0, sum;
    for (int i = 1; i <= n; ++i) {
        sum = 0;
        if (!used[a[i]])
            for (int x = a[i]; x <= t; x += a[i])
                sum += (cnt[min(x+a[i]-1, t)]-cnt[x-1])*x, used[a[i]] = true;
        ans = max(ans, sum);
    }
    cout << ans;
    return 0;
}