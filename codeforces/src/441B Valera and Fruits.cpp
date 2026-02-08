//
// Created by Psy.C on 2026/2/8.
//
/**
n: 表示物品数量
v: 表示每天最大处理量
p[N]: 存储物品信息的数组，每个元素包含时间截止日期和价值
q: 优先队列，存储ii类型的元素，按照cmp规则排序
数组按 first 降序排列，p[n].first 是所有截止时间中最小的 最早的截止时间
 */
#include <algorithm>
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3005
#define ii pair<int, int>
using namespace std;

struct cmp {
    bool operator()(const ii& x, const ii& y) const {
        if (x.first == y.first) return x.second < y.second;
        return x.first > y.first;
    }
};

int n, v;
ii p[N];
priority_queue<ii, vector<ii>, cmp> q;
int get() {
    const int st = p[n].first, ed = p[1].first;//最晚截止时间和最早截止时间
    int res = 0;
    for (int i = st, w; i <= ed+1; ++i) {
        w = 0;//每天初始工作量
        while (!q.empty() && q.top().first <= i) {//当前物品截止时间小于等于当天
            auto u = q.top(); q.pop();
            //任务失效日期早于当前日期
            if (u.first + 1 < i) continue;//当前物品已经过期
            const int val = min(u.second, v - w);//剩余容量和物品价值中的较小值
            w += val; u.second -= val;//更新已处理量和物品剩余量
            if (u.second) q.push(u);// 如果还有剩余，放回队列
            if (w == v) break;//当天达到最大处理量
        }
        res += w;//累加当天处理量到总结果
    }
    return res;
}

int main() {
    fast;
    cin >> n >> v;
    for (int i = 1; i <= n; ++i)
        cin >> p[i].first >> p[i].second, q.push(p[i]);
    sort(p + 1, p + n + 1, cmp());
    cout << get() << '\n';
    return 0;
}