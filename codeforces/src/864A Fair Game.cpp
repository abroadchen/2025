//
// Created by Psy.C on 2026/10/4.
//
/**
a[x]：计数数组。a[x] 表示数值 x 出现了几次（值域是 1-100，N=110 足够）。
b[]：去重存储，按首次出现顺序记录所有不同数值
读入 n 个数 x：

如果 a[x]==0（即这个值第一次出现），就把 x 存进 b[++cnt]，cnt 自增，表示"目前发现了 cnt 种不同的数值"。
无论是否首次出现，都 ++a[x] 给这个数值的出现次数 +1
cnt == 2：恰好只有两种不同的数值。
a[b[1]] == a[b[2]]：这两种数值各自出现的次数相等（因为整个数组就 n 个数，两种数次数相等就意味着每种恰好出现 n/2 次）。
两者同时满足才输出 YES 和这两个数值；否则输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 110;
int a[N], b[N];
int main() {
    fast;
    int n, cnt = 0; cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        if (!a[x]) b[++cnt] = x;
        ++a[x];
    }
    if (cnt == 2 && a[b[1]] == a[b[2]]) {
        cout << "YES\n" << b[1] << ' ' << b[2] << '\n';
    } else cout << "NO\n";
    return 0;
}