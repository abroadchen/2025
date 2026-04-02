//
// Created by Psy.C on 2026/4/1.
//
/**
n: 输入数组的长度
a[N]: 存储输入的数组元素
mx: 当前区间中最高频率
id: 当前区间中具有最高频率的最小数值
t[N]: 临时计数数组，统计每个数值的出现次数
ans[N]: 结果数组，记录每个数值作为最高频数的次数

外层循环 (i 从 1 到 n):
处理以位置i结尾的所有子数组
内层循环 (j 从 i 递减到 1):
考虑子数组 [j, i]（从位置j到位置i）
循环内部操作:
memset(t, 0, sizeof t): 重置计数数组
t[a[j]]++: 将当前元素a[j]的计数加1
更新最高频次元素的判断条件：
t[a[j]] > mx: 如果当前元素频率更高，更新mx和id
t[a[j]] == mx && a[j] < id: 如果频率相同但数值更小，更新id
ans[id]++: 将当前最高频次元素的计数加1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5005;
int n, a[N], mx, id, t[N], ans[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        mx = 0, id = 0;
        memset(t, 0, sizeof t);
        for (int j = i; j; --j) {
            t[a[j]]++;
            if (t[a[j]] > mx || t[a[j]] == mx && a[j] < id)
                mx = t[a[j]], id = a[j];
            ans[id]++;
        }
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << ' ';
    return 0;
}