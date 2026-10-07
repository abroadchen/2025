//
// Created by Psy.C on 2026/10/7.
//
/**
a[1..n]：一组数值（例如高度/价格）。
p[1..m]：pair，.first 和 .second 分别读入，second 是某种"额度/优惠"
sort 按 pair 默认排序 = 按 first 升序
从右往左（i 从 n 往 1）。
内层从 j = i 向左走，凡是 a[j] <= a[i] 就一路累加进 tot，直到遇到第一个 a[j] > a[i] 停下。
即：tot = 以 a[i] 为"当前段最大值"的一整段连续元素之和，这一段里的每个元素都不超过 a[i]。
然后 i = j，继续处理下一段。
所以整个数组被分成若干段，每段内元素值都 ≤ 该段最右端 a[i]（因为是倒序扫描，段以某个"峰值"右端点为界，往左遍历到下一个更大的值为止）
pre 记录上次处理到哪，保证每段只把"first ≤ 当前段最大值 a[i]"的 p 压一次。
小根堆 q 存的是这些额度 second，堆顶是最小额度
每次尝试：当前段总和 tot 是否 ≥ 当前最小额度。
若够：ans++（说明这一段能满足一个小额度需求），tot 扣除该额度，弹出。
若不够：说明最小额度大于 tot，把差值 q.top() - tot 重新压回堆（相当于"借/合并额度"），并 break 跳出本段处理。
结果累加到 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e5+7, inf = 1e9+7;
int a[N];
ii p[N];
priority_queue<int, vector<int>, greater<>> q;
int main() {
    fast; a[0] = inf;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> p[i].first;
    for (int i = 1; i <= m; ++i) cin >> p[i].second;
    sort(p+1, p+1+m);
    int j = 0, k, pre = 1, ans = 0; ll tot;
    for (int i = n; i >= 1; i = j) {
        tot = 0;
        for (j = i; a[j] <= a[i]; --j) tot += a[j];
        for (k = pre; k <= m && p[k].first <= a[i]; ++k)
            q.push(p[k].second);
        pre = k;
        while (!q.empty()) {
            if (tot >= q.top()) ans++, tot -= q.top(), q.pop();
            else {
                tot = q.top() - tot; q.pop();
                q.push(tot);
                break;
            }
        }
    }
    cout << ans << '\n';
    return 0;
}