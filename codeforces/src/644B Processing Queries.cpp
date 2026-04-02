//
// Created by Psy.C on 2026/4/1.
//
/**
n: 顾客总数
b: 服务窗口数量上限
t[N]: 每个顾客的到达时间
d[N]: 每个顾客的服务持续时间
T: 当前服务完成时间
q: 队列，存储服务完成时间
第一个顾客立即服务：T = t[1] + d[1]（到达时间+服务时间）
输出第一个顾客的服务完成时间
将完成时间加入队列
从第二个顾客开始处理
移除队列中所有在当前顾客到达时间之前已完成的服务
如果队列大小（正在服务的顾客数）不超过窗口数量b：
T = max(T, t[i]): 服务开始时间为当前时间或顾客到达时间的最大值
T += d[i]: 服务完成时间 = 开始时间 + 服务持续时间
输出完成时间
将完成时间加入队列
如果队列大小超过窗口数量，输出"-1"（无法服务）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
ll n, b, t[N], d[N], T;
queue<ll> q;
int main() {
    fast;
    cin >> n >> b;
    for (ll i = 1; i <= n; ++i) cin >> t[i] >> d[i];
    T = t[1] + d[1];
    cout << T << ' ';
    q.push(T);
    for (int i = 2; i <= n; ++i) {
        while (!q.empty() && q.front() <= t[i]) q.pop();
        if (q.size() <= b) {
            T = max(T, t[i]); T += d[i];
            cout << T << ' ';
            q.push(T);
        } else cout << "-1 ";
    }
    return 0;
}