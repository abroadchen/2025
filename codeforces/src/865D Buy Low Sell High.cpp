//
// Created by Psy.C on 2026/10/4.
//
/**
每个数 k（可以理解为股票某天的价格）。
维护一个小根堆，堆里存的是已经"买入"的候选价格/以及卖出后留下的代理。
当读到一个新价格 k 大于堆顶（当前最低可买入价格）时，就假装以堆顶价格买入、以 k 卖出，赚取差价 k - 堆顶，把差价累加进 ans；然后把堆顶弹出，把 k 再推回堆（这就是"反悔"：把 k 作为未来可能的"新的买入点"代理）。
关键细节：q.push(k) 出现两次（一次在 if 里，一次无条件）‍——这正是 CF 867E 的标准写法：

if 里 q.push(k)：卖出后，k 要作为新的代理入堆，以便未来可能以更高的价格再卖出（可反悔）。
底部无条件 q.push(k)：每个价格自身都作为潜在的"最低买入点"加入堆。
这样跑完所有价格，ans 就是能获得的最大总利润（可任意多次买卖、可反悔的买入卖出）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

priority_queue<int, vector<int>, greater<>> q;
int ans;
signed main() {
    fast;
    int n = rd();
    for (int i = 1; i <= n; ++i) {
        int k = rd();
        if (!q.empty() && q.top() < k)
            ans += k - q.top(), q.pop(), q.push(k);
        q.push(k);
    }
    cout << ans << '\n';
    return 0;
}