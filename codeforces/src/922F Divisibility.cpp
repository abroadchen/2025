//
// Created by Psy.C on 2026/10/14.
//
/**
枚举因子 i，对其所有大于 i 的倍数 j 做 d[j]++。
这样 d[j] 统计的是 j 的真约数（不含自身），因为从 i*2 开始。
正确性：j 的每个真约数 i（i<j 且 i|j）都会使 d[j]++ 一次
sum[i] = d[1..i] 前缀和，即 1..i 所有真约数个数总和
若 k 超过全部可能的总和上限，直接判 No
找到最小的 q，使 sum[q] >= k，即"前缀选的数足够覆盖 k"。
res = sum[q]-k：当前多出来的量，需要从方案里"删掉"一部分，使总数正好降到 k
把 1..q 分成两半：前半 1 .. (q+2)/2 - 1 全部选入集合 v；
后半 (q+2)/2 .. q 放入数组 a（元素为 {d[i], i}），等待进一步筛选
目标是删掉总和恰好为 res 的一组数（即这些数不选），使总数从 sum[q] 降到 k。
按 d 值从大到小贪心：当前数 d 值 ≤ 剩余 res，就"丢弃"它（不选入集合，从而删掉这部分），res 减少；否则只能选入集合 v。
结束后若 res > 0，说明无法精确构造，判 No
res 清零则构造成功，输出选出的数（注意这里输出的是数本身 i，而不是 d 值）。
v 中选入的这些数，它们的 d 值总和恰为 k
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;
constexpr int N = 3e5+10;
int n, k, d[N], q, tot;
ll sum[N];
vector<int> v;
ii a[N];
int main() {
    fast;
    cin >> n >> k;
    rep(i,1,n) for (int j = i*2; j <= n; j += i) d[j]++;
    rep(i,1,n) sum[i] = sum[i-1] + d[i];
    if (k > sum[n]) { cout << "No"; return 0; }
    rep(i,1,n) if (sum[i] >= k) { q = i; break; }
    int res = sum[q] - k;
    rep(i,1,(q+2)/2-1) v.push_back(i);
    rep(i,(q+2)/2,q) a[++tot] = {d[i], i};
    sort(a+1, a+1+tot); reverse(a+1, a+1+tot);
    rep(i,1,tot) {
        if (a[i].first <= res) res -= a[i].first;
        else v.push_back(a[i].second);
    }
    if (res > 0) { cout << "No"; return 0; }
    cout << "Yes\n";
    ranges::sort(v); cout << v.size() << '\n';
    for (auto x : v) cout << x << ' ';
    return 0;
}