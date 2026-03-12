//
// Created by Psy.C on 2026/3/12.
//
/**
n: 数组长度
k: 倍数因子
a[N]: 输入数组
mp[4]: 4个映射表（索引0-3），用于记录不同阶段的计数

mp[3][a[i]]: 以a[i]为第三个元素的三元组数量
mp[2][a[i]/k]: 以a[i]/k为第二个元素的二元组数量
如果a[i]/k可以作为二元组的末尾元素，则a[i]可以作为三元组的末尾元素
mp[2][a[i]]: 以a[i]为第二个元素的二元组数量
mp[1][a[i]/k]: 以a[i]/k为第一个元素的单元素数量
如果a[i]/k存在，则可以形成以a[i]为第二个元素的二元组
mp[1][a[i]]: 记录值为a[i]的单个元素数量
遍历mp[3]，累加所有三元组的数量
it->second: 每个值对应的三元组数量
输出最终结果

动态规划思想
mp[1]: 记录单个元素的数量
mp[2]: 记录二元组的数量（满足a * k = b）
mp[3]: 记录三元组的数量（满足a * k = b 且 b * k = c）
转移方程
当遇到值为x的元素且x % k == 0时：
mp[3][x] += mp[2][x/k]（三元组扩展）
mp[2][x] += mp[1][x/k]（二元组扩展）
mp[1][x]++（单元素计数）

O(n log n)，主要是map操作的复杂度
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5;
int n, k, a[N];
map<int, int> mp[4];
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] % k == 0) {
            mp[3][a[i]] += mp[2][a[i]/k];
            mp[2][a[i]] += mp[1][a[i]/k];
        }
        mp[1][a[i]]++;
    }
    int ans = 0;
    for (auto it = mp[3].begin(); it != mp[3].end(); ++it)
        ans += it->second;
    cout << ans << '\n';
    return 0;
}