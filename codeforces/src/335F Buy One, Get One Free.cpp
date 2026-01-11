//
// Created by Psy.C on 2026/1/11.
//
/**
 *
*res 存储所有数字的总和
b 数组存储值和其出现次数的对（值，次数）
m 记录不同数值的个数
*cur 当前处理的数量
sum 累计处理的总数
q 最小堆（优先队列），存储处理后的结果
 *
*遍历每种不同的数值
使用结构化绑定获取当前值(val)和出现次数(cnt)
计算当前能直接使用的数量（避免过度使用）
 *将cur个当前值添加到临时向量
 *
*lim 是基于已有数据的处理限制
从最小堆中取出最小值进行比较和处理
如果堆顶元素小于当前值，则使用当前值
否则根据一定条件决定是否进行数值变换
*将处理后的值重新加入最小堆
更新累计处理总数
*从最小堆中取出所有元素，从总和中减去它们
输出最终结果
 *
*当我们从堆中取出一个较小的值 x，并且发现当前值 val 更大时
我们可以选择使用 val 替代 x，并且在不是最后一轮的情况下，会成对地使用 val
j 每次增加2（j += 2），表示每次处理一对元素
如果 j == lim，说明这是最后一次处理，只添加一个 val
 *
*当堆中的值 x 比当前值 val 更大或相等时，我们保留 x
但在某些情况下（不是最后一轮且 2*val >= x），我们可以用 val 的两倍减去 x 来得到一个新值
这个新值 val*2 - x 实际上是一种"补偿"机制，可能代表了一种更优的组合方式
 *
* min(cnt, sum)：
从当前值的出现次数 cnt 和累计总数 sum 中取较小值
这确保了不会超出已有的数据范围
min(cnt, sum) - cur：
减去已经直接使用的数量 cur
得到还可以进一步处理的数量限制
 *
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 500005
using namespace std;


int main() {
    fast;
    ll n, a[N]; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1, [](const int x, const int y) {
        return x > y;
    });
    ll res = 0; pair<ll, ll> b[N]; int m = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[m].first != a[i]) b[++m].first = a[i];
        b[m].second++;
        res += a[i];
    }
    ll cur = 0, sum = 0;
    priority_queue<ll, vector<ll>, greater<>> q;
    for (int i = 1; i <= m; ++i) {
        auto [val, cnt] = b[i];
        cur = sum - 2*q.size() < cnt ? static_cast<ll>(sum - 2*q.size()) : cnt;
        vector<ll> t; t.clear();
        for (int j = 1; j <= cur; ++j) t.push_back(val);
        const ll lim = min(cnt, sum) - cur;
        for (int j = 1; j <= lim; j += 2) {
            ll x = q.top(); q.pop();
            if (x < val) {
                t.push_back(val);
                if (j != lim) t.push_back(val);
            } else {
                t.push_back(x);
                if (j != lim && 2 * val >= x) t.push_back(val*2 - x);
            }
        }
        for (auto x : t) q.push(x);
        sum += cnt;
    }
    while (!q.empty()) res -= q.top(), q.pop();
    cout << res;
    return 0;
}