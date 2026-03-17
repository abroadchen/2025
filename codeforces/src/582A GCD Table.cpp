//
// Created by Psy.C on 2026/3/16.
//
/**
n: 输入的矩阵边长
num[M]: 存储去重后的数值
cnt: 不同数字的个数
tot: 结果数组已填入元素的个数
a[N]: 存储结果数组
mp 每个数字及其出现次数

如果这个数x第一次出现（!mp[x]为真），就把它加入num数组
更新mp[x]的计数（记录每个数出现的频次）

从最大的数开始构造结果数组
跳过已经被使用完的数字
将当前最大数放入结果数组a
减少该数字的计数
对于已确定的数与当前新加入的数，它们的最大公约数在矩阵中会成对出现，所以减去2
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 505, M = 250005;
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
int n, num[M], cnt, tot, a[N];
map<int, int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n*n; ++i) {
        cin >> x;
        if (!mp[x]) num[++cnt] = x;
        mp[x]++;
    }
    sort(num + 1, num + cnt + 1);
    for (int i = cnt; i >= 1 && tot < n;) {
        while (!mp[num[i]]) i--;
        a[++tot] = num[i];
        mp[num[i]]--;
        for (int j = 1; j < tot; ++j)
            mp[gcd(num[i], a[j])] -= 2;
    }
    for (int i = 1; i <= tot; ++i) cout << a[i] << ' ';
    return 0;
}