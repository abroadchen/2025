//
// Created by Psy.C on 2026/10/10.
//
/**
计算 x 的平方根 q（向下取整），若 q*q == x 则说明 x 是完全平方数
读入所有数并统计其中完全平方数的个数 cnt
情况一：cnt > n/2（完全平方数太多了，需要把一些"降级"成非完全平方数）
目标：把多出来的 cnt - n/2 个完全平方数变成非完全平方数。

对每个已有的完全平方数：

若 a[i] != 0：变 1 步就能变非平方数（如 4→5 或 4→3，都不是平方数，只需 ±1），代价是 1
若 a[i] == 0：0 的邻居 1 是平方数、-1 不是平方数但需要从 0 走到 -1 是 1 步……这里填了 2，因为 0 加 1 得 1（仍是平方数），需要减到 -1（不是平方数）或加 2 到 2（非平方数），至少 2 步
把每个需要降级元素的代价放进 b，排序后取最小的 cnt - n/2 个相加，得到最小代价
情况二：cnt < n/2（完全平方数不够，需要把一些"升格"成完全平方数）
目标：把缺的 n/2 - cnt 个非平方数变成完全平方数。

对每个非完全平方数：

q = sqrt(a[i])：向下取整的平方根
最近的平方数有上下两个：q²（≤ a[i]）和 (q+1)²（≥ a[i]）
到 q² 的距离是 a[i] - q*q
到 (q+1)² 的距离是 (q+1)*(q+1) - a[i]
取两者较小者作为该数"升格"所需代价
代价全部放进 b，排序后取最小的 n/2 - cnt 个相加。（注意：这里计算 sq 变量时 s1 = a[i] - q*q，只对非完全平方数使用，q*q != a[i] 所以 s1 >= 1，正确。）
情况三：cnt == n/2
数量刚好达标，代价为 0

排序
O
(
n
log
⁡
n
)
O(nlogn)
主循环
O
(
n
)
O(n)，每次计算平方根
O
(
1
)
O(1)
总复杂度
O
(
n
log
⁡
n
)
O(nlogn)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;

bool check(int x) {
    int q = sqrt(x);
    return q*q == x;
}

int n, a[N], cnt;
vector<ll> b;
ll ans;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (check(a[i])) cnt++;
    }
    if (cnt > n/2) {
        for (int i = 1; i <= n; ++i)
            if (check(a[i])) {
                if (a[i] != 0) b.push_back(1);
                else b.push_back(2);
            }
        ranges::sort(b);
        for (int i = 0; i < cnt-n/2; ++i) ans += b[i];
        cout << ans;
    }
    else if (cnt < n/2) {
        for (int i = 1; i <= n; ++i)
            if (!check(a[i])) {
                int q = sqrt(a[i]);
                ll s1 = a[i]-q*q, s2 = (q+1)*(q+1) - a[i];
                b.push_back(min(s1, s2));
            }
        ranges::sort(b);
        for (int i = 0; i < n/2-cnt; ++i) ans += b[i];
        cout << ans;
    }
    else cout << 0;
    return 0;
}