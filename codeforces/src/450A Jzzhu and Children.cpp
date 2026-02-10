//
// Created by Psy.C on 2026/2/10.
//
/**
n：元素总数
m：每次减少的数值
a[N]：存储n个初始数值的数组
queue<ii> q：存储(pair<位置, 数值>)的队列

模拟约瑟夫斯问题

时间复杂度：O(∑a[i]/m)，取决于所有元素值的总和
空间复杂度：O(n)，队列最多存储n个元素
 */
#include <iostream>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
#define ii pair<int, int>
using namespace std;

int n, m, a[N];
queue<ii> q;

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) q.emplace(i, a[i]);
    ii p;
    while (!q.empty()) {
        p = q.front(); q.pop();
        p.second -= m;
        if (p.second > 0) q.push(p);
    }
    cout << p.first << '\n';
    return 0;
}