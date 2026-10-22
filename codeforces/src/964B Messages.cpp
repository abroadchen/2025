//
// Created by Psy.C on 2026/10/21.
//
/**
n：次数/笼数；A：每次基础报价；B：早采单价；C：晚采单价；T：最晚天数；a[i]：第 i 次可采摘的日期
ans = n*A：先给每次采摘计入基础报价 A，共 n 次，得到基准答案 n*A。
if (B < C)：只有当晚采单价 C 高于早采单价 B 时才值得多等。
若 B >= C：早采更优，不做任何补偿，答案就是 n*A。
若 B < C：对每个 a[i]，把它的采摘拖到第 T 天。晚了 T-a[i] 天，每天可多赚 C-B 差价，因此累加 (C-B)*(T-a[i]) 到答案。
最后输出 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e3+5;

int n, A, B, C, T, a[N], ans;
int main() {
    fast;
    cin >> n >> A >> B >> C >> T;
    for (int i = 1; i <= n; i++) cin >> a[i];
    ans = n*A;
    if (B < C)
        for (int i = 1; i <= n; i++)
            ans += (C-B)*(T-a[i]);
    cout << ans << '\n';
    return 0;
}