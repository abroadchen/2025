//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
2×2 → 0
2×3 → 4
2×7 → 12
当只有一行（1×m）时，答案按 m 对 6 取模分三类：

m % 6 == 0：输出 m（刚好全部能用上）。
m % 6 <= 3：输出 m - (m%6)（向下取整到 6 的倍数，余 1/2/3 的部分浪费掉）。
否则（m%6 为 4 或 5）：输出 m - (6 - m%6)，即向上补到 6 的倍数再少一点。
这本质是对一行内按周期 6 的某种覆盖规律做出的结论（与"马步/某棋子一次跨 6 格"的周期性相关）
若 n 和 m 都是奇数：输出 n*m - 1（面积减一）。
否则（至少一边是偶数）：输出 n*m（整个面积）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, m;
signed main() {
    fast;
    cin >> n >> m;
    if (n > m) swap(n, m);
    if (n == 2 && m == 2) { cout << "0\n"; return 0; }
    if (n == 2 && m == 3) { cout << "4\n"; return 0; }
    if (n == 2 && m == 7) { cout << "12\n"; return 0; }
    if (n == 1) {
        if (m%6 == 0) { cout << m << '\n'; return 0; }
        if (m%6 <= 3) { cout << m-m%6 << '\n'; return 0; }
        cout << m-(6-m%6) << '\n';
        return 0;
    }
    if (n%2 && m%2) cout << n*m-1 << '\n'; else cout << n*m << '\n';
    return 0;
}