//
// Created by Psy.C on 2026/9/30.
//
/**
M 是"和值"能到的最大范围（a[i] 与偏移量都 ≤ 1e6 量级，和值上限 2e6）。
vis[x] = true 表示值 x 已被某个已经选好的方案占用了
1. 贪心选择偏移量 i

从小到大尝试每个偏移量 i。对当前候选 i，检查它与每个 a[j] 产生的和 a[j]+i 是否已被之前选好的偏移量占用（vis）。

2. vis 的作用

vis 记录了"所有已经被选中的偏移量 + 所有 a[j]"的配对和。这样一旦某个和值已经出现过，就不能再选会产生相同和的偏移量，保证所有配对和互不相同。

3. 占用 / 采纳

若 i 与所有 a[j] 的和都未被占用（flag=0），说明这个偏移量安全，采纳它：把 a[j]+i 全部标记为已占用，并把 i 存入 ans。

4. 终止条件

一旦凑满 n 个偏移量就提前结束，输出 YES；若枚举到上限 K=1e6 还没凑满，输出 No（cnt != n）。

ans[++cnt] = i：ans 存的是选中的偏移量（不是最终值）。输出时按顺序打印这些偏移量作为可行方案。
K=1e6：偏移量理论搜索上限。由于当 n 较小（≤105）而 K 很大，通常总能找到方案，所以多数情况输出 YES。
复杂度：O(K * n) 级别，约 1e6 × 105 = 1e8，配合 break 提前终止在可用范围内
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105, M = 2e6+5, K = 1e6;
int T, cnt, n, a[N], ans[N];
bool vis[M];
int main() {
    fast;
    cin >> T;
    while (T--) {
        cnt = 0;
        memset(vis, 0, sizeof(vis));
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= K; ++i) {
            bool flag = 0;
            for (int j = 1; j <= n; ++j)
                if (vis[i+a[j]]) { flag = 1; break; }
            if (flag) continue;
            for (int j = 1; j <= n; ++j) vis[a[j]+i] = 1;
            ans[++cnt] = i;
            if (cnt == n) break;
        }
        if (cnt == n) {
            cout << "YES\n";
            for (int i = 1; i <= cnt; ++i) cout << ans[i] << ' ';
            cout << '\n';
        } else cout << "No\n";
    }
    return 0;
}