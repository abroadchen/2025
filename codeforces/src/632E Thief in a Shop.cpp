//
// Created by Psy.C on 2026/3/30.
//
/**
将所有元素减去最小值，进行平移变换
这样第一个元素变为0，便于背包处理
dp[i] 表示凑出和为i最少需要多少个元素
初始化为无穷大，dp[0] = 0（和为0需要0个元素）
从第2个元素开始（因为第1个元素已平移到0）
完全背包转移：对于重量a[i]，更新所有可达状态
dp[j] = min(dp[j], dp[j-a[i]]+1)：选择使用或不使用当前元素
如果dp[i] <= k，说明可以用不超过k个元素凑出和i
由于之前进行了平移，现在需要还原：mn*k + i

用变换后的数组凑出和为i，用了dp[i]个元素
实际原数组的和为：dp[i] × mn + i
但我们限制最多选k个，所以要加上(k-dp[i]) × mn
即：(k-dp[i]) × mn + dp[i] × mn + i = k × mn + i

排序去重：O(n log n)
背包：O(n × max_value × k)
总体：O(n × max_value × k)

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, inf = 0x3f3f3f3f;
int n, k, a[N], dp[N];
vector<int> v;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    n = unique(a, a + n) - a;
    int mn = a[0];
    for (int i = 0; i < n; ++i) a[i] -= mn;
    int mx = a[n-1];
    for (int i = 1; i <= mx*k; ++i) dp[i] = inf;
    dp[0] = 0;
    for (int i = 1; i < n; ++i)
        for (int j = a[i]; j <= mx*k; ++j)
            dp[j] = min(dp[j], dp[j-a[i]]+1);
    for (int i = 0; i <= mx*k; ++i)
        if (dp[i] <= k) v.push_back(mn*k+i);
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " \n"[i==v.size()-1];
    return 0;
}