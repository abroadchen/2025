//
// Created by Psy.C on 2026/3/17.
//
/**
n: 数组长度
m: 操作次数或目标长度
a[N]: 原始数组
dp1[N]: 从左到右的最长非降子序列长度
dp2[N]: 从右到左的最长非增子序列长度
dp3[N]: 记录每个值出现的频次

将原数组循环扩展，创建长度为n²的数组
通过取模操作实现数组元素的循环复制
计算实际需要考虑的最大长度l
l=min(n,m)*n，限制处理范围

计算以每个位置结尾的最长非降子序列长度
对于位置i，寻找前面满足a[j]<=a[i]的j中dp1[j]的最大值
dp1[i] = 找到的最大值 + 1
计算以每个位置开头的最长非增子序列长度
从后往前遍历
寻找后面满足a[j]>=a[i]的j中dp2[j]的最大值
dp2[i] = 找到的最大值 + 1

如果m<=n，在扩展数组范围内找到最长的回文子序列
如果m>n，则加上由于重复元素带来的额外贡献
dp1[i] + dp2[i] - 1：以i为中心的回文序列长度
dp3[a[i]]*(m-n)：当m>n时，中间元素a[i]的额外贡献

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e4+5;
int n, m, a[N], dp1[N], dp2[N], dp3[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; dp3[a[i]]++;
    }
    for (int i = 1; i <= n*n; ++i) a[i] = a[(i-1)%n+1];
    int l = min(n, m); l *= n;
    for (int i = 1; i <= l; ++i) {
        int x = 0;
        for (int j = 0; j < i; ++j)
            if (a[j] <= a[i]) x = max(x, dp1[j]);
        dp1[i] = x + 1;
    }
    for (int i = l; i >= 1; --i) {
        int x = 0;
        for (int j = l + 1; j > i; --j)
            if (a[j] >= a[i]) x = max(x, dp2[j]);
        dp2[i] = x + 1;
    }
    int ans = 0;
    if (m <= n) {
        for (int i = 1; i <= l; ++i)
            ans = max(ans, dp1[i] + dp2[i] - 1);
    } else {
        for (int i = 1; i <= l; ++i)
            ans = max(ans, dp1[i] + dp2[i] - 1 + dp3[a[i]]*(m-n));
    }
    cout << ans << '\n';
    return 0;
}