//
// Created by Psy.C on 2026/10/24.
//

/**
真正学会的起点..
若排序后前 n 个最小数中最大值 a[n] 与最小值 a[1] 的差已经超过 l，说明连"取最小的 n 个"都无法满足差值限制，更不可能有解，直接输出 0
while (p <= m && a[p]-a[1] <= l) p++;：找到最大下标 p，使得 a[p] - a[1] ≤ l。即所有与 a[1] 的差不超过 l 的数都在 a[2..p-1] 范围内（[1, p-1] 区间内的数都可用）。
贪心循环，执行 n 次（每次选一个数）：
ans += a[i];：累加当前选中的数 a[i]。
if (p-i-n >= k) i += k; else i = p-n+1;：
更新下一个要选的数位置 i。
p-i-n 判断当前还能用多少个在合法区间内的数。
若剩余可用的合法性还充裕（p-i-n >= k），说明可以从 i 往后跳 k 个（保证每组候选充足），即 i += k，贪心地选尽量大的数。
否则说明剩余的合法数不够完整地填满，只能从 p-n+1 位置选（下边界收紧，保证最终仍能选出 n 个合法数）。
循环条件 n > 0 意味着每轮 n 自减 1，直到选满 n 个。
最终输出 ans（选出的 n 个数总和的最大值）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 1e5+5;

int n, k, l, m, a[N];
signed main() {
    fast;
    cin >> n >> k >> l; m = n*k;
    for (int i = 1; i <= m; i++) cin >> a[i];
    sort(a+1, a+m+1);
    if (a[n] - a[1] > l) cout << 0;
    else {
        int p = 1, ans = 0;
        while (p <= m && a[p] - a[1] <= l) p++;
        for (int i = 1; n > 0; n--) {
            ans += a[i];
            if (p-i-n >= k) i += k; else i = p-n+1;
        }
        cout << ans;
    }
    return 0;
}