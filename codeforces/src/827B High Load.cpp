//
// Created by Psy.C on 2026/9/24.
//
/**
a[i]：某种"当前代表点"，初始 a[i] = i（1..k 各对应一个）。
cnt[i]：统计第 i 个桶/类加入的点的数量。
v：最终要输出的边对 (u, w)
对 i 从 k+1 到 n-1（即跳过前 k 个和后 1 个点）：
用轮转方式 i % k + 1 轮流选中一个桶。
给该桶连一条边 (当前代表 a[桶], i)。
更新该桶代表为 i，并使该桶计数 cnt++。
效果：把 k+1 .. n-1 这 n-k-1 个点尽量均匀地轮流放进 k 个桶，每放一个就在桶内形成一条"链式边"（每个点与它前面的代表相连）。
因为轮流分配，cnt[] 会尽量均匀，最大值与第二大值差距小，从而 ans 逼近理论值
把各桶计数排序。
cnt[k] = 最大值，cnt[k-1] = 第二大值。
ans = 最大 + 次大 + 2。
这是题目要求输出的"答案"（某种界/上界的构造值）
每个桶的当前代表 a[i] 连到点 n。
这样点 n 与每个桶的代表相连，凑够完整的边集合
先输出 ans，再输出所有边 (u, w)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
using namespace std;
constexpr int N = 2e5+10;
int a[N], cnt[N];
vector<ii> v;
int main() {
    fast;
    int n, k; cin >> n >> k;
    for (int i = 1; i <= k; ++i) a[i] = i;
    for (int i = k+1; i <= n-1; ++i) {
        v.emplace_back(a[i%k+1], i);
        a[i%k+1] = i;
        cnt[i%k+1]++;
    }
    sort(cnt+1, cnt+k+1);
    int ans = cnt[k] + cnt[k-1] + 2;
    for (int i = 1; i <= k; ++i)
        v.emplace_back(a[i], n);
    cout << ans << '\n';
    for (auto &[fst, snd] : v)
        cout << fst << ' ' << snd << '\n';
    return 0;
}