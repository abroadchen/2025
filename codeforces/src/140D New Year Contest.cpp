//
// Created by Psy.C on 2025/11/20.
//
/*
*a[N]: 存储每个任务所需时间的数组
s(0): 计数器，记录完成的任务数（初始化为0）
p(0): 惩罚分数累计值（初始化为0）
t(10): 当前累计时间（初始化为10分钟）
 *
*循环条件：
s < n：还有未处理的任务
t + a[s] <= 720：加上当前任务后总时间不超过720分钟
循环体：
t += a[s]：将当前任务时间加到总时间上
p += max(0, t - 360)：计算惩罚分数
*如果累计时间t超过360分钟，则产生惩罚
惩罚值为超出360分钟的部分
如果未超过360分钟，惩罚为0
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

const int N = 111;
int n, a[N], s(0), p(0), t(10);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    for (cin >> n, s = 0; s < n; ++s) cin >> a[s];
    for (sort(a, a + n), s = 0;
        s < n && t + a[s] <= 720; ++s, p += max(0, t - 360))
        t += a[s];
    cout << s << ' ' << p;
    return 0;
}