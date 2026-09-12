//
// Created by Psy.C on 2026/9/12.
//
/**
s[i][0] = a[0]a[1]a[2]（名字前 3 字母）。
s[i][1] = a[0]a[1]b[0]（名字前 2 + 姓氏首字母）。
mp = 每种 s[i][1]（第二候选）出现的次数。
cnt = 每种候选（两个都计）出现的次数
默认为第二候选 s[i][1]。
若该第二候选只出现一次（mp==1），它不会冲突，直接用它，continue。
否则（第二候选多人想要）尝试改用第一候选 s[i][0]，条件是第一候选只出现一次（cnt[s[i][0]]==1）——这样第一候选没人抢，可安全分配给 i
统计最终分配结果每种用户名出现次数。
若所有用户名出现次数都 ≤1（互不相同）→ YES，输出方案。
否则 → NO
 */
#include <ranges>
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+10;
string s[N][2], a, b, ans[N];
map<string, int> mp, cnt, res;
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) s[i][0] = "@@@", s[i][1] = "@@@";
    for (int i = 1; i <= n; ++i) {
        cin >> a >> b;
        s[i][0][0] = a[0], s[i][0][1] = a[1], s[i][0][2] = a[2];
        s[i][1][0] = a[0], s[i][1][1] = a[1], s[i][1][2] = b[0];
        mp[s[i][1]]++; cnt[s[i][0]]++, cnt[s[i][1]]++;
    }
    for (int i = 1; i <= n; ++i) {
        ans[i] = s[i][1];
        if (mp[s[i][1]] == 1) continue;
        if (cnt[s[i][0]] == 1) ans[i] = s[i][0];
    }
    for (int i = 1; i <= n; ++i) res[ans[i]]++;
    bool flag = true;
    for (const auto &val: res | views::values)
        if (val >= 2) flag = false;
    if (flag) {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
        return 0;
    }
    cout << "NO\n";
    return 0;
}