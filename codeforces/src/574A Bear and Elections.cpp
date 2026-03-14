//
// Created by Psy.C on 2026/3/14.
//
/**
定义最大堆优先队列 q
n: 总共的数字个数
x: 初始目标值
t: 临时变量
只有当数值 >= x 时才加入优先队列
如果没有元素大于等于x，则无需操作，返回0
当最大元素仍大于等于x时继续循环
x++: 提升目标值（这是一次操作）
ans++: 操作次数增加
t = q.top(); q.pop(): 取出最大元素
q.push(t - 1): 将最大元素减1后放回队列

时间复杂度: O(m log m)，其中m是≥x的元素个数 空间复杂度: O(m)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
priority_queue<int> q;
int n, x, t;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 2; i <= n; ++i) {
        cin >> t;
        if (t >= x) q.push(t);
    }
    if (q.empty()) { cout << "0\n"; return 0; }
    int ans = 0;
    while (x <= q.top()) {
        x++; ans++;
        t = q.top(); q.pop();
        q.push(t - 1);
    }
    cout << ans << '\n';
    return 0;
}