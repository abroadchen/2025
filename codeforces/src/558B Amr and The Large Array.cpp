//
// Created by Psy.C on 2026/3/11.
//
/**
N: 最大数组长度 M: 最大值域范围
a[N]: 输入数组
cnt[M]: 每个值的出现次数
l[M]: 每个值首次出现的位置
r[M]: 每个值最后出现的位置

遍历数组，统计每个值的出现次数和位置信息：
首次出现时，同时记录首次和最后位置
非首次出现时，只更新最后位置
增加计数
更新最大出现次数

遍历数组，找到频次等于最大频次的所有元素
计算每个元素首次到最后一次出现的位置差
在所有最大频次元素中，选择位置差最小的元素

遍历数组两次: O(n)
空间复杂度: O(max_value)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 1e6+5, inf = 1e9+7;
int n, a[N], cnt[M], l[M], r[M];
int main() {
    fast;
    cin >> n;
    int mx = -1;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (cnt[a[i]] == 0) l[a[i]] = i, r[a[i]] = i;
        else r[a[i]] = i;
        cnt[a[i]]++;
        mx = max(mx, cnt[a[i]]);
    }
    int ans = 0, x = inf;
    for (int i = 1; i <= n; ++i)
        if (cnt[a[i]] == mx) {
            int d = r[a[i]] - l[a[i]];
            if (x > d) {
                x = d; ans = a[i];
            }
        }
    cout << l[ans] << ' ' << r[ans] << '\n';
    return 0;
}