//
// Created by Psy.C on 2026/10/17.
//
/**
读入 n 个数，全部插入 multiset p（可重复）。
i 从 1 递增（1, 2, 3, ...），j 从 N=1e6 递减（1e6, 999999, ...）。
每轮：若 p 中包含 i，则 n--；若 p 中包含 j，则 n--。
当 n == 0 时退出循环。
否则 ans++（每轮 +1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;
constexpr int N = 1e6;
multiset<int> p;//可存放重复值的集合，自动升序
int main() {
    fast;
    int n, ans = 0; cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x; p.insert(x);
    }
    for (int i = 1, j = N; ; ++i, --j) {
        if (p.contains(i)) --n;
        if (p.contains(j)) --n;
        if (n == 0) break;
        ans++;
    }
    cout << ans;
    return 0;
}