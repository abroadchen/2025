//
// Created by Psy.C on 2026/10/8.
//
/**
a[n]：n 个元素（权重）。
q：priority_queue<int>，大顶堆（C++ priority_queue 默认大的在顶）。
入堆时压入 -a[i]（取负），这样负数的"最大"就是原数的最小，即用大顶堆实现了小顶堆效果——堆顶永远是最小的原数值
所有元素取负压入堆（等效小顶堆)
若 n 是偶数（三叉哈夫曼需要操作数凑成"奇数个"），先弹出两个最小元素合并：
-x-y 是这两个元素的和（因为 x、y 是负数），累加到 ans；
把合并后的和 x+y（也是负数）重新压回堆
只要堆中元素 ≥ 3，就每次弹出最小的 3 个合并成 1 个，累加三者和 -x-y-z，把新和压回堆。
不断三路合并直到堆中只剩 1 个元素
输出所有合并步骤的代价总和 = 三叉哈夫曼树的总带权路径长度（WPL）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 2e5+5;
int n, a[N], ans;
priority_queue<int> q;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; q.push(-a[i]);
    }
    if (!(n&1)) {
        int x, y;
        x = q.top(); q.pop();
        y = q.top(); q.pop();
        ans += -x-y;
        q.push(x+y);
    }
    while (q.size() >= 3) {
        int x, y, z;
        x = q.top(); q.pop();
        y = q.top(); q.pop();
        z = q.top(); q.pop();
        ans += -x-y-z;
        q.push(x+y+z);
    }
    cout << ans;
    return 0;
}