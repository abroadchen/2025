//
// Created by Psy.C on 2025/11/24.
//
/*
*首先按b字段降序排列
如果b相等，则按a字段降序排列
 *
*每次选择一个节点，将其a值加入结果
选择后，剩余次数增加该节点的b值
继续选择直到没有剩余次数或遍历完所有节点
 *
*时间复杂度：O(n log n)，主要消耗在排序上
空间复杂度：O(n)，存储节点数组
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define sz(x) ((int)(x).size())
using namespace std;

constexpr int N = 1e3+50;
struct node { int a, b; } p[N];

bool cmp(const node x, const node y) {
    if (x.b == y.b) return x.a > y.a;
    return x.b > y.b;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> p[i].a >> p[i].b;
    sort(p, p+n, cmp);
    int ans(0), k(0), cnt(1);
    while (cnt--) {
        ans += p[k].a;
        cnt += p[k++].b;
        if (cnt == 0 || k == n) break;
    }
    cout << ans << '\n';
    return 0;
}