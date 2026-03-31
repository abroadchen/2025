//
// Created by Psy.C on 2026/3/31.
//
/**
n：障碍物数量
m：终点位置
s：跳跃必须跨越的最小距离（至少s+1）
d：跳跃的最大距离限制
a[N]：存储障碍物位置的数组
v：存储行动序列的向量
检查是否可达：if (a[i] - s - 1 < pre) - 如果当前位置前s+1的位置小于已到达位置，说明无法绕过障碍
添加RUN操作：if (a[i] - 1 > pre) v.emplace_back("RUN", a[i]-1-pre) - 如果需要先跑步到障碍前
确定跳跃区间：l = a[i]-1, r = a[i]+1 - 跳跃的起始和结束点
合并连续障碍：while (i < n && a[i+1]-a[i] < s+2) - 将距离太近的障碍合并成一次跳跃
验证跳跃距离：if (r - l > d) - 检查跳跃距离是否超出限制
记录跳跃操作：v.emplace_back("JUMP", r-l)
更新位置：pre = r
如果 flag 为1，输出"IMPOSSIBLE"
否则，如果终点在最后一个障碍之后，添加最后的跑步段
输出所有行动序列
时间复杂度：O(n log n)，主要是排序的时间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define si pair<string, int>
using namespace std;
constexpr int N = 2e5+5;

int n, m, s, d, a[N];
vector<si> v;
int main() {
    fast;
    cin >> n >> m >> s >> d;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    int pre = 0, flag = 0;
    for (int i = 1; i <= n; ++i) {
        if (a[i] - s - 1 < pre) { flag = 1; break; }
        if (a[i] - 1 > pre) v.emplace_back("RUN", a[i]-1-pre);
        int l = a[i]-1, r = a[i]+1;
        while (i < n && a[i+1]-a[i] < s+2)
            i++, r = a[i]+1;
        if (r - l > d) { flag = 1; break; }
        v.emplace_back("JUMP", r-l);
        pre = r;
    }
    if (flag) cout << "IMPOSSIBLE\n";
    else {
        if (a[n] + 1 < m)
            v.emplace_back("RUN", m-a[n]-1);
        for (auto &[fst, snd] : v)
            cout << fst << ' ' << snd << '\n';
    }
    return 0;
}