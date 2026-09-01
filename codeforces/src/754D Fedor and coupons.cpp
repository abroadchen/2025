//
// Created by Psy.C on 2026/9/1.
//
/**
- N = 300100 ：最大区间数 30 万
- inf = 0x3f3f3f3f ：极大值（约 10 亿），用于特殊标记
l 左端点 r 右端点 num 原始编号 （排序后编号会乱，需要记住原来的编号）
按左端点升序排序 。这是贪心策略的前提
int 存储类型：只存区间的 右端点 r
vector<int> 底层容器
greater<> 比较器 → 最小堆 （堆顶是最小的右端点）
n 区间总数 读入
k 需要选的区间数 读入
mx 最大交集长度 0
xx 最优交集的左端点 L 0
yy 最优交集的右端点 R 0
m 输出计数 0
读入左端点、右端点，同时保存原始编号 num = i 。
sort 是 STL 快速排序，对区间 e[1] ~ e[n] 按左端点升序重排。
逐个处理排序后的区间：
- x = 当前区间左端点
- y = 当前区间右端点
- 把右端点 y 加入最小堆
堆的大小超过 k → 弹出 最小的右端点 。这意味着我们始终保留 k 个"右边界最大"的区间（因为弹出的是最小的右端点）。
- q.top() = 堆顶 = k 个区间中 最小的右端点 （交集的 R）
- x = 当前区间左端点（也是当前所有堆中区间的 最大左端点 L，因为已按左端点排序）
- len = R - L + 1 = 交集长度
只有堆里恰好有 k 个区间时才更新 （ q.size() == k ）：
- mx < len ：找到更长的交集 → 更新最大值和对应区间
- xx = x ：交集左端点
- yy = q.top() ：交集右端点
- mx == 0 → 所有选法的交集都是空的（ R < L ），无解
- 把 xx 设成极大值 inf ， yy 设成极小值 -inf
- 这样后面的筛选条件 e[i].l <= xx && e[i].r >= yy 会变成：
- e[i].l <= inf → 永远成立（所有区间左端点 ≤ 极大值）
- e[i].r >= -inf → 永远成立（所有区间右端点 ≥ 极小值）
- 效果 ：随便选 k 个区间就行（因为反正没有交集）
遍历所有区间，找出 完全包含 交集 [xx, yy] 的区间：
- e[i].l <= xx ：区间左边界在交集左边界左边或重合
- e[i].r >= yy ：区间右边界在交集右边界右边或重合
- 两个条件都满足 → 这个区间包含了整个交集 → 入选
输出 e[i].num （原始编号，不是排序后的位置）。
提前退出 ： m < k → 已经选够 k 个就停。

排序 O(n log n) sort
快速排序 堆操作 O(n log k) 每个区间入堆出堆一次，堆大小 ≤ k
筛选输出 O(n) 遍历一次
总计 O(n log n) 排序主导
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 3e5+100, inf = 0x3f3f3f3f;
struct node { int l, r, num; } e[N];
bool cmp(node a, node b) { return a.l < b.l; }
priority_queue<int, vector<int>, greater<>> q;

int main() {
    fast;
    int n, k, mx = 0, xx = 0, yy = 0, m = 0; cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> e[i].l >> e[i].r;
        e[i].num = i;
    }
    sort(e + 1, e + 1 + n, cmp);
    for (int i = 1; i <= n; ++i) {
        int x = e[i].l, y = e[i].r; q.push(y);
        if (q.size() > k) q.pop();
        int len = q.top() - x + 1;
        if (q.size() == k && mx < len) {
            mx = len;
            xx = x; yy = q.top();
        }
    }
    cout << mx << '\n';
    if (mx == 0) xx = inf, yy = -inf;
    for (int i = 1; i <= n && m < k; ++i)
        if (e[i].l <= xx && e[i].r >= yy)
            m++, cout << e[i].num << ' ';
    return 0;
}