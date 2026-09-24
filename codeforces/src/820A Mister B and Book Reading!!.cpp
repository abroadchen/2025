//
// Created by Psy.C on 2026/9/23.
//
/**
c：总目标量（要完成的总页数/总任务量）。
v0：每天初始完成的量（第一天的量）。
v1：每天能完成的最大量上限。
a：每天增长量（速度提升）。
l：每天开始前会遗忘/回退的量
cnt = 1, sum = v0：从第一天开始，第一天完成 v0 的量（读完 v0 页）。

只要还没完成总目标（sum < c）就进入下一天：

sum -= l：新一天开始前，先回退/遗忘 l（之前读的内容忘了 l）。
v0 += a; v0 = min(v0, v1)：速度提升 a，但不超过上限 v1。
sum += v0：这一天又读 v0 的量，累加到总进度。
cnt++：天数 +1。
当 sum >= c 时退出循环，输出总天数 cnt
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int c, v0, v1, a, l;
int main() {
    fast;
    while (cin >> c >> v0 >> v1 >> a >> l) {
        int cnt = 1, sum = v0;
        while (sum < c) {
            sum -= l; v0 += a; v0 = min(v0, v1);
            sum += v0;
            cnt++;
        }
        cout << cnt << '\n';
    }
    return 0;
}