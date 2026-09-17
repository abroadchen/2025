//
// Created by Psy.C on 2026/9/17.
//
/**
n：位置/元素个数。
m：目标/参照位置（通常是人所在位置，1-based）。
k：目标数值上限（要找数值 ≤ k 的）
对第 i 个位置：
读入 a[i]。
若该位置数值 a[i] <= k（≤ 期望上限）‍ 并且 a[i] != 0（非零）‍，则这个位置是"候选"。
记录它到 m 的距离 abs(i - m)，压入 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a[105];
vector<int> ans;
int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] <= k && a[i] != 0)
            ans.push_back(abs(i-m));
    }
    ranges::sort(ans);
    cout << ans[0]*10 << '\n';
    return 0;
}