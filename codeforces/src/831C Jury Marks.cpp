//
// Created by Psy.C on 2026/9/24.
//
/**
a[0] 是首项，后面读入的是差分、累加成前缀和。
sort + unique：把前缀和去重，得到互不相同的 len 个前缀和候选值。
（去重是因为在前缀和比较中重复值没有区分意义。）
输入的每个数 x（共 n 个），都与每个前缀和 a[j] 做差 x - a[j]，压入数组 v。
这样 v 里累积了 n × len 个"候选差值"
排序后统计每个差值出现次数 mp[i]。
统计出现次数恰好等于 n 的差值个数 sum：
只有某个差值在 v 中精确出现 n 次，才说明它能同时匹配全部 n 个输入（对每一个输入 x 都存在某个 a[j] 使得 x - a[j] = 该差值）。
每统计一次就把 mp[i] 清零，避免同一个差值被重复计数。
输出 sum，即可行解的候选数量
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2010;
int k, n, a[N], x;
vector<int> v;
map<int, int> mp;
int main() {
    fast;
    cin >> k >> n >> a[0];
    for (int i = 1; i < k; ++i) {
        cin >> x;
        a[i] = a[i-1] + x;
    }
    sort(a, a+k);
    int len = unique(a, a+k) - a;
    for (int i = 0; i < n; ++i) {
        cin >> x;
        for (int j = 0; j < len; ++j)
            v.push_back(x - a[j]);
    }
    ranges::sort(v);
    for (int i : v) mp[i]++;
    int sum = 0;
    for (int i : v)
        if (mp[i] == n) {
            sum++;
            mp[i] = 0;
        }
    cout << sum << '\n';
    return 0;
}