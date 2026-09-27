//
// Created by Psy.C on 2026/9/27.
//
/**
每个任务 t[i] 有两个值 a、b（典型地，a 是区间左端点、b 是右端点）。
排序规则：先按 a 升序；a 相等时按 b 升序。排序是后面贪心判断的基础
读入所有任务并按 (a, b) 升序排序。
把前两个任务作为基准，分别放进两个"容器"，记录它们各自的右端点 b 为 t1、t2（代表两个容器目前最靠右的占用结束位置）
对第 i 个任务（按起始点 a 升序）：它的起点 a 必须晚于某个容器里上一个任务的结束时间，才不冲突。
判断逻辑：
若 a <= t1 且 a <= t2：两个容器的上一个任务都还没结束，当前任务哪个容器都放不进去 → 冲突，输出 NO。
否则，优先放进"更早结束"的容器：
若 a > t1：能放进容器 1，更新 t1 = b；
否则（说明 a <= t1 但 a > t2）：能放进容器 2，更新 t2 = b。
若全程所有任务都能放下，输出 YES。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e5+5;
struct node { int a, b; } t[N];
bool cmp(node m, node n) {
    if (m.a == n.a) return m.b < n.b;
    return m.a < n.a;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> t[i].a >> t[i].b;
    sort(t, t+n, cmp);
    int t1 = t[0].b, t2 = t[1].b;
    for (int i = 2; i < n; ++i) {
        if (t[i].a <= t1 && t[i].a <= t2) {
            cout << "NO\n"; return 0;
        }
        if (t[i].a > t1) t1 = t[i].b;
        else if (t[i].a > t2) t2 = t[i].b;
    }
    cout << "YES\n";
    return 0;
}