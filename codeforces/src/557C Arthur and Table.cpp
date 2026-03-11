//
// Created by Psy.C on 2026/3/11.
//
/**
0x3f3f3f3f = 1061109567
l为左端点，d为某种权重/长度
tr[N]: 存储所有区间
n: 区间总数
cnt[N]: 计数数组，记录各种权重的出现次数

读入n个区间的左端点
读入n个区间的权重/长度，并计算总和
按左端点升序排序所有区间
处理相同左端点的区间组
num: 当前左端点的区间数量
cost: 剩余区间总权重（排除当前左端点的区间）
贪心优化: 从最大权重开始，用之前统计的区间来抵消当前需求
num--: 减少1是为了满足覆盖约束
按权重从大到小使用已统计的区间来减少总成本
更新最小成本
将当前左端点的区间权重加入计数数组
移动到下一组不同左端点的区间

排序: O(n log n)
主循环: O(n × M) = O(200n) ≈ O(n)
总体: O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 200, inf = 0x3f3f3f3f;

struct node { int l, d; } tr[N];
int n, cnt[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> tr[i].l;
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> tr[i].d; sum += tr[i].d;
    }
    sort(tr + 1, tr + n + 1, [](node a, node b) {
        return a.l < b.l;
    });
    int i = 1, j, ans = inf;
    while (i <= n) {
        int num = 0, cost = sum;
        for (j = i; tr[j].l == tr[i].l; ++j) {
            num++; cost -= tr[j].d;
        }
        num--;
        for (j = M; j >= 1 && num > 0; --j) {
            cost -= min(num, cnt[j]) * j;
            num -= cnt[j];
        }
        ans = min(ans, cost);
        for (j = i; tr[j].l == tr[i].l; ++j)
            cnt[tr[j].d]++;
        i = j;
    }
    cout << ans << '\n';
    return 0;
}