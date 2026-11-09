//
// Created by Psy.C on 2026/11/9.
//

/**
真正学会的起点..
n：点数
s：目标点编号
a[i]：点 i 是否因"正向可达"被标记
b[i]：点 i 是否因"换乘回跳"被标记
如果 a[1] == 0，表示第 1 号点一开始就不可达。既然连起点都进不去，后面自然到不了 s → 直接 NO
如果目标点 s 本身能被直接（正向）到达，则一路正向走过去即可 → YES。
当 a[s] == 0（正向到不了 s）但 b[s] == 1（s 可以通过换乘回跳到达）时：

思路：要先走到某个比 s 编号大（或等于 s）且既能正向到达、又能作为回跳起点的点 i，再从 i 借助 b 回跳到 s。
所以从 s 一路往上枚举 i ∈ [s, n]，寻找：
a[i] == 1：点 i 能正向走过去；
a[i] == b[i]（即 b[i]==1 因为此时 a[i]==1）：点 i 同时具备"回跳能力"。
一旦找到这样的 i，说明可以从 1 → ... → i（正向）→ 回跳到 s → YES。
如果一路到 n 都没找到，则 NO。
为什么范围从 s 开始：回跳的目标是 s，通常只能从编号 ≥ s 的点往回跳到 s，所以枚举从 s 开始往大走
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (i=1; i<=n; ++i)
using namespace std;

constexpr int N = 1010;

int n, s, a[N], b[N];
int main() {
    fast; int i;
    cin >> n >> s;
    rep(i,n) cin >> a[i];
    rep(i,n) cin >> b[i];
    if (a[1] == 0) cout << "NO\n";
    else if (a[s] == 1) cout << "YES\n";
    else if (b[s] == 1) {
        bool f = 0;
        for (i = s; i <= n; i++) if (a[i] == 1 && a[i] == b[i]) { f = 1; break; }
        if (f) cout << "YES\n"; else cout << "NO\n";
    } else cout << "NO\n";
    return 0;
}