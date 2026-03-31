//
// Created by Psy.C on 2026/3/31.
//
/**
读取每个元素到数组 a[] 中，同时增加其在频率数组 f[] 中的计数
初始化变量 b 来跟踪最大频率
遍历数组以找到所有元素中的最高频率
用找到的最大频率更新 b
使用 memset 将频率数组 f[] 重置为全零
再次按原始顺序遍历数组
对于每个元素，增加其在频率数组中的计数
当某个元素的频率达到最大频率（b）时，输出该元素并跳出
这确保我们输出具有最大频率的第一个元素（在原始顺序中）
时间复杂度：O(n)，空间复杂度：O(最大值)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005, M = 1e6+5;
int n, a[N], f[M];
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; f[a[i]]++;
    }
    int b = 0;
    for (int j = 0; j < n; ++j)
        if (f[a[j]] > b) b = f[a[j]];
    memset(f, 0, sizeof f);
    for (int i = 0; i < n; ++i) {
        f[a[i]]++;
        if (f[a[i]] == b) {
            cout << a[i] << '\n';
            break;
        }
    }
    return 0;
}