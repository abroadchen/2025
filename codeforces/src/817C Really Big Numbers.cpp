//
// Created by Psy.C on 2026/9/22.
//
/**
f(x) 即"数位和"，如 f(123)=6；get(x) 即"几位数"，如 get(123)=3
读入上界 n 和阈值 s；ans 累计答案；len = s 的位数。
为什么从 s 开始统计？因为对任何 i < s，i - f(i) < i < s，必定不满足条件，无需考虑
函数 g(i) = i - f(i) 是单调不减的：从 i 到 i+1，数位和最多增加 1，所以
g(i+1) - g(i) = 1 - (f(i+1) - f(i)) ≥ 0。
即一旦某个 i 满足 g(i) >= s，则此后所有更大的 i 都满足。

同时，f(i) ≤ 9 × 位数，所以当 i ≥ s + len*9 时必有
g(i) = i - f(i) ≥ i - 9*len ≥ s，
即枚举到 s + len*9 一定已经越过满足点。这正是下面循环上界的由来
只需枚举 i 从 s 到 s + len*9（一个很窄的窗口，因为越过它必然满足）。
若中途 i 已 > n，说明整个 [s, n] 都枚举完了，直接 break，此时答案就是 ans。
否则在窗口内逐个数出"首个满足点之前"中恰好满足的个数 ans
若 i > n：窗口已覆盖全部范围，输出 ans。
否则（循环正常结束，i == s+len*9+1 ≤ n）：由单调性质，从 i 到 n 的所有数都已满足，把这整段个数 n - i + 1 加上前面的 ans 一起输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int inf = 1e18;

int f(int x) {
    int ans = 0;
    while (x) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int get(int x) {
    int ans = 0;
    while (x) { x /= 10; ans++; }
    return ans;
}


signed main() {
    fast;
    int n, s; cin >> n >> s;
    int ans = 0, i, len = get(s);
    for (i = s; i <= s+len*9; ++i) {
        if (i > n) break;
        if (i - f(i) >= s) ans++;
    }
    if (i > n) cout << ans << '\n';
    else cout << n-i+1+ans << '\n';
    return 0;
}