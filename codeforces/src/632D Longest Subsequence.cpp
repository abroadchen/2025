//
// Created by Psy.C on 2026/3/30.
//
/**
n: 数组长度
m: 上界值
a[i]: 输入数组
v[i]: 存储值为i的元素在原数组中的位置
将值≤m的元素按值分组，记录其在原数组中的位置
对于每个值i，将其所有不超过m的倍数位置都增加v[i].size()个
也就是说，如果存在值i，那么i的所有倍数j（j≤m）都会受到影响
cnt[k] 表示值为k的倍数的元素个数
找到使cnt最大的索引
mx是要找的最大倍数值
对于mx的所有因数i
将值为i的所有位置加入优先队列（小顶堆，保证升序）

如果队列非空：
cout << q.size(): 输出队列中元素的总个数
'\n': 换行
<< q.top(): 输出第一个元素（最小的位置）
q.pop(): 弹出第一个元素
如果队列为空：
输出 0 和换行
输出空格分隔的其余元素
每次输出队顶元素后弹出

时间复杂度约为O(m log m + n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5;
int n, m, a[N];
vector<int> v[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] <= m) v[a[i]].push_back(i);
    }
    vector<int> cnt(m+5);
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= m/i; ++j)
            cnt[i*j] += v[i].size();
    int mx = max(1, (int)(ranges::max_element(cnt) - cnt.begin()));
    priority_queue<int, vector<int>, greater<>> q;
    for (int i = 1; i <= mx; ++i)
        if (mx % i == 0)
            for (int j : v[i]) q.push(j);
    cout << mx << ' ';
    if (!q.empty()) {
        cout << q.size() << '\n' << q.top(); q.pop();
    } else cout << 0 << '\n';
    while (!q.empty()) {
        cout << ' ' << q.top(); q.pop();
    }
    cout << '\n';
    return 0;
}