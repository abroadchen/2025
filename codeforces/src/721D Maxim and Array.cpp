//
// Created by Psy.C on 2026/4/23.
//
/**
pos：原始位置索引
val：数值
重载 < 操作符：按绝对值大小排序（绝对值大的优先）
n：数组长度
k：操作次数
x：每次操作的增量
将所有元素放入优先队列（按绝对值最大优先）
执行k次操作：每次取出最大绝对值元素
如果是正数，加上x
如果是负数，减去x（使绝对值更大）
将结果放回原位置
输出最终数组

读入数组元素，记录位置，统计负数个数
如果全是非负数，找最小值
计算需要多少次操作使其变为负数
执行相应操作
如果有偶数个负数，找绝对值最小的数
如果该数为正：减去x使其变为负数
如果该数为负：加上x使其变为正数
目的是让最终负数个数为奇数（有利于最大化）

(a + b - 1) / b 是向上取整
(a + b) / b 也是向上取整（只是a的值增加了1）
+1 是为了确保变成负数而不是零
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;

struct node {
    int pos; ll val;
    bool operator<(const node &o) const {
        return abs(val) > abs(o.val);
    }
} tr[N];

int n;
ll k, x;
void get() {
    priority_queue<node> q;
    for (int i = 1; i <= n; ++i) q.push(tr[i]);
    while (k) {
        auto now = q.top(); q.pop();
        if (now.val >= 0) now.val += x;
        else now.val -= x;
        q.push(now);
        k--;
    }
    while (!q.empty()) { tr[q.top().pos] = q.top(); q.pop(); }
    for (int i = 1; i <= n; ++i)
        cout << tr[i].val << ' ';
    cout << '\n';
}

int cnt;
int main() {
    fast;
    cin >> n >> k >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> tr[i].val; tr[i].pos = i;
        if (tr[i].val < 0) cnt++;
    }
    if (cnt == 0) {
        int idx = 1;
        for (int i = 1; i <= n; ++i)
            if (tr[i].val < tr[idx].val) idx = i;
        ll t = (tr[idx].val + 1ll + x - 1) / x;
        if (t > k) tr[idx].val -= k*x;
        else tr[idx].val -= t*x;
        k -= min(t, k);
    } else if (cnt > 0 && cnt%2 == 0) {
        int idx = 1;
        for (int i = 1; i <= n; ++i)
            if (abs(tr[i].val) < abs(tr[idx].val))
                idx = i;
        if (tr[idx].val >= 0) {
            ll t = (tr[idx].val + 1ll + x - 1) / x;
            if (t > k) tr[idx].val -= k*x;
            else tr[idx].val -= t*x;
            k -= min(t, k);
        } else {
            ll t = (abs(tr[idx].val)+1ll+x-1) / x;
            if (t > k) tr[idx].val += k*x;
            else tr[idx].val += t*x;
            k -= min(t, k);
        }
    }
    get();
    return 0;
}