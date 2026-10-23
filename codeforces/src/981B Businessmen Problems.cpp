//
// Created by Psy.C on 2026/10/23.
//

/**
真正学会的起点..
n：读入的次数（两段共用到）。
m（键，编号）、t（值，分数）。
i：循环计数器（由宏使用）。
mp：map<int,int> 映射，key 是编号 m，value 是对应最大值
max(mp[m], t)：对同一个编号 m，只保留出现过的最大的 t（取最大值覆盖）。

第一个循环：读入 n 组 (m, t)，对每组把 mp[m] 更新为 max(mp[m], t)。

第二个循环：重新读入一个 n，再读入 n 组 (m, t)，同样更新 mp[m]。

→ 即：两段输入合并处理，对于相同的 key m，最终保留所有出现中 t 的最大值。

for (auto &val: mp | views::values) sum += val;

用 C++20范围表达式 + views::values遍历 mp 的所有 value。
把全部 value 累加到 sum。
输出 sum
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i, n) for (i=1; i<=(n); i++)
#define int long long
using namespace std;


int n, i, m, t;
map<int, int> mp;
signed main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> m >> t;
        mp[m] = max(mp[m], t);
    }
    cin >> n;
    rep(i,n) {
        cin >> m >> t;
        mp[m] = max(mp[m], t);
    }
    int sum = 0;
    for (auto &val: mp | views::values) sum += val;
    cout << sum << '\n';
    return 0;
}