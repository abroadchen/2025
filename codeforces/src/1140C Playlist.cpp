//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
所有物品按 y 升序排列。
priority_queue<node> q 是小根堆（因为 operator< 用 u.x > v.x，堆顶是 x 最小的）
"选 k 个物品，最小 y 由被选者决定" 的贪心：

固定当前的 y 为扫描到的 p[i].y（即当前那组里最小的 y）。
从 y 较大的物品里挑 x 最大的补足 k 个，用堆维护。
当遇到 x 更大的物品，替换堆内 x 最小的，更新答案
清空堆，重新从最大的 y 往小取 k-1 个。
枚举不同 y 断点，用 ans * 当前最小 y 更新答案

因为返回 u.x > v.x，所以小的才"优"——priority_queue 默认是大根堆（用 < 判断），这里反向定义就让堆顶变成 x 最小的元素，即小根堆
这个函数用于 sort(p+1, p+n+1, cmp)，决定数组顺序。
它按 y 升序排列整个数组，以便后续枚举"最小 y 的断点"
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

struct node {
    ll x, y;
    friend bool operator<(node u, node v) { return u.x > v.x; }
} p[N];
bool cmp(node a, node b) { return a.y < b.y; }

int n, k;
ll res, ans;
priority_queue<node> q;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> p[i].x >> p[i].y;
        res = max(res, p[i].x*p[i].y);//先算单个物品 x*y
    }
    sort(p+1,p+n+1,cmp);
    //取 y 最大的 k 个
    for (int i = n; i >= n-k+1; i--) { q.push(p[i]); ans += p[i].x; }
    res = ans*p[n-k+1].y;
    //逐步尝试：把更高 x 的较小 y 物品换进来
    for (int i = n-k; i >= 1; i--) {
        auto o = q.top();//堆内 x 最小者
        if (p[i].x > o.x) {//若能提升 x 总和
            ans -= o.x; ans += p[i].x; q.pop();
            q.push(p[i]); res = max(res, ans*p[i].y);//用当前最小 y 求
        }
    }
    while (!q.empty()) q.pop();
    ans = 0;
    for (int i = n; i >= n-k+2; i--) {
        q.push(p[i]); ans += p[i].x;
        res = max(res, ans*p[i].y);
    }
    cout << res << '\n';
    return 0;
}