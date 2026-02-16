//
// Created by Psy.C on 2026/2/16.
//
/**
时间复杂度：
O(k × n log n)，每次操作需要排序
空间复杂度：
O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1005, M = 110;
int n, k, ans[N][2];//一对操作
ii p[M];//值和原始索引

int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].first; p[i].second = i;
    }
    sort(p + 1, p + n + 1);
    if (p[n].first == p[1].first) cout << "0 0\n";//最大值等于最小值（所有数相等)
    else {
        int cnt = 0;
        for (int i = 0; i < k; ++i) {
            ans[cnt][0] = p[n].second;//最大值的原始索引
            ans[cnt++][1] = p[1].second;//最小值的原始索引
            p[n].first--; p[1].first++;//最大值-1，最小值+1
            sort(p + 1, p + n + 1);
            if (p[n].first == p[1].first) break;
        }
        cout << p[n].first - p[1].first << ' ' << cnt << '\n';
        for (int i = 0; i < cnt; ++i)
            cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    }
    return 0;
}