//
// Created by Psy.C on 2026/9/20.
//
/**
n：数组长度，a[1..n] 数组元素。
ft[v]：值 v 首次出现的位置（下标）。初始 inf。
ed[v]：值 v 末次出现的位置。初始 0。
dp[i]：前 i 个位置能得到的最大贡献（DP 值）。
vis[]：去重标记，用于本轮扫描。
sum：当前段的异或和
ft[a[i]]：记录值 a[i] 第一次出现的下标。
ed[a[i]]：记录值 a[i] 最后一次出现的下标。
目标：对每个数值，知道它的"出现区间" [ft, ed]
内层扫描（j 从 i 往左）：

固定右端 i，尝试左端 j，判断 [j, i] 是否能构成一个"完整段"：

vis[a[j]]：这个值在 [j,i] 内是否已出现过。
第一次遇到某值 v（!vis[a[j]]）时：
if (ed[a[j]] > i) break;：如果值 v 在 i 之后还有出现，那么 [j,i] 就无法包含 v 的全部出现 → 这段不完整，直接 break（因为 j 再往左只会让段更大、更不可能排除外部出现）。
st = min(st, ft[a[j]])：更新段的"最左需求位置"（要把 v 的所有出现都包进来，段左端至少要能到 ft[v]）。
sum ^= a[j]：把 v 的值异或进本段得分（每个不同值只异或一次，因为去重了）。
vis[a[j]] = 1：标记 v 已计入。
if (st >= j) dp[i] = max(dp[i], dp[j-1]+sum);：只有当段的"需求左边界 st"不超过段左端 j（即 st ≥ j，说明段 [j,i] 确实完整覆盖了内部所有值的全部出现）时，[j,i] 才是一个合法的完整段，此时可以用 dp[j-1] + sum 更新 dp[i]。
注意 st >= j 这个条件：st 是所有已统计值的最左出现位置的最小值；段必须从 j 覆盖到 i，若要完整，需要 st ≥ j（即所有值的首现都在 j 到 i 之间）。其实正确性判断是"段内容纳了所有值的全部出现"，即 ft[v] >= j 且 ed[v] <= i 对所有段内 v。这里 ed[a[j]] > i 已经 break 保证 ed ≤ i；st>=j 保证 ft ≥ j。
DP 转移

dp[i] = dp[i-1]：不把 i 作为某段的右端（i 单独不成段或直接跳过）。
dp[j-1] + sum：把 [j,i] 作为一段，得分 sum，前面 [1,j-1] 用 dp[j-1]。
取所有合法段的最大值。
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e3+10, inf = 0x3f3f3f3f;
int ft[N], ed[N], a[N], dp[N], vis[N];
int main() {
    fast;
    int n; cin >> n;
    memset(ft, inf, sizeof ft);
    memset(ed, 0, sizeof ed);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ft[a[i]] = min(ft[a[i]], i);
        ed[a[i]] = max(ed[a[i]], i);
    }
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i-1];
        memset(vis, 0, sizeof vis);
        int sum = 0, st = i;
        for (int j = i; j >= 1; --j) {
            if (!vis[a[j]]) {
                if (ed[a[j]] > i) break;
                st = min(st, ft[a[j]]);
                sum ^= a[j];
                vis[a[j]] = 1;
            }
            if (st >= j) dp[i] = max(dp[i], dp[j-1]+sum);
        }
    }
    cout << dp[n] << '\n';
    return 0;
}