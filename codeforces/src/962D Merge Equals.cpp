//
// Created by Psy.C on 2026/10/21.
//
/**
q：小根堆，按 pair 从小到大（先按 first 即数值，再按 second 即下标）。
ans：同样是小根堆，用于收集输出的元素
读入 n，把 n 个数 (t, i) 放入小根堆 q（i 为输入顺序/下标）。
while(q.size()>1)：只要堆里至少两个元素：
弹出最小两个 a=(va,ia) 与 b=(vb,ib)（因小根堆，va <= vb）。
若相等 va == vb：合并成 (va*2, b.second) 放回 q（用第二个的下标）。这里"合并"把两个相等的合并成一个两倍值。
若不等（va < vb）：把大的 b 放回堆（q.push(b)），把较小的 a 记为"淘汰"结果，其数值 va、下标 ia 存入 ans。
循环结束后堆里只剩 1 个元素，把它也放入 ans。
输出 ans.size()，再从小到大输出 ans 中每个元素的数值 second（用空格分隔）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

priority_queue<ii, vector<ii>, greater<>> q, ans;
signed main() {
    fast;
    int n = rd();
    for (int i = 0; i < n; ++i) {
        int t = rd();
        q.emplace(t, i);
    }
    while (q.size() > 1) {
        ii a, b; a = q.top(); q.pop(); b = q.top(); q.pop();
        if (a.first == b.first) q.emplace(a.first*2, b.second);
        else q.push(b), ans.emplace(a.second, a.first);
    }
    ans.emplace(q.top().second, q.top().first);
    cout << ans.size() << '\n';
    while (!ans.empty()) {
        ii now = ans.top(); ans.pop();
        cout << now.second << ' ';
    }
    return 0;
}