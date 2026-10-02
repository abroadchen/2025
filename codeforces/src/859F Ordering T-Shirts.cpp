//
// Created by Psy.C on 2026/10/2.
//
/**
c[x*2-2] = 前 2x-2 个元素的原始累加值；
cnt[x-1] = 已算出的前 x-1 组 DP 值。
所以 get(i) 是一个把"已结算的 DP 前缀 cnt[i-1]"和"尚未覆盖的原始量 c[i*2-2]"组合起来的混合量，用于单调队列中比较大小（它代表"从某个起点开始、以最优分割能获得的某种净收益"）
j 是单调不减的右指针：确保区间 [j..i] 满足原始长度之和 ≥ C（while 移动 j 直到 c[i*2-1] - c[j*2-2] >= C）。这是"尺取法/滑动窗口"：维护一个满足长度约束的合法起点下界 j。
q 是单调递增（按 get 值下降即队首最大）的候选下标队列，队首是当前最优的 get 起点。
入队前把 get 更小的队尾弹出（维护单调），再压入 i；
把队首中小于 j（已过期、不满足长度）的弹出。
转移取 tot（本轮新增收益）两种来源的最大值：
分支 A：j>1 时，用 C - (cnt[i-1]-cnt[j-2])；
分支 B：从单调队列队首 h（最优起点）算 (c[i*2-1]-c[h*2-2]) - (cnt[i-1]-cnt[h-1])。
cnt[i] = cnt[i-1] + tot：DP 前缀累加
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 4e5+7, M = 2e5+7;
ll c[N], cnt[M];

inline ll get(int x) { return cnt[x-1] - c[x*2-2]; }

deque<int> q;
int main() {
    fast;
    int n, m; ll C; cin >> n >> C; m = n*2-1;
    for (int i = 1, x; i <= m; ++i) {
        cin >> x;
        c[i] = c[i-1] + x;
    }
    for (int i = 1, j = 1; i <= n; ++i) {
        ll cur = get(i), tot = 0;
        while (j <= i && c[i*2-1]-c[j*2-2] >= C) j++;
        while (!q.empty() && get(q.back()) < cur) q.pop_back(); q.push_back(i);
        while (!q.empty() && q.front() < j) q.pop_front();
        if (j > 1) tot = max(tot, C-(cnt[i-1]-cnt[j-2]));
        if (!q.empty()) {
            int h = q.front();
            tot = max(tot, (c[i*2-1]-c[h*2-2])-(cnt[i-1]-cnt[h-1]));
        }
        cnt[i] = cnt[i-1] + tot;
    }
    cout << cnt[n];
    return 0;
}