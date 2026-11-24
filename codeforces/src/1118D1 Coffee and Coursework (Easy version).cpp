//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
a[i] 降序排（大的在前），便于贪心分配优先用大的任务补足总量。
尝试用 day 天安排。t 表示"下一个任务该分到哪一天"（轮流）
把剩余最大任务轮流塞进 day 天。
规则：放到某天时，该天已放了 len 个，若 a[j] - len <= 0 说明这个任务放进去会因衰减变没（非正贡献）→ 本天数 day 不可行，break 跳出该任务循环
对每种 day 分布，累计总贡献：同一天第 k（0 基）个任务贡献 = 原值 − k。
若 tot ≥ m，说明 day 天可行 → 输出最小 day。
都试过仍不行 → -1。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 110;
int n, m, a[N];//任务数、目标量、每个任务的量
vector<int> v[N];//v[day]=该天安排的任务列表
int main() {
    fast;
    cin >> n >> m;
    rep(i,n) cin >> a[i];
    sort(a+1,a+n+1); reverse(a+1,a+n+1);
    rep(day,n) {
        int t = 1;
        rep(j,day) v[j].clear();
        rep(j,n) {
            int len = v[t].size();
            if (len > 0 && a[j]-len <= 0) break;
            v[t].push_back(a[j]);//把任务 j 放到第 t 天
            t++;
            if (t > day) t = 1;//轮转
        }
        int tot = 0;
        rep(j,day) {
            int len = v[j].size();
            for (int k = 0; k < len; k++) { int x = v[j][k]; x -= k; tot += x; }
        }
        if (tot >= m) { cout << day << '\n'; return 0; }
    }
    cout << "-1\n";
    return 0;
}