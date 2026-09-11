//
// Created by Psy.C on 2026/9/11.
//
/**
mp：用 map 把某个前缀和值映射到一个唯一编号（压缩存储）。
a[编号]：记录所有出现该前缀和值的下标位置（vector，按下标递增）
mp[k] 取 k 的编号，若不存在（!t）返回 0；
在 a[t]（该值出现的所有下标，递增）里用 ranges::upper_bound(v, i) 找第一个大于 i 的位置，后面的都是 > i 的，数量 = end - 该位置。
读入 n、k，构建前缀和 pre[i] = pre[i-1] + t。
对每个前缀和值建立压缩编号，并把其下标 i 存入对应 vector。这样每个不同的前缀和值都维护了一个"从小到大排列的所有出现位置"
外层枚举左侧端点 i（从 0 到 n）。
初始化 t = 1（即 k^0）。
统计满足 pre[j] - pre[i] = 1（即 k^0=1）的 j 的个数，加到 ans
若 k == 1，等比数列只有一项（恒为 1），直接 continue（不再乘 k 继续）。
否则 t *= k 前进到下一项
cnt(pre[i]+t, i)：统计 pre[j] == pre[i] + t 且 j > i 的个数（即子数组 [i+1..j] 和为 t）。
用 abs(t + pre[i]) <= inf 防止溢出 / 无限循环，当 t 过大时终止。
if (t == -1) break;：处理 k 为负等比时的特殊边界（k=-1 时循环会在 ±1 间打转，故提前跳出）。
每步 t *= k 得到等比数列下一项
输出满足条件的子数组总个数 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e5+7;
constexpr ll inf = 1e14;
map<ll, int> mp;
vector<int> a[N];
int cnt(ll k, int i) {
    int t = mp[k];
    if (!t) return 0;
    const vector<int>& v = a[t];
    return v.end() - ranges::upper_bound(v, i);
}

int n, m(0);
ll k, pre[N], t, ans(0);
int main() {
    fast;
    cin >> n >> k; pre[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> t;
        pre[i] = pre[i-1] + t;
        if (!mp[pre[i]]) mp[pre[i]] = ++m;
        a[mp[pre[i]]].push_back(i);
    }
    for (int i = 0; i <= n; ++i) {
        t = 1;
        ans += cnt(pre[i]+t, i);
        if (k == 1) continue; t *= k;
        while (abs(t + pre[i]) <= inf) {
            ans += cnt(pre[i]+t, i);
            if (t == -1) break;
            t *= k;
        }
    }
    cout << ans << '\n';
    return 0;
}