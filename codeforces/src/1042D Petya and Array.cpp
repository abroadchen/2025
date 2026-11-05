//
// Created by Psy.C on 2026/11/5.
//

/**
真正学会的起点..
low_bit：取 x 最低位的 1。
sum(x)：查询 BIT 中下标 1..x 的累计值。
add(x)：在 BIT 下标 x 处 +1
a[i] 在此是前缀和：a[i] = a[i-1] + 原元素。
用有序 map d 收集所有需要用到的关键值：
0、t、
每个前缀和 a[i]、
每个 a[i]+t。
遍历 d 的键（自动有序），给每个值一个从 1 起的连续编号（dc），完成离散化（压缩坐标到 BIT 可用的 1..cnt 范围）
先 add(dc[t])：把 t（作初值）插入 BIT。
对每个 i（按 a[i] 递增处理前，实际是按原始顺序 i=1..n）：
s = sum(cnt) - sum(dc[a[i]]) → 统计 BIT 中编号大于 a[i] 的已插入键的数量。
已插入的键形如 {t} ∪ {a[1]+t, ..., a[i-1]+t}。
编号 > a[i] 意味着其真实值也 > a[i]（因为离散化保持顺序）。
ans += s：累计对数。
add(dc[a[i]+t])：把新键 a[i]+t 插入


这段本质是统计：

满足 a[i] - a[j] ≤ t（其中 j < i）的区间 (j, i] 对数，即子数组和 ≤ t 的个数。
推导：

前缀和数组 s，区间 (j,i] 的和 = a[i] - a[j]。
条件 a[i] - a[j] ≤ t ⇔ a[j] ≥ a[i] - t ⇔ a[j] + t ≥ a[i]。
即对每个 i，统计满足 a[j] + t ≥ a[i] 的 j（j < i）。
这正是：BIT 中已插入的键是 a[j]+t，统计 a[j]+t ≥ a[i] 的个数 = sum(cnt) - sum(dc[a[i]])（因为离散化单调，编号 ≥ dc[a[i]] 对应真实值 ≥ a[i]）。
s = sum(cnt) - sum(dc[a[i]]) 统计的是严格 > a[i] 或 ≥ a[i] 取决于离散化编号处理，这里 sum(dc[a[i]]) 表示编号 ≤ a[i]，相减后为编号 > a[i]，即 a[j]+t > a[i]，即 a[i]-a[j] < t——（对 a[i]+t 与 a[j] 相等边界是否计入取决于具体离散化细节）——总之是子数组和 ≤ t 的对数统计。
注意：d[0]=1 与先 add(dc[t]) 的初值代表"空前缀 j=0"（即 s[0]=0 + t = t），用于统计从 1 开始的子区间。
最终输出 ans：满足条件的子数组（连续子区间）数量，其和要求 ≤ t。

复杂度：O(n log n)，BIT 查询插入各 O(log n)，加上 O(n log n) 离散化，适合 n ≤ 2e5
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 2e5;

int low_bit(int x) { return x & (-x); }

ll b[(N<<1)+10];
ll sum(int x) {
    ll ans = 0;
    while (x > 0) { ans += b[x]; x -= low_bit(x); }
    return ans;
}
void add(int x) { while (x <= (N<<1)+2) { b[x] += 1; x += low_bit(x); } }

int n;
ll t, a[N+10], ans;
map<ll,int> d, dc;
int main() {
    fast;
    cin >> n >> t; d[0] = 1; d[t] = 1;
    rep(i,n) {
        cin >> a[i]; a[i] += a[i-1];
        d[a[i]] = 1; d[a[i]+t] = 1;
    }
    int cnt = 0;
    for (const auto key: d | views::keys) dc[key] = ++cnt;
    add(dc[t]);
    rep(i,n) {
        ll s = sum(cnt) - sum(dc[a[i]]);
        ans += s;
        add(dc[a[i]+t]);
    }
    cout << ans << '\n';
    return 0;
}