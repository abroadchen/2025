//
// Created by Psy.C on 2026/4/25.
//
/**
b: 某种基准值
w: 某种权重值
nd = w - b + 1: 一个计算得出的值
operator<: 优先队列比较函数，nd小的优先级更高
按b值降序排列

将所有b值大于原始第一个元素b值的元素加入优先队列
由于已按b值降序排列，所以连续处理直到遇到b值小于等于x.b的元素

x: 初始的"主角"元素
nd = w - b + 1: 可能是击败某个对手需要的代价
q: 优先队列存储待处理的对手，按击败难度排序
rk: 当前排名
mx: 最佳排名记录

排序: O(n log n)
优先队列操作: 最坏情况下O(n log n)，每次push/pop操作O(log n)
总体: O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+7;

struct node {
    ll b, w, nd;
    bool operator<(const node& o) const {
        return nd > o.nd;
    }
} t[N];

bool cmp(node a, node b) {
    return a.b > b.b;
}

int n;
priority_queue<node> q;//存储待处理的对手，按击败难度排序
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> t[i].b >> t[i].w;
        t[i].nd = t[i].w - t[i].b + 1;
    }
    auto x = t[0];//保存原始的第一个元素
    sort(t, t+n, cmp);
    for (int i = 0; i < n; ++i) {
        if (t[i].b > x.b) q.push(t[i]);
        else break;
    }
    int idx = q.size(), rk = idx+1, mx = rk;
    while (!q.empty()) {
        auto u = q.top(); q.pop();
        x.b -= u.nd;//减少x的b值
        if (x.b < 0) break;
        int cnt = 0;
        while (x.b < t[idx+1].b) {//将更多元素加入优先队列
            q.push(t[idx+1]);
            idx++;
            cnt++;
        }
        rk += cnt - 1;//更新排名
        mx = min(mx, rk);//记录最小排名
    }
    cout << mx << '\n';
    return 0;
}