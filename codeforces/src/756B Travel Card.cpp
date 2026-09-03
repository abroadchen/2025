//
// Created by Psy.C on 2026/9/2.
//
/**
t 请求的 时间戳
p 该请求分配到的 配额值
q1 维护 90 秒窗口 内的所有请求 90 秒
q2 维护 1440 秒窗口 内的所有请求 1440 秒（= 24×60）
p1 当前 q1 中所有 p 值之和 （90 秒窗口内累计）
p2 当前 q2 中所有 p 值之和 （1440 秒窗口内累计）
n 请求总数
t 当前请求的时间戳（每次循环读一个）
步骤 1：清理 q1 中超出 90 秒窗口的请求
只要 q1 非空，且队首请求的时间 t_front 满足：
  t - t_front >= 90
就弹出队首，并从 p1 中减去它的 p 值
用 while 而不是 if ，因为可能有多个请求同时超出窗口（比如两个请求相隔 1 秒，t 一下子跳了 100 秒）。
步骤 2：清理 q2 中超出 1440 秒窗口的请求
c1 固定 20 这个请求 最多 给 20（单请求硬上限）
c2 max(0, 50 - p1) 90 秒窗口还剩多少配额可用。如果 p1 ≥ 50，剩余 0
c3 max(0, 120 - p2) 1440 秒窗口还剩多少配额。如果 p2 ≥ 120，剩余 0
max(0, ...) 的保护 ：如果窗口已经用完配额（p1 ≥ 50），剩余配额不能是负数，强制为 0。
三重限制取 最严格的那个 ：
把当前请求加入两个队列 + 更新累计值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

struct node { int t, p; };
queue<node> q1, q2;

int p1 = 0, p2 = 0;
int main() {
    fast;
    int n, t; cin >> n;
    while(n--) {
        cin >> t;
        while (!q1.empty() && t - q1.front().t >= 90)
            p1 -= q1.front().p, q1.pop();
        while (!q2.empty() && t - q2.front().t >= 1440)
            p2 -= q2.front().p, q2.pop();
        int c1 = 20, c2 = max(0, 50-p1), c3 = max(0, 120-p2);
        cout << min(min(c1, c2), c3) << '\n';
        q1.push({.t = t, .p = min(min(c1, c2), c3)});
        q2.push({.t = t, .p = min(min(c1, c2), c3)});
        p1 += min(min(c1, c2), c3);
        p2 += min(min(c1, c2), c3);
    }
    return 0;
}