//
// Created by Psy.C on 2026/10/20.
//
/**
l[p] 和 r[p] 记录 p 在"差值序列"中的左右邻居索引
删除左右邻居（标记已用）后，维护链表结构
int L = l[p], R = r[p];
vis[L] = vis[R] = true;        // 标记左右邻居被"废弃"
l[p] = l[L];  r[l[L]] = p;     // 左邻居的左邻居 与 p 连接
r[p] = r[R];  l[r[R]] = p;     // 右邻居的右邻居 与 p 连接
这样 p 的新左右邻居变成原来 L 的左边、R 的右边，链表正确跳过被废弃的 L、R
首尾用极大值 inf 作为哨兵，防止越界取到不存在的邻居（取到 inf 则不会影响答案）
按差值从小到大的最小堆，每次弹出当前最小候选
while 循环先把堆顶那些已被 vis 标记废弃的过期元素弹出（惰性删除）。
每次取最小有效差值 x，累加进 sum。
然后生成反悔值重新入堆
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;

constexpr int N = 5e5+5e2, inf = 1e18;

int k, n, a[N], l[N], r[N];
priority_queue<ii, vector<ii>, greater<>> q;
bool vis[N];
signed main() {
    fast;
    cin >> k >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a+1, a+n+1);
    for (int i = 1; i < n; ++i) {
        a[i] = a[i+1] - a[i];
        l[i] = i-1, r[i] = i+1;
        q.emplace(a[i], i);//(差值, 索引)
    }
    a[0] = a[n] = inf; l[0] = 1, r[n] = n-1;
    int sum = 0;
    for (int i = 1; i <= k; ++i) {
        while (!q.empty() && vis[q.top().second]) q.pop();
        int x = q.top().first, p = q.top().second; q.pop();
        sum += x;
        a[p] = a[l[p]] + a[r[p]] - a[p];//合并出"反悔值"
        q.emplace(a[p], p);
        int L = l[p], R = r[p]; vis[L] = vis[R] = true;
        l[p] = l[L], r[l[L]] = p;
        r[p] = r[R], l[r[R]] = p;
    }
    cout << sum;
    return 0;
}