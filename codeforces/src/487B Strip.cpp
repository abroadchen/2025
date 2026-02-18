//
// Created by Psy.C on 2026/2/18.
//
/**
n: 数组长度
s: 最大允许差值
l: 最小组长度
a[N]: 输入数组
dp[N]: DP数组，dp[i]表示前i个元素分割的最少段数
s1: multiset，维护当前窗口内元素
s2: multiset，维护可行解

s1.insert(a[i]): 将a[i]加入当前窗口
*s1.rbegin(): s1中的最大值
*s1.begin(): s1中的最小值
*s1.rbegin() - *s1.begin() > s: 当前窗口极差超过s
s1.erase(s1.find(a[j])): 移除左端元素
if (i - j >= l) s2.erase(s2.find(dp[j-1])): 如果窗口长度≥l，更新s2
j++: 左指针右移

if (i-j+1 >= l) s2.insert(dp[i-l]): 如果当前窗口长度≥l，添加dp[i-l]到候选
if (s2.size() == 0) dp[i] = inf: 没有可行解，设为无穷大
else dp[i] = *s2.begin() + 1: 取最小可行解+1
i++: 右指针右移

时间复杂度：O(n log n)（每次操作multiset是log n）
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 100005, inf = 0x3f3f3f3f;
int n, s, l, a[N], dp[N];
multiset<int> s1, s2;
int main() {
    fast;
    cin >> n >> s >> l;
    s1.clear(); s2.clear();
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int i = 1, j = 1;
    while (i <= n) {
        s1.insert(a[i]);//将a[i]加入当前窗口
        while (*s1.rbegin() - *s1.begin() > s) {
            s1.erase(s1.find(a[j]));
            if (i - j >= l) s2.erase(s2.find(dp[j-1]));
            j++;
        }
        if (i-j+1 >= l) s2.insert(dp[i-l]);
        if (s2.size() == 0) dp[i] = inf;
        else dp[i] = *s2.begin() + 1;
        i++;
    }
    if (dp[n] >= inf) cout << "-1\n";
    else cout << dp[n] << '\n';
    return 0;
}