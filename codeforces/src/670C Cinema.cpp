//
// Created by Psy.C on 2026/4/12.
//
/**
mx: 当前最优项中b[i]对应的频率最大值
mx2: 当b频率相同时，c[i]对应的频率最大值
ans: 最优答案的索引

优先级1: 比较mp[b[i]]（b[i]在a数组中的出现频率）
优先级2: 如果mp[b[i]]相同，则比较mp[c[i]]（c[i]在a数组中的出现频率）
如果mp[b[i]] > mx: 找到了更好的b频率，更新所有值
如果mp[b[i]] < mx: 当前项不如已有最佳项，跳过
如果mp[b[i]] == mx: b频率相同，比较c频率，如果mp[c[i]] > mx2则更新

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+5;
int n, m, a[N], b[N], c[N];
map<int, int> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i], mp[a[i]]++;
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> b[i];
    for (int i = 1; i <= m; ++i) cin >> c[i];
    int mx = -1, mx2 = -1, ans = 0;
    for (int i = 1; i <= m; ++i) {
        if (mp[b[i]] > mx)
            mx = mp[b[i]], mx2 = mp[c[i]], ans = i;
        else if (mp[b[i]] < mx) continue;
        else if (mp[c[i]] > mx2)
            mx2 = mp[c[i]], ans = i;
    }
    cout << ans << '\n';
    return 0;
}