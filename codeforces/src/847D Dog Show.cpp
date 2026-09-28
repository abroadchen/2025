//
// Created by Psy.C on 2026/9/28.
//
/**
n：任务个数。
t：总时限 / 总可用时间刻度。
q：最大堆，用来在贪心时动态剔除"代价过大、排不上"的任务。
① 先剔除超时的已选任务
t - i - 1 表示剩余可用时间（还剩 i 个位置没填处理，总时限 t，当前到了第 i 个位置，剩余刻度 t - i - 1，下标从 1 计或因边界）。
堆顶是已选任务里"代价/占用最大"的那个。如果它已超过剩余时限，说明这个任务已经排不下了，把它弹出（放弃）。
这是个经典的"先把最大的超时任务丢掉"的贪心维护：保证堆里存的都是当前仍可行的选择
② 读入当前任务 a
a 是第 i 个任务的某个属性（通常是它的截止时刻 / 最晚开始时刻 / 等待需求）
③ 判断当前任务是否可放入堆
max(a, i) - i：若 a > i，值为 a - i；否则为 0。可理解成任务 i 的某个"代价/占用刻度"（从它在序列中的位置 i 到其要求时刻 a 的跨度）。
条件 max(a,i) - i <= t - i - 1：该任务的代价不超过剩余时限，即当前仍能排进时间表。
满足则 q.push(...) 把它加入堆（视为"已安排"）
④ 更新答案
堆大小 = 当前能安排的任务数。
用历史最大值更新 ans，表示整个过程中能达到的最大可完成任务数。
输出最多能完成的任务个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

priority_queue<int> q;
int ans;
int main() {
    fast;
    int n, t; cin >> n >> t;
    for (int i = 1, a; i <= n; ++i) {
        while (!q.empty() && q.top() > t - i - 1) q.pop();
        cin >> a;
        if (max(a, i) - i <= t - i - 1) q.push(max(a, i) - i);
        ans = max(ans, (int)q.size());
    }
    cout << ans;
    return 0;
}